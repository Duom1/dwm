static const char norm_fg[] = "#d9979a";
static const char norm_bg[] = "#090914";
static const char norm_border[] = "#97696b";

static const char sel_fg[] = "#d9979a";
static const char sel_bg[] = "#654049";
static const char sel_border[] = "#d9979a";


static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
};
