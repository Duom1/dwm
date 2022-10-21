static const char norm_fg[] = "#afbbcc";
static const char norm_bg[] = "#080F37";
static const char norm_border[] = "#7a828e";

static const char sel_fg[] = "#afbbcc";
static const char sel_bg[] = "#A24952";
static const char sel_border[] = "#afbbcc";


static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
};
