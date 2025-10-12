#!/bin/sh
# DWM startup script - launches compositor and status bar

xrdb merge ~/.Xresources          # Load X resources (fonts, colors, etc.)
xset r rate 200 50 &              # Set keyboard repeat rate (200ms delay, 50/sec)
dash ~/.config/chadwm/scripts/bar.sh &  # Launch status bar script
picom -b --config ~/.config/picom/picom.conf & # Launch picom compositor
while type chadwm >/dev/null; do chadwm && continue || break; done  # Restart DWM on crash
