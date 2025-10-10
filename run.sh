#!/bin/sh

xrdb merge ~/.Xresources 
xbacklight -set 10 &
feh --bg-fill ~/Pictures/wall/gruv.png &
xset r rate 200 50 &
picom --config $HOME/.config/picom/picom.conf --experimental-backends &
dash ~/.config/chadwm/scripts/bar.sh &
while type chadwm >/dev/null; do chadwm && continue || break; done
