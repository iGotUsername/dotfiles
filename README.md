# iGotUsername's ChadWM Dotfiles

Personal [ChadWM](https://github.com/siduck/chadwm) rice featuring Tokyo Night colorscheme with custom status bar and window animations.


## Features

- **Tokyo Night** theme across all components
- Custom **dash-based status bar** (RAM · Battery · WiFi · Volume · Time · Date)
- **Picom** compositor with animations, rounded corners, and shadows
- **Rofi** application launcher with matching theme
- **Alacritty** terminal with transparency
- Hardware key support (brightness, volume control)
- Screenshot utilities (fullscreen & selection)
- 5 workspace setup with minimal gaps


## Core Dependencies

- chadwm
- alacritty
- rofi
- picom
- dash


## Utilities

- `brightnessctl` - Brightness control
- `maim` - Screenshots
- `xclip` - Clipboard support
- `wireplumber` - Audio control (wpctl)
- `xsetroot` - Status bar rendering


## Fonts

- ttf-jetbrains-mono-nerd


## Install

1. git clone https://github.com/iGotUsername/dotfiles ~/
2. cd ~/dotfiles
3. chmod +x scripts/*
4. ./scripts/push (or move manually)
5. Recompile chadwm


## Usage

Deploy changes in dotfiles with
- ./scripts/push

Backup current config installed with
- ./scripts/pull


## Credits

- **ChadWM**: Based on [siduck's chadwm](https://github.com/siduck/chadwm)
- **Tokyo Night Theme**: Color scheme by [tokyo-night](https://github.com/enkia/tokyo-night-vscode-theme)
- **Documentation**: README structure and configuration explanations created with assistance from Claude (Anthropic)
- **Code**: Significant portions generated with AI assistance (Claude Sonnet 4.5), then reviewed, corrected, tested, and validated by me
- **Additional Sources**: This project may incorporate techniques, snippets, or inspiration from other sources not explicitly documented here. If you recognize uncredited work, please contact me.
 

## Info

- If you have issues with my scripts, simply edit them to match your file structure.
- This was made with my exact build in mind, incompatibility is expected.
