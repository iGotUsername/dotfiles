# ~/.config/chadwm/scripts/run.sh
#!/bin/sh
set -eu

[ -f "$HOME/.Xresources" ] && xrdb -merge "$HOME/.Xresources"
xset r rate 200 50 &

# Launch bar and picom
"$HOME/.config/chadwm/scripts/bar.sh" & bar_pid=$!
trap 'kill "$bar_pid" 2>/dev/null || true' EXIT

picom -b --config "$HOME/.config/picom/picom.conf"

# Restart loop (quiet)
while command -v chadwm >/dev/null 2>&1; do
  chadwm && break || sleep 1
done
