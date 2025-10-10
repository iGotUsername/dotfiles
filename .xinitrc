#!/bin/sh
pipewire &
wireplumber &
pipewire-pulse &
feh --bg-fill ~/.config/chadwm/wallpapers/mistyroad.jpg
picom -b --config ~/.config/picom/picom.conf &
exec ~/.config/chadwm/scripts/run.sh
