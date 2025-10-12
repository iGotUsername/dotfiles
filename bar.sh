#!/bin/dash
# Minimal status bar: RAM · Battery · WiFi · Volume · Time · Date
# Requires: Nerd Font, PipeWire/PulseAudio/ALSA, brightnessctl

# Load Tokyo Night colors
. ~/.config/chadwm/scripts/bar_themes/tokyonight

# Separator between modules
sep() { printf " ^c$grey^·^d^ "; }

# Battery indicator with charging state
battery() {
  bat="$(ls -d /sys/class/power_supply/BAT* 2>/dev/null | head -n1)" || return
  val="$(cat "$bat/capacity" 2>/dev/null)"
  status="$(cat "$bat/status" 2>/dev/null)"

  # Check if AC adapter is connected
  mains="$(ls -d /sys/class/power_supply/AC* /sys/class/power_supply/ADP* 2>/dev/null | head -n1)"
  online=""
  [ -n "$mains" ] && online="$(cat "$mains/online" 2>/dev/null)"

  charging=0
  [ "$status" = "Charging" ] || [ "$online" = "1" ] && charging=1

  # Icon and color based on state
  icon=""; col="$red"
  if [ "$charging" -eq 1 ]; then
    icon="󱐋"; col="$green"
  else
    if   [ "$val" -ge 80 ]; then icon=""; col="$blue"
    elif [ "$val" -ge 50 ]; then icon=""; col="$blue"
    elif [ "$val" -ge 30 ]; then icon=""; col="$blue"
    elif [ "$val" -ge 10 ]; then icon=""; col="$blue"
    else                        icon=""; col="$red"
    fi
  fi

  printf "^c$col^%s ^c$white^%s%s" "$icon" "$val" "^d^"
}

# RAM usage
mem() {
  used="$(free -h | awk '/^Mem/ {print $3}' | sed 's/i//')"
  printf "^c$blue^ ^c$white^%s%s" "$used" "^d^"
}

# WiFi status
wlan() {
  case "$(cat /sys/class/net/wl*/operstate 2>/dev/null)" in
    up)     printf "^c$blue^󰤨^d^" ;;
    down|*) printf "^c$grey^󰤭^d^" ;;
  esac
}

# Volume with mute detection (PipeWire → PulseAudio → ALSA fallback)
vol() {
  icon="󰕾"
  val="0"; muted=0

  # Try wpctl (PipeWire/WirePlumber)
  if command -v wpctl >/dev/null 2>&1; then
    out="$(wpctl get-volume @DEFAULT_AUDIO_SINK@ 2>/dev/null)"
    val=$(printf "%s" "$out" | awk '{print int($2*100)}')
    printf "%s" "$out" | grep -q '\[MUTED\]' && muted=1

  # Fallback to pamixer (PulseAudio)
  elif command -v pamixer >/dev/null 2>&1; then
    val="$(pamixer --get-volume 2>/dev/null)"
    [ "$(pamixer --get-mute 2>/dev/null)" = "true" ] && muted=1

  # Fallback to amixer (ALSA)
  elif command -v amixer >/dev/null 2>&1; then
    line="$(amixer get Master | tail -n1)"
    val=$(printf "%s" "$line" | awk -F'[][]' '{print $2}' | tr -d '%')
    [ "$(printf "%s" "$line" | awk -F'[][]' '{print $4}')" = "off" ] && muted=1

  else
    val="N/A"
  fi

  # Display muted or active volume
  if [ "$muted" -eq 1 ]; then
    printf "^c$red^󰝟 ^c$grey^%s%s" "$val" "^d^"
  else
    volcol="${magenta:-$blue}"
    printf "^c$volcol^%s ^c$white^%s%s" "$icon" "$val" "^d^"
  fi
}

# Time display
time_display() {
  printf "^c$blue^󱑆 ^c$white^%s^d^" "$(date '+%H:%M')"
}

# Date display
date_display() {
  printf "^c$white^%s^d^" "$(date '+%a %d %b')"
}

# Update loop (refresh every second)
counter=0
while true; do
  # Update fast-changing items every loop
  time_str="$(time_display)"
  vol_str="$(vol)"
  
  # Update slow-changing items every 5 seconds
  if [ $((counter % 5)) -eq 0 ]; then
    mem_str="$(mem)"
    bat_str="$(battery)"
    wifi_str="$(wlan)"
  fi
  
  xsetroot -name "  ${mem_str}$(sep)${bat_str}$(sep)${wifi_str}$(sep)${vol_str}$(sep)${time_str}$(sep)$(date_display)" 2>/dev/null
  
  counter=$((counter + 1))
  sleep 1
done
