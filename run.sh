#!/bin/sh

xrdb merge ~/.Xresources 
xbacklight -set 10 &
xset r rate 200 50 &
dash ~/.config/chadwm/scripts/bar.sh &
while type chadwm >/dev/null; do chadwm && continue || break; done
