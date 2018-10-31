/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2;       /* border pixel of windows */
static const unsigned int snap     = 32;      /* snap pixel */
static const unsigned int minwsz   = 1;       /* minimal height of a client for smfact */
static const unsigned int gappx    = 5;       /* gap pixel between windows */
static const int showbar           = 1;       /* 0 means no bar */
static const int topbar            = 1;       /* 0 means bottom bar */
static const char *fonts[]         = { "dina:size=8", "Wuncon Siji:size=8" };
static const char dmenufont[]      = "dina:size=8";

/* colors sourced from Xresources values */
#define NORFG "foreground"
#define NORBG "color8"
#define SELFG "color15"
#define SELBG "background"
#define URGENT "color1"

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Firefox",  "Places",   NULL,       0,            1,           -1 },
	{ "Firefox",  "Browser",  NULL,       0,            1,           -1 },
	{ "Icecat",   NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Icecat",   "Places",   NULL,       0,            1,           -1 },
	{ "Icecat",   "Browser",  NULL,       0,            1,           -1 },
	{ "Java",     NULL,       NULL,       0,            1,           -1 },
	{ "Eclipse",  NULL,       NULL,       1 << 6,       0,           -1 },
	{ "Lxappearance",NULL,    NULL,       0,            1,           -1 },
	{ "com-intellij-rt-execution-application-AppMain",
	              NULL,       NULL,       0,            1,           -1 },
	{ "Quartus",  NULL,       NULL,       1 << 7,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.45; /* factor of master area size [0.05..0.95] */
static const float smfact    = 0.00; /* factor of tiled clients [0.00..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol        arrange function */
	{ "右/振り",    rtile },    /* first entry is default */
	{ "左/振り",    ltile },
	{ "/振り",      NULL },    /* no layout function means floating behavior */
	{ "[M]/振り",    monocle },
	{ "/振り",      bstack },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      comboview,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      combotag,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0";
static const char *dmenucmd[]     = { "dmenu_run_recent.sh", NULL };
static const char *termcmd[]      = { "urxvtc", NULL };
static const char *nmcmd[]        = { "networkmanager_dmenu", NULL };
static const char *lockcmd[]      = { "lockscreen.sh", NULL};
static const char *suscmd[]       = { "systemctl", "suspend", NULL };
static const char *mutecmd[]      = { "pulseaudio-ctl.sh", "mute", NULL };
static const char *muteincmd[]    = { "pulseaudio-ctl.sh", "mute-input", NULL };
static const char *volucmd[]      = { "pulseaudio-ctl.sh", "up", NULL };
static const char *voldcmd[]      = { "pulseaudio-ctl.sh", "down", NULL };
static const char *otogglecmd[]   = { "output-toggle.sh", NULL };
static const char *ssucmd[]       = { "upload.sh", NULL };
static const char *ssccmd[]       = { "upload.sh", "-c", NULL };
static const char *brightup10[]   = { "bright.sh", "+", "10", NULL };
static const char *brightdown10[] = { "bright.sh", "-", "10", NULL };
static const char *brightup1[]    = { "bright.sh", "+", "1", NULL };
static const char *brightdown1[]  = { "bright.sh", "-", "1", NULL };
static const char *blankoff[]     = { "blank.sh", "-off", NULL };
static const char *blankon[]      = { "blank.sh", "-on", NULL };
static const char *pmenucmd[]     = { "passmenu", NULL };
static const char *recompile[]    = { "redwm.sh", NULL };
static const char *patchcolors[]  = { "recolor.sh", "--fast", NULL };
static const char *nightcmd[]     = { "night.sh", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,                            0xff61,    spawn,          {.v = ssucmd } },
	{ ControlMask,                  0xff61,    spawn,          {.v = ssccmd } },
	{ 0,                            0x1008ff12,spawn,          {.v = mutecmd } },
	{ 0,                            0x1008ffb2,spawn,          {.v = muteincmd } },
	{ ControlMask,                  0x1008ff12,spawn,          {.v = otogglecmd } },
	{ 0,                            0x1008ff13,spawn,          {.v = volucmd } },
	{ 0,                            0x1008ff11,spawn,          {.v = voldcmd } },
	{ 0,                            0x1008ff41,spawn,          {.v = lockcmd } },
	{ 0,                            0x1008ff2d,spawn,          {.v = lockcmd } },
	{ 0,                            0x1008ff2d,spawn,          {.v = suscmd } },
	{ 0,                            0x1008ff02,spawn,          {.v = brightup10 } },
	{ 0,                            0x1008ff03,spawn,          {.v = brightdown10 } },
	{ MODKEY,                       0xff50    ,spawn,          {.v = blankoff } },
	{ MODKEY,                       0xff57    ,spawn,          {.v = blankon } },
	{ ControlMask,                  0x1008ff02,spawn,          {.v = brightup1 } },
	{ ControlMask,                  0x1008ff03,spawn,          {.v = brightdown1 } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = pmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_w,      spawn,          {.v = nmcmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = nightcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_k,      setsmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_j,      setsmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = recompile } },
	{ MODKEY|ShiftMask,             XK_c,      quit,           {0} },
	{ MODKEY,                       XK_r,      recolor,        {0} },
	{ MODKEY,                       XK_r,      spawn,          {.v = patchcolors } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

