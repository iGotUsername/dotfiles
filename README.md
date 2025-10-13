# iGotUsername's ChadWM Dotfiles

A clean, minimalist ChadWM configuration featuring the Tokyo Night colorscheme, custom status bar, and smooth window animations.
Screenshots

## Screenshots

![Desktop with Rofi](screenshots/rofi.png)
![Desktop rice](screenshots/rice.png)
![Editing configs](screenshots/work.png)


## Features

*   Tokyo Night colorscheme across all components
*   Custom status bar - RAM · Battery · WiFi · Volume · Time · Date (dash-based, minimal overhead)
*   Picom compositor - Smooth animations, rounded corners, and elegant shadows
*   Rofi launcher - Fast application menu with matching theme
*   Alacritty terminal - GPU-accelerated with transparency support
*   Hardware keys - Brightness and volume controls (laptop-friendly)
*   Screenshot utilities - Fullscreen and selection capture to clipboard
*   5 workspaces - Clean layout with minimal gaps


## Prerequisites

*   ChadWM must be installed first - Follow the official installation guide: https://github.com/siduck/chadwm#setup


## Core Components

*   chadwm
*   alacritty
*   rofi
*   picom
*   dash


## System Utilities

*   brightnessctl (Brightness control)
*   maim (Screenshot capture)
*   xclip (Clipboard management)
*   wireplumber (Audio control via wpctl)
*   xsetroot (Status bar rendering)


## Fonts

*   ttf-jetbrains-mono-nerd


## Installation

**WARNING:** Backup your existing configs before proceeding! The deployment script will overwrite files without confirmation.

1.  Clone the repository
    ```bash
    git clone https://github.com/iGotUsername/dotfiles ~/dotfiles
    ```

2.  Navigate to directory
    ```bash
    cd ~/dotfiles
    ```

3.  Make scripts executable
    ```bash
    chmod +x scripts/*
    ```

4.  Deploy dotfiles to your system (or do manually)
    ```bash
    ./scripts/push
    ```

5.  Recompile ChadWM
    ```bash
    cd ~/.config/chadwm
    ```


## Usage

*   Deploy Changes:
    After editing files in ~/dotfiles/, sync them to your system:
    ./scripts/push

*   Backup Current Config:
    Pull your current system configs into the dotfiles directory:
    ./scripts/pull


## File Structure

    ~/dotfiles/
    ├── scripts/
    │ ├── push (Deploy dotfiles to system)
    │ └── pull (Backup system to dotfiles)
    ├── config.def.h (DWM window manager configuration)
    ├── picom.conf (Compositor settings - animations, shadows)
    ├── alacritty.toml (Terminal emulator config)
    ├── config.rasi (Rofi launcher theme)
    ├── bar.sh (Status bar script)
    ├── run.sh (DWM startup script)
    ├── tokyonight.h (DWM color definitions)
    └── tokyonight (Status bar colors)


## Keybindings available in config.def.h

*   Should be the same as ChadWM. If not, take a look in config.def.h for confirmation.


## Troubleshooting

> [!TIP]
> *   Scripts don't work?
>     Ensure paths in scripts/push and scripts/pull match your file structure
>     Check script permissions: chmod +x scripts/*

> [!TIP]
>*   Status bar not showing?
>    Verify dash is installed: which dash
>    Check bar.sh has execute permissions
>    Ensure required utilities are installed (see Dependencies)

> [!TIP]
>*   Picom animations laggy?
>    Your GPU may not support the features. Maybe try another backend in picom.conf
>    Disable animations: comment out animations = true; 


## Incompatibility issues?

*   These dotfiles are tailored to my specific setup. Minor adjustments may be needed for different systems or ChadWM versions.


## Credits

*   ChadWM: Based on siduck's chadwm (https://github.com/siduck/chadwm)

*   Tokyo Night Theme: Color scheme by enkia (https://github.com/enkia/tokyo-night-vscode-theme)

*   Documentation: README structure created with assistance from Claude (Anthropic)

*   Code: Significant portions generated with AI assistance (Claude Sonnet 4.5), then reviewed, tested, and validated by me

*   Community: Inspiration from countless dotfiles repos and r/unixporn

If you recognize uncredited work, please open an issue so I can properly attribute it.


## License

*MIT License - Feel free to use and modify as you wish.*
