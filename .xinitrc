#!/bin/sh

pipewire &
wireplumber &
pipewire-pulse &
feh --bg-fill ~/.config/chadwm/wallpapers/mistyroad.jpg
exec ~/.config/chadwm/scripts/run.sh
