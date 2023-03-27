/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 5, .gappx = 5};
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const int focusonwheel       = 0;

static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=10" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=10";

static const char col_bg[]      = "#1a1b26";
static const char col_black[]   = "#32344a";
static const char col_fg[]      = "#a9b1d6";
static const char col_blue[]    = "#7aa2f7";

static const char *colors[][3]      = {
  /*                    fg         bg         border   */
  [SchemeNorm]      = { col_fg,    col_bg,    col_black },
  [SchemeSel]       = { col_bg,    col_blue,  col_blue  },
  [SchemeStatus]    = { col_fg,    col_bg,    "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
  [SchemeTagsSel]   = { col_bg,    col_blue,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
  [SchemeTagsNorm]  = { col_fg,    col_bg,    "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
  [SchemeInfoSel]   = { col_fg,    col_bg,    "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
  [SchemeInfoNorm]  = { col_fg,    col_bg,    "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

// const char *spterm1[]  = {"st", "-n", "spterm1", "-g", "120x34", NULL };
// const char *spterm2[]  = {"st", "-n", "spterm2", "-g", "120x34", NULL };
// const char *spfm[]     = {"st", "-n", "spfm", "-g", "144x41", "-e", "lf", NULL };

const char *spterm1[]  = {"alacritty", "--class", "spterm1", "-o", "window.dimensions.lines=30", "-o", "window.dimensions.columns=120", NULL };
const char *spterm2[]  = {"alacritty", "--class", "spterm2", "-o", "window.dimensions.lines=30", "-o", "window.dimensions.columns=120", NULL };
const char *spfm[]     = {"alacritty", "--class", "spfm", "-o", "window.dimensions.lines=45", "-o", "window.dimensions.columns=160", "-e", "lf", NULL };

static Sp scratchpads[] = {
  /* name          cmd  */
  {"spterm1",      spterm1},
  {"spterm2",      spterm2},
  {"spfm",         spfm},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                  instance    title           tags mask     isfloating    monitor */
	{ "Gimp",                 NULL,       NULL,           0,            1,            -1 },
	{ "firefox",              NULL,       NULL,           1,            0,            -1 },
  { "Brave-browser",        NULL,       NULL,           1,            0,            -1 },

  { "Ferdi",                NULL,       NULL,           1 << 9,       0,            -1 },

  { "1Password",            NULL,       NULL,           0,            1,            -1 },
  { NULL,                   NULL,       "pulsemixer",   0,            1,            -1 },
  { NULL,                   NULL,       "lf",           0,            1,            -1 },
  { NULL,                   NULL,       "htop",         0,            1,            -1 },

  // scratchpads
	/* class    instance      title   tags mask   isfloating    monitor */
	{ NULL,		  "spterm1",		NULL,		SPTAG(0),		1,			      -1 },
	{ NULL,		  "spterm2",		NULL,		SPTAG(1),		1,			      -1 },
	{ NULL,		  "spfm",	      NULL,		SPTAG(2),		1,			      -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
// TODO: Add setup for multiple monitors. Set the -m dmenumon parameter which should be updated
// in spawn() function to request dmenu to remnder on selected monitor. Currently the *-menu commands
// do not support passing the "-m" switch and therefore appropriate code was commented out in dwm.c.
// static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
// static const char *termcmd[]  = { "st", NULL };

// menu commands
static const char *drunmenucmd[]    = { "drun-menu", NULL };
static const char *runmenucmd[]     = { "run-menu", NULL };
static const char *sshotmenucmd[]   = { "sshot-menu", NULL };
static const char *pmenucmd[]       = { "power-menu", NULL };
static const char *linksmenucmd[]   = { "links-menu", NULL };

// volume control commands
static const char *upvolcmd[]       = { "volume", "up", NULL };
static const char *downvolcmd[]     = { "volume", "down", NULL };
static const char *togglmutecmd[]   = { "volume", "toggle", NULL };

// playback control
static const char *playpausecmd[]   = { "playerctl", "play-pause", NULL };
static const char *playnextcmd[]    = { "playerctl", "next", NULL };
static const char *playprevcmd[]    = { "playerctl", "previous", NULL };

// other commands
// static const char *termcmd[]        = { "st", NULL };
static const char *termcmd[]        = { "alacritty", NULL };
static const char *lockscreencmd[]  = { "lockscreen", NULL };

// apps
static const char *pmixercmd[]      = { "alacritty", "-e", "pulsemixer", NULL };
static const char *lfcmd[]          = { "alacritty", "-e", "lf", NULL };
static const char *browsercmd[]     = { "brave", NULL };
static const char *htopcmd[]        = { "st", "-e", "htop", NULL };
static const char *ferdicmd[]       = { "ferdi", NULL };
static const char *onepasswordcmd[] = { "1password", NULL };

#include "movestack.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  { MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
  { MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

  // menus
  { MODKEY,                       XK_p,      spawn,          {.v = drunmenucmd } },
  { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = runmenucmd } },
  { MODKEY,                       XK_s,      spawn,          {.v = sshotmenucmd } },
  { MODKEY,                       XK_x,      spawn,          {.v = pmenucmd } },
  { Mod1Mask,                     XK_l,      spawn,          {.v = linksmenucmd } },

  // volume control keybinding
  { 0,                            XF86XK_AudioRaiseVolume,    spawn,  {.v = upvolcmd } },
  { 0,                            XF86XK_AudioLowerVolume,    spawn,  {.v = downvolcmd } },
  { 0,                            XF86XK_AudioMute,           spawn,  {.v = togglmutecmd } },

  // playback keybindins
  { 0,                            XF86XK_AudioPlay,           spawn,  {.v = playpausecmd } },
  { 0,                            XF86XK_AudioNext,           spawn,  {.v = playnextcmd } },
  { 0,                            XF86XK_AudioPrev,           spawn,  {.v = playprevcmd } },

  // other keybindings
	{ MODKEY,                       XK_Return,  spawn,          {.v = termcmd } },
	{ ControlMask|Mod1Mask,         XK_l,       spawn,          {.v = lockscreencmd } },

  // app bindings
  { MODKEY|ControlMask,        XK_m,       spawn,      {.v = pmixercmd } },
  { MODKEY|ControlMask,        XK_l,       spawn,      {.v = lfcmd } },
  { MODKEY|ControlMask,        XK_b,       spawn,      {.v = browsercmd } },
  { MODKEY|ControlMask,        XK_t,       spawn,      {.v = htopcmd } },
  { MODKEY|ControlMask,        XK_f,       spawn,      {.v = ferdicmd } },
  { MODKEY|ControlMask,        XK_p,       spawn,      {.v = onepasswordcmd } },

  // scratchpad bindings
	{ MODKEY|ShiftMask,     		XK_u,  	 togglescratch,  {.ui = 0 } },
	{ MODKEY|ShiftMask,     		XK_i,	   togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,      		XK_o,	   togglescratch,  {.ui = 2 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
