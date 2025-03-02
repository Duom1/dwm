/* See LICENSE file for copyright and license details. */

#define PrintScreen 0x0000ff61
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const int startwithgaps = 1;     /* 1 means gaps are used by default */
static const unsigned int gappx = 0; /* default gap between windows in pixels */
static const int vertpad = 0;        /* vertical padding of bar */
static const int sidepad = 0;        /* horizontal padding of bar */
static const unsigned int snap = 32; /* snap pixel */
static const int showbar = 1;        /* 0 means no bar */
static const int topbar = 1;         /* 0 means bottom bar */
static const char *fonts[] = {"JetBrainsMono Nerd Font:size=10:antialias=true"};
#include "/home/user/.cache/wal/colors-wal-dwm.h"
/* static const char dmenufont[]       = "JetBrainsMono Nerf Font Mono:size=10";
 */
/* static const char col_gray1[]       = "#222222"; */
/* static const char col_gray2[]       = "#444444"; */
/* static const char col_gray3[]       = "#bbbbbb"; */
/* static const char col_gray4[]       = "#eeeeee"; */
/* static const char col_cyan[]        = "#00a9da"; */
/* static const char *colors[][3]      = { */
/* 	/1*               fg         bg         border   *1/ */
/* 	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 }, */
/* 	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  }, */
/* }; */

/* tagging */
static const char *tags[] = {"", "1", "2", "3", "4",
                             "5",   "6", "7", "8", "9"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 0, -1},
    /* { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 }, */
};

/* layout(s) */
static const float mfact = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;   /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
/* static const char *dmenucmd[]               = { "dmenu_run", "-m", dmenumon,
 * "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf",
 * col_gray4, NULL }; */
static const char *dmenucmd[] = {"rofi", "-show", "drun", NULL};
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
/* static const char *termcmd[]                = { "tabbed", "-c", "-r", "2",
 * "st", "-w", "''", NULL }; */
static const char *termcmd[] = {"st", NULL};
static const char *lock[] = {"/home/user/lock.sh", NULL};
static const char screenshot_command[] =
    "maim | xclip -selection clipboard -t image/png";
static const char screenshot_area_command[] =
    "maim -s | xclip -selection clipboard -t image/png";
static const char *br_up_command[] = {"brightnessctl", "set", "10%+", NULL};
static const char *br_down_command[] = {"brightnessctl", "set", "10%-", NULL};
static const char *power_menu[] = {
    "rofi", "-show", "power-menu", "-modi", "power-menu:rofi-power-menu", NULL};

static const Key keys[] = {
    /* modifier          key                             function argument */
    {0, XF86XK_MonBrightnessUp, spawn, {.v = br_up_command}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = br_down_command}},
    {ShiftMask, PrintScreen, spawn, SHCMD(screenshot_area_command)},
    {0, PrintScreen, spawn, SHCMD(screenshot_command)},
    {MODKEY, XK_BackSpace, spawn, {.v = power_menu}},

    /* modifier                     key        function        argument */
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_l, spawn, {.v = lock}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY, XK_minus, setgaps, {.i = -5}},
    {MODKEY, XK_equal, setgaps, {.i = +5}},
    {MODKEY | ShiftMask, XK_minus, setgaps, {.i = GAP_RESET}},
    {MODKEY | ShiftMask, XK_equal, setgaps, {.i = GAP_TOGGLE}},
    TAGKEYS(XK_1, 1) TAGKEYS(XK_2, 2) TAGKEYS(XK_3, 3) TAGKEYS(XK_4, 4)
        TAGKEYS(XK_5, 5) TAGKEYS(XK_6, 6) TAGKEYS(XK_7, 7) TAGKEYS(XK_8, 8)
            TAGKEYS(XK_9, 9){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
