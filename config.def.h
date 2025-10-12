/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* ========================================
 * APPEARANCE
 * ======================================== */

/* Window Borders & Gaps */
static const unsigned int borderpx  = 0;        /* Border width around windows */
static const unsigned int default_border = 0;   /* Default border to revert to */
static const unsigned int snap      = 32;       /* Snap pixel threshold */
static const unsigned int gappih    = 7;        /* Horizontal inner gap between windows */
static const unsigned int gappiv    = 7;        /* Vertical inner gap between windows */
static const unsigned int gappoh    = 7;        /* Horizontal outer gap (screen edge) */
static const unsigned int gappov    = 7;        /* Vertical outer gap (screen edge) */
static const int smartgaps          = 0;        /* 1 = no outer gap with single window */

/* System Tray */
static const unsigned int systraypinning = 0;   /* 0 = follow selected monitor, >0 = pin to monitor X */
static const unsigned int systrayspacing = 8;   /* Space between tray icons */
static const unsigned int systrayiconsize = 20; /* Tray icon size in pixels */
static const int systraypinningfailfirst = 1;   /* 1 = fallback to first monitor, 0 = last monitor */
static const int showsystray        = 1;        /* 0 = hide systray */

/* Status Bar */
static const int showbar            = 1;        /* 0 = hide bar */
static const int showtab            = showtab_auto;
static const int toptab             = 1;        /* 0 = bottom tab bar */
static const int floatbar           = 1;        /* 1 = floating bar (no padding) */
static const int topbar             = 1;        /* 0 = bottom bar */
static const int horizpadbar        = 20;       /* Horizontal bar padding */
static const int vertpadbar         = 11;       /* Vertical bar padding */
static const int vertpadtab         = 35;       /* Vertical tab padding */
static const int horizpadtabi       = 15;       /* Horizontal inner tab padding */
static const int horizpadtabo       = 15;       /* Horizontal outer tab padding */
static const int scalepreview       = 4;        /* Tag preview scaling factor */
static const int tag_preview        = 0;        /* 1 = enable tag previews */
static const int colorfultag        = 1;        /* 0 = use SchemeSel for all active tags */

/* Hardware Control Paths */
static const char *light_up[]   = { "/usr/bin/brightnessctl", "set", "5%+", NULL };
static const char *light_down[] = { "/usr/bin/brightnessctl", "set", "5%-", NULL };

/* Window Behavior */
static const int new_window_attach_on_end = 0;  /* 1 = new windows attach at end, 0 = at front */

/* Icon Settings */
#define ICONSIZE 19       /* Window icon size */
#define ICONSPACING 10    /* Space between icon and title */

/* Font */
static const char *fonts[] = {
    "Iosevka:style:medium:size=11",
    "JetBrainsMono Nerd Font Mono:style:medium:size=21"
};

/* ========================================
 * COLORS (Tokyo Night Theme)
 * ======================================== */

#include "themes/tokyonight.h"

static const char *colors[][3] = {
    /*                     fg       bg      border */
    [SchemeNorm]       = { gray3,   black,  gray2 },     /* Unfocused windows */
    [SchemeSel]        = { gray4,   blue,   gray3 },     /* Focused window */
    [SchemeTitle]      = { white,   black,  black },     /* Active window title */
    [TabSel]           = { blue,    gray2,  black },     /* Selected tab */
    [TabNorm]          = { gray3,   black,  black },     /* Normal tab */
    [SchemeTag]        = { gray2,   black,  black },     /* Tag base */
    [SchemeTag1]       = { gray3,   black,  black },     /* Tag 1 */
    [SchemeTag2]       = { gray3,   black,  black },     /* Tag 2 */
    [SchemeTag3]       = { gray3,   black,  black },     /* Tag 3 */
    [SchemeTag4]       = { gray3,   black,  black },     /* Tag 4 */
    [SchemeTag5]       = { gray3,   black,  black },     /* Tag 5 */
    [SchemeLayout]     = { gray3,   black,  black },     /* Layout indicator */
    [SchemeBtnPrev]    = { gray3,   black,  black },     /* Previous button */
    [SchemeBtnNext]    = { yellow,  black,  black },     /* Next button */
    [SchemeBtnClose]   = { red,     black,  black },     /* Close button */
};

/* ========================================
 * WORKSPACES (Tags)
 * ======================================== */

static char *tags[] = {"󰣨", "", "", "", ""};

static const Launcher launchers[] = {
    /* No external launchers - using bar.sh script */
    { NULL } /* Dummy element to prevent empty array */
};

static const int tagschemes[] = {
    SchemeTag1, SchemeTag2, SchemeTag3, SchemeTag4, SchemeTag5
};

/* Tag Underline Styling */
static const unsigned int ulinepad      = 5;  /* Padding between underline and tag */
static const unsigned int ulinestroke   = 2;  /* Underline thickness */
static const unsigned int ulinevoffset  = 0;  /* Vertical offset from bar bottom */
static const int ulineall               = 0;  /* 1 = underline all tags, 0 = active only */

/* ========================================
 * WINDOW RULES
 * Format: { "class", "instance", "title", tags_mask, iscentered, isfloating, monitor }
 * 
 * - tags_mask: 0 = current, 1<<0 = tag1, 1<<1 = tag2, etc.
 * - iscentered: 1 = center window, 0 = normal placement
 * - isfloating: 1 = floating, 0 = tiled
 * - monitor: -1 = current, 0+ = specific monitor
 * 
 * Use `xprop` to find window class/instance
 * ======================================== */

static const Rule rules[] = {
    /* class         instance    title       tags mask     centered   floating   monitor */
    { "Gimp",        NULL,       NULL,       0,            0,         1,         -1 },
    { "Firefox",     NULL,       NULL,       1 << 8,       0,         0,         -1 },
    { "mpv",         NULL,       NULL,       0,            1,         1,         -1 },
    { "feh",         NULL,       NULL,       0,            1,         1,         -1 },
};

/* ========================================
 * LAYOUTS
 * ======================================== */

static const float mfact     = 0.50;  /* Master area size ratio [0.05..0.95] */
static const int nmaster     = 1;     /* Number of clients in master area */
static const int resizehints = 0;     /* 1 = respect size hints in tiled mode */
static const int lockfullscreen = 1;  /* 1 = force focus on fullscreen window */

#define FORCE_VSPLIT 1  /* Force vertical split for 2 clients in nrowgrid */
#include "functions.h"

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },                    /* Master + stack */
    { "[M]",      monocle },                 /* All windows fullscreen */
    { "[@]",      spiral },                  /* Fibonacci spiral */
    { "[\\]",     dwindle },                 /* Fibonacci dwindle */
    { "H[]",      deck },                    /* Master + deck */
    { "TTT",      bstack },                  /* Bottom stack */
    { "===",      bstackhoriz },             /* Horizontal bottom stack */
    { "HHH",      grid },                    /* Grid layout */
    { "###",      nrowgrid },                /* N-row grid */
    { "---",      horizgrid },               /* Horizontal grid */
    { ":::",      gaplessgrid },             /* Gapless grid */
    { "|M|",      centeredmaster },          /* Centered master */
    { ">M>",      centeredfloatingmaster },  /* Centered floating master */
    { "><>",      NULL },                    /* Floating mode */
    { NULL,       NULL },
};

/* ========================================
 * KEYBINDINGS
 * ======================================== */

#define MODKEY Mod4Mask  /* Super/Windows key */

/* Tag switching macro */
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* Shell command helper */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const Key keys[] = {
    /* modifier                     key                         function        argument */

    /* Hardware Controls (Laptop Function Keys) */
    { 0, XF86XK_AudioRaiseVolume,  spawn, SHCMD("wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ 5%+") },
    { 0, XF86XK_AudioLowerVolume,  spawn, SHCMD("wpctl set-volume -l 1.0 @DEFAULT_AUDIO_SINK@ 5%-") },
    { 0, XF86XK_AudioMute,         spawn, SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle") },
    { 0, XF86XK_MonBrightnessUp,   spawn, {.v = light_up} },
    { 0, XF86XK_MonBrightnessDown, spawn, {.v = light_down} },

    /* Screenshots */
    { MODKEY|ControlMask, XK_u, spawn, SHCMD("maim | xclip -selection clipboard -t image/png") },          /* Fullscreen */
    { MODKEY,             XK_u, spawn, SHCMD("maim --select | xclip -selection clipboard -t image/png") }, /* Selection */

    /* Application Launchers */
    { MODKEY, XK_c,      spawn, SHCMD("rofi -show drun") },  /* App launcher */
    { MODKEY, XK_Return, spawn, SHCMD("alacritty") },        /* Terminal */

    /* Window/Bar Toggles */
    { MODKEY,              XK_b,     togglebar,      {0} },            /* Toggle status bar */
    { MODKEY|ControlMask,  XK_t,     togglegaps,     {0} },            /* Toggle gaps */
    { MODKEY|ShiftMask,    XK_space, togglefloating, {0} },            /* Toggle floating */
    { MODKEY,              XK_f,     togglefullscr,  {0} },            /* Toggle fullscreen */

    /* Window Focus */
    { MODKEY|ControlMask, XK_w, tabmode,     { -1 } },      /* Tab mode */
    { MODKEY,             XK_j, focusstack,  {.i = +1 } },  /* Focus next window */
    { MODKEY,             XK_k, focusstack,  {.i = -1 } },  /* Focus previous window */
    { MODKEY,             XK_i, incnmaster,  {.i = +1 } },  /* Increase master count */
    { MODKEY,             XK_d, incnmaster,  {.i = -1 } },  /* Decrease master count */

    /* Workspace Navigation */
    { MODKEY, XK_Left,  shiftview, {.i = -1 } },  /* Previous tag */
    { MODKEY, XK_Right, shiftview, {.i = +1 } },  /* Next tag */

    /* Master/Client Area Sizing */
    { MODKEY,              XK_h, setmfact, {.f = -0.05} },  /* Shrink master */
    { MODKEY,              XK_l, setmfact, {.f = +0.05} },  /* Grow master */
    { MODKEY|ShiftMask,    XK_h, setcfact, {.f = +0.25} },  /* Grow client */
    { MODKEY|ShiftMask,    XK_l, setcfact, {.f = -0.25} },  /* Shrink client */
    { MODKEY|ShiftMask,    XK_o, setcfact, {.f =  0.00} },  /* Reset client size */

    /* Window Stack Movement */
    { MODKEY|ShiftMask, XK_j,      movestack, {.i = +1 } },  /* Move window down */
    { MODKEY|ShiftMask, XK_k,      movestack, {.i = -1 } },  /* Move window up */
    { MODKEY|ShiftMask, XK_Return, zoom,      {0} },         /* Swap with master */
    { MODKEY,           XK_Tab,    view,      {0} },         /* Toggle last tag */

    /* Gap Adjustments */
    { MODKEY|ControlMask,           XK_i, incrgaps,  {.i = +1 } },  /* Increase all gaps */
    { MODKEY|ControlMask,           XK_d, incrgaps,  {.i = -1 } },  /* Decrease all gaps */
    { MODKEY|ShiftMask,             XK_i, incrigaps, {.i = +1 } },  /* Increase inner gaps */
    { MODKEY|ControlMask|ShiftMask, XK_i, incrigaps, {.i = -1 } },  /* Decrease inner gaps */
    { MODKEY|ControlMask,           XK_o, incrogaps, {.i = +1 } },  /* Increase outer gaps */
    { MODKEY|ControlMask|ShiftMask, XK_o, incrogaps, {.i = -1 } },  /* Decrease outer gaps */

    /* Directional Gap Adjustments */
    { MODKEY|ControlMask,           XK_6, incrihgaps, {.i = +1 } },  /* Inner horizontal + */
    { MODKEY|ControlMask|ShiftMask, XK_6, incrihgaps, {.i = -1 } },  /* Inner horizontal - */
    { MODKEY|ControlMask,           XK_7, incrivgaps, {.i = +1 } },  /* Inner vertical + */
    { MODKEY|ControlMask|ShiftMask, XK_7, incrivgaps, {.i = -1 } },  /* Inner vertical - */
    { MODKEY|ControlMask,           XK_8, incrohgaps, {.i = +1 } },  /* Outer horizontal + */
    { MODKEY|ControlMask|ShiftMask, XK_8, incrohgaps, {.i = -1 } },  /* Outer horizontal - */
    { MODKEY|ControlMask,           XK_9, incrovgaps, {.i = +1 } },  /* Outer vertical + */
    { MODKEY|ControlMask|ShiftMask, XK_9, incrovgaps, {.i = -1 } },  /* Outer vertical - */
    { MODKEY|ControlMask|ShiftMask, XK_d, defaultgaps, {0} },        /* Reset to default gaps */

    /* Layout Selection */
    { MODKEY,                       XK_t,      setlayout, {.v = &layouts[0]} },   /* Tile */
    { MODKEY|ShiftMask,             XK_f,      setlayout, {.v = &layouts[1]} },   /* Monocle */
    { MODKEY,                       XK_m,      setlayout, {.v = &layouts[2]} },   /* Spiral */
    { MODKEY|ControlMask,           XK_g,      setlayout, {.v = &layouts[10]} },  /* Gapless grid */
    { MODKEY|ControlMask|ShiftMask, XK_t,      setlayout, {.v = &layouts[13]} },  /* Floating */
    { MODKEY,                       XK_space,  setlayout, {0} },                  /* Toggle last layout */
    { MODKEY|ControlMask,           XK_comma,  cyclelayout, {.i = -1 } },         /* Previous layout */
    { MODKEY|ControlMask,           XK_period, cyclelayout, {.i = +1 } },         /* Next layout */

    /* Multi-Monitor */
    { MODKEY,              XK_0,      view,     {.ui = ~0 } },   /* View all tags */
    { MODKEY|ShiftMask,    XK_0,      tag,      {.ui = ~0 } },   /* Tag on all */
    { MODKEY,              XK_comma,  focusmon, {.i = -1 } },    /* Focus previous monitor */
    { MODKEY,              XK_period, focusmon, {.i = +1 } },    /* Focus next monitor */
    { MODKEY|ShiftMask,    XK_comma,  tagmon,   {.i = -1 } },    /* Send to previous monitor */
    { MODKEY|ShiftMask,    XK_period, tagmon,   {.i = +1 } },    /* Send to next monitor */

    /* Border Size */
    { MODKEY|ShiftMask, XK_minus, setborderpx, {.i = -1 } },            /* Decrease border */
    { MODKEY|ShiftMask, XK_p,     setborderpx, {.i = +1 } },            /* Increase border */
    { MODKEY|ShiftMask, XK_w,     setborderpx, {.i = default_border } }, /* Reset border */

    /* System Controls */
    { MODKEY|ControlMask, XK_q, spawn,   SHCMD("killall bar.sh chadwm") },  /* Quit DWM */
    { MODKEY,             XK_q, killclient, {0} },                           /* Close window */
    { MODKEY|ShiftMask,   XK_r, restart,    {0} },                           /* Restart DWM */

    /* Window Hiding (Scratchpad) */
    { MODKEY,          XK_e, hidewin,    {0} },  /* Hide window */
    { MODKEY|ShiftMask, XK_e, restorewin, {0} },  /* Restore hidden window */

    /* Workspace (Tag) Keybinds */
    TAGKEYS(XK_1, 0)
    TAGKEYS(XK_2, 1)
    TAGKEYS(XK_3, 2)
    TAGKEYS(XK_4, 3)
    TAGKEYS(XK_5, 4)
    TAGKEYS(XK_6, 5)
    TAGKEYS(XK_7, 6)
    TAGKEYS(XK_8, 7)
    TAGKEYS(XK_9, 8)
};

/* ========================================
 * MOUSE BINDINGS
 * ======================================== */

static const Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          SHCMD("st") },

    /* Window Dragging/Resizing
     * placemouse modes:
     *   0 = tiled position relative to cursor
     *   1 = tiled position relative to window center
     *   2 = cursor warps to window center
     */
    { ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkClientWin,         ControlMask,    Button1,        dragmfact,      {0} },
    { ClkClientWin,         ControlMask,    Button3,        dragcfact,      {0} },

    /* Tag Bar Clicks */
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },

    /* Tab Bar Controls */
    { ClkTabBar,            0,              Button1,        focuswin,       {0} },
    { ClkTabPrev,           0,              Button1,        movestack,      { .i = -1 } },
    { ClkTabNext,           0,              Button1,        movestack,      { .i = +1 } },
    { ClkTabClose,          0,              Button1,        killclient,     {0} },
};
