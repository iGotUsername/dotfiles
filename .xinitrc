#!/bin/sh

pipewire &
sleep 0.5
wireplumber &
pipewire-pulse &
xset s off
xset -dpms
xset dpms 0 0 0
feh --bg-fill ~/.config/chadwm/wallpapers/mistyroad.jpg
exec ~/.config/chadwm/scripts/run.sh
