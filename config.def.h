/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 7;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 7;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"monospace:style=Bold:size=8"};
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#191d21";
static const char col_gray2[]       = "#343e47";
static const char col_gray3[]       = "#979ead";
static const char col_gray4[]       = "#acb2bf";
/* static const char col_cyan[]        = "#005577"; */
static const char col_cyan[]        = "#004777";
static const char col_blue[]        = "#566faf";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_blue  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance            title   tags mask   isfloating  monitor */
	{ "firefox",    "Navigator",        NULL,   1 << 1,     0,          -1 },
	{ "mpv",        "gl",               NULL,   1 << 3,     1,          -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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
static char dmenulines[] = "13";
static char dmenuprompt[] = "run:";
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-i", "-l", dmenulines, "-p", 
                                dmenuprompt, "-m", dmenumon, "-fn", dmenufont,
                                "-nb", col_gray1, "-nf", col_gray3, "-sb", 
                                col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "urxvt", "-title", scratchpadname, "-geometry", "100x28", NULL };

#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key                 function            argument */
	{ MODKEY,                       XK_d,               spawn,              {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,          spawn,              {.v = termcmd } },
 	{ MODKEY,                       XK_grave,           togglescratch,      {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_b,               togglebar,          {0} },
	{ MODKEY,                       XK_j,               focusstack,         {.i = +1 } },
	{ MODKEY,                       XK_k,               focusstack,         {.i = -1 } },
	{ MODKEY,                       XK_i,               incnmaster,         {.i = +1 } },
	{ MODKEY,                       XK_p,               incnmaster,         {.i = -1 } },
	{ MODKEY,                       XK_h,               setmfact,           {.f = -0.05} },
	{ MODKEY,                       XK_l,               setmfact,           {.f = +0.05} },
	{ MODKEY,                       XK_space,           zoom,               {0} },
	{ MODKEY,                       XK_Tab,             view,               {0} },
	{ MODKEY,                       XK_q,               killclient,         {0} },
	{ MODKEY,                       XK_t,               setlayout,          {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,               setlayout,          {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,               setlayout,          {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_Return,          setlayout,          {0} },
	{ MODKEY|ShiftMask,             XK_space,           togglefloating,     {0} },
	{ MODKEY,                       XK_s,               togglesticky,       {0} },
	{ MODKEY,                       XK_f,               togglefullscr,      {0} },
	{ MODKEY,                       XK_0,               view,               {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,               tag,                {.ui = ~0 } },
	{ MODKEY,                       XK_comma,           focusmon,           {.i = -1 } },
	{ MODKEY,                       XK_period,          focusmon,           {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,           tagmon,             {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,          tagmon,             {.i = +1 } },
    { MODKEY,                       XK_g,               shiftview,          {.i = -1 } },
    { MODKEY,                       XK_semicolon,       shiftview,          {.i = +1 } },
	TAGKEYS(                        XK_1,                                   0)
	TAGKEYS(                        XK_2,                                   1)
	TAGKEYS(                        XK_3,                                   2)
	TAGKEYS(                        XK_4,                                   3)
	TAGKEYS(                        XK_5,                                   4)
	TAGKEYS(                        XK_6,                                   5)
	TAGKEYS(                        XK_7,                                   6)
	TAGKEYS(                        XK_8,                                   7)
	TAGKEYS(                        XK_9,                                   8)
	{ MODKEY|ShiftMask,             XK_q,               quit,               {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkTagBar,		    0,		        Button4,	    shiftview,	    {.i = -1} },
	{ ClkTagBar,		    0,		        Button5,	    shiftview,	    {.i = 1} },
};
