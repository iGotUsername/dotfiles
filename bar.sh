#!/bin/dash
# chadwm minimal right status: RAM | BAT | WiFi | VOL | DATE/TIME

# Volume percentage + mute state (PipeWire -> Pulse -> ALSA)
#!/bin/dash
# chadwm status: RAM · Battery · WiFi · Volume · Time/Date (time first)
# no background blocks; tokyonight accents; clear mute icon
# requires a Nerd Font for the icons

# ^c$var^ = fg color
# ^d^     = reset to default colors

# load colors
. ~/.config/chadwm/scripts/bar_themes/tokyonight

# thin separator
sep() { printf " ^c$grey^·^d^ "; }

battery() {
  bat="$(ls -d /sys/class/power_supply/BAT* 2>/dev/null | head -n1)" || return
  val="$(cat "$bat/capacity" 2>/dev/null)"
  status="$(cat "$bat/status" 2>/dev/null)"

  mains="$(ls -d /sys/class/power_supply/AC* /sys/class/power_supply/ADP* 2>/dev/null | head -n1)"
  online=""
  [ -n "$mains" ] && online="$(cat "$mains/online" 2>/dev/null)"

  charging=0
  [ "$status" = "Charging" ] || [ "$online" = "1" ] && charging=1

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

mem() {
  used="$(free -h | awk '/^Mem/ {print $3}' | sed 's/i//')"
  printf "^c$blue^ ^c$white^%s%s" "$used" "^d^"
}

wlan() {
  case "$(cat /sys/class/net/wl*/operstate 2>/dev/null)" in
    up)     printf "^c$blue^󰤨^d^" ;;
    down|*) printf "^c$grey^󰤭^d^" ;;
  esac
}

# Volume with mute icon and colors (PipeWire -> Pulse -> ALSA)
vol() {
  icon="󰕾"  # default high (will adjust by level)
  val="0"; muted=0

  if command -v wpctl >/dev/null 2>&1; then
    out="$(wpctl get-volume @DEFAULT_AUDIO_SINK@ 2>/dev/null)"
    val=$(printf "%s" "$out" | awk '{print int($2*100)}')
    printf "%s" "$out" | grep -q '\[MUTED\]' && muted=1
  elif command -v pamixer >/dev/null 2>&1; then
    val="$(pamixer --get-volume 2>/dev/null)"
    [ "$(pamixer --get-mute 2>/dev/null)" = "true" ] && muted=1
  elif command -v amixer >/dev/null 2>&1; then
    line="$(amixer get Master | tail -n1)"
    val=$(printf "%s" "$line" | awk -F'[][]' '{print $2}' | tr -d '%')
    [ "$(printf "%s" "$line" | awk -F'[][]' '{print $4}')" = "off" ] && muted=1
  else
    val="N/A"
  fi

  if [ "$muted" -eq 1 ]; then
    # Muted: red mute icon + greyed percentage
    printf "^c$red^󰝟 ^c$grey^%s%s" "$val" "^d^"
  else
    # Unmuted: accent icon + white percentage
    volcol="${magenta:-$blue}"
    printf "^c$volcol^%s ^c$white^%s%s" "$icon" "$val" "^d^"
  fi
}

time_display() {
  printf "^c$blue^󱑆 ^c$white^%s^d^" "$(date '+%H:%M')"
}

date_display() {
  printf "^c$white^%s^d^" "$(date '+%a %d %b')"
}

while true; do
  xsetroot -name "  $(mem)$(sep)$(battery)$(sep)$(wlan)$(sep)$(vol)$(sep)$(time_display)$(sep)$(date_display)"
  sleep 1
done
