#!/bin/sh
pipewire &
sleep 0.7
wireplumber &
pipewire-pulse &
feh --bg-fill ~/.config/chadwm/wallpapers/lamps.jpg
picom -b --config ~/.config/picom/picom.conf &
exec ~/.config/chadwm/scripts/run.sh
