
typedef union {
    unsigned int value;
    struct {
#ifdef BIGENDIAN
        unsigned char alpha, red, green, blue;
#else
        unsigned char blue, green, red, alpha;
#endif
    };
} Colour;
static_assert(sizeof(Colour) == 4, "");

Colour invert(Colour col)
{
    return (Colour) { .red = 255 - col.red,
        .green = 255 - col.green,
        .blue = 255 - col.blue,
        .alpha = col.alpha };
}

enum ColourBlendModes {
    ColourBlendModes_SoftLight,
    ColourBlendModes_DarkLight,
    ColourBlendModes_Multiply,
    ColourBlendModes_Dissolve,
    ColourBlendModes_Normal,
};

Colour blend(Colour col, Colour col2, float factor)
{
    return (Colour) { .red = factor * col.red + (1 - factor) * col2.red,
        .green = factor * col.green + (1 - factor) * col2.green,
        .blue = factor * col.blue + (1 - factor) * col2.blue,
        .alpha = col.alpha };
}

Colour darken(Colour col, float amount)
{
    col.red *= 1 - amount;
    col.green *= 1 - amount;
    col.blue *= 1 - amount;
    return col;
}

Colour lighten(Colour col, float amount)
{
    col.red += amount * (255 - col.red);
    col.green += amount * (255 - col.green);
    col.blue += amount * (255 - col.blue);
    return col;
}

Colour Colour_rgba(int r, int g, int b, int a)
{
    return (Colour) { .red = r, .green = g, .blue = b, .alpha = a };
}

Colour Colour_rgb(int r, int g, int b) { return Colour_rgba(r, g, b, 0); }
Colour Colour_new(unsigned int value)
{
    //    unsigned char *bytes = (unsigned char *)&value;
    //#ifdef BIGENDIAN
    //    return Colour_rgba(bytes[0],bytes[1], bytes[2], bytes[3]);
    //#else
    //    return Colour_rgba(bytes[3],bytes[2], bytes[1], bytes[0]);
    //#endif
    return (Colour) { .value = value };
}

void Colour_print(Colour col)
{
    printf("#%02x%02x%02x", col.red, col.green, col.blue);
    if (col.alpha) printf("%02x", col.alpha);
    puts("");
}

void Colour_printRGBA(Colour col)
{
    if (col.alpha)
        printf("rgba(%d,%d,%d,%d)\n", col.red, col.green, col.blue, col.alpha);
    else
        printf("rgb(%d,%d,%d)\n", col.red, col.green, col.blue);
}

typedef int YesOrNo;
#define no 0
#define yes 1

YesOrNo isDark(Colour col)
{
    return no; // NYI
}

enum SystemColours {
    SystemColours_window,
    SystemColours_text,
    SystemColours_background,
    SystemColours_highlight,
    SystemColours_accent,
    SystemColours_red,
    SystemColours_green,
    SystemColours_blue,
    SystemColours_yellow,
    SystemColours_purple,
    SystemColours_orange,
    SystemColours_systemred,
    SystemColours_systemgreen,
    SystemColours_systemblue,
    SystemColours_systemyellow,
    SystemColours_systempurple,
    SystemColours_systemorange
};

const Colour _systemColoursArray[] = {
    [SystemColours_window] = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_text] = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_background]
    = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_highlight] = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_accent] = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_red] = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_green] = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_blue] = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_yellow] = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_purple] = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_orange] = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_systemred] = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_systemgreen]
    = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_systemblue]
    = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_systemyellow]
    = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_systempurple]
    = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
    [SystemColours_systemorange]
    = { .red = 0, .green = 0, .blue = 0, .alpha = 0 },
};

Colour Colour_systemColour(enum SystemColours which)
{
    return _systemColoursArray[which];
}

enum KnownColours {
    KnownColours_indianRed,
    KnownColours_lightCoral,
    KnownColours_salmon,
    KnownColours_darkSalmon,
    KnownColours_lightSalmon,
    KnownColours_crimson,
    KnownColours_red,
    KnownColours_fireBrick,
    KnownColours_darkRed,
    KnownColours_pink,
    KnownColours_lightPink,
    KnownColours_hotPink,
    KnownColours_deepPink,
    KnownColours_mediumVioletRed,
    KnownColours_paleVioletRed,
    KnownColours_coral,
    KnownColours_tomato,
    KnownColours_orangeRed,
    KnownColours_darkOrange,
    KnownColours_orange,
    KnownColours_gold,
    KnownColours_yellow,
    KnownColours_lightYellow,
    KnownColours_lemonChiffon,
    KnownColours_lightGoldenrodYellow,
    KnownColours_papayaWhip,
    KnownColours_moccasin,
    KnownColours_peachPuff,
    KnownColours_paleGoldenrod,
    KnownColours_khaki,
    KnownColours_darkKhaki,
    KnownColours_lavender,
    KnownColours_thistle,
    KnownColours_plum,
    KnownColours_violet,
    KnownColours_orchid,
    KnownColours_fuchsia,
    KnownColours_magenta,
    KnownColours_mediumOrchid,
    KnownColours_mediumPurple,
    KnownColours_blueViolet,
    KnownColours_darkViolet,
    KnownColours_darkOrchid,
    KnownColours_darkMagenta,
    KnownColours_purple,
    KnownColours_rebeccaPurple,
    KnownColours_indigo,
    KnownColours_mediumSlateBlue,
    KnownColours_slateBlue,
    KnownColours_darkSlateBlue,
    KnownColours_greenYellow,
    KnownColours_chartreuse,
    KnownColours_lawnGreen,
    KnownColours_lime,
    KnownColours_limeGreen,
    KnownColours_paleGreen,
    KnownColours_lightGreen,
    KnownColours_mediumSpringGreen,
    KnownColours_springGreen,
    KnownColours_mediumSeaGreen,
    KnownColours_seaGreen,
    KnownColours_forestGreen,
    KnownColours_green,
    KnownColours_darkGreen,
    KnownColours_yellowGreen,
    KnownColours_oliveDrab,
    KnownColours_olive,
    KnownColours_darkOliveGreen,
    KnownColours_mediumAquamarine,
    KnownColours_darkSeaGreen,
    KnownColours_lightSeaGreen,
    KnownColours_darkCyan,
    KnownColours_teal,
    KnownColours_aqua,
    KnownColours_cyan,
    KnownColours_lightCyan,
    KnownColours_paleTurquoise,
    KnownColours_aquamarine,
    KnownColours_turquoise,
    KnownColours_mediumTurquoise,
    KnownColours_darkTurquoise,
    KnownColours_cadetBlue,
    KnownColours_steelBlue,
    KnownColours_lightSteelBlue,
    KnownColours_powderBlue,
    KnownColours_lightBlue,
    KnownColours_skyBlue,
    KnownColours_lightSkyBlue,
    KnownColours_deepSkyBlue,
    KnownColours_dodgerBlue,
    KnownColours_cornflowerBlue,
    KnownColours_royalBlue,
    KnownColours_blue,
    KnownColours_mediumBlue,
    KnownColours_darkBlue,
    KnownColours_navy,
    KnownColours_midnightBlue,
    KnownColours_cornsilk,
    KnownColours_blanchedAlmond,
    KnownColours_bisque,
    KnownColours_navajoWhite,
    KnownColours_wheat,
    KnownColours_burlyWood,
    KnownColours_tan,
    KnownColours_rosyBrown,
    KnownColours_sandyBrown,
    KnownColours_goldenrod,
    KnownColours_darkGoldenrod,
    KnownColours_peru,
    KnownColours_chocolate,
    KnownColours_saddleBrown,
    KnownColours_sienna,
    KnownColours_brown,
    KnownColours_maroon,
    KnownColours_white,
    KnownColours_snow,
    KnownColours_honeydew,
    KnownColours_mintCream,
    KnownColours_azure,
    KnownColours_aliceBlue,
    KnownColours_ghostWhite,
    KnownColours_whiteSmoke,
    KnownColours_seashell,
    KnownColours_beige,
    KnownColours_oldLace,
    KnownColours_floralWhite,
    KnownColours_ivory,
    KnownColours_antiqueWhite,
    KnownColours_linen,
    KnownColours_lavenderBlush,
    KnownColours_mistyRose,
    KnownColours_gainsboro,
    KnownColours_lightGray,
    KnownColours_silver,
    KnownColours_darkGray,
    KnownColours_gray,
    KnownColours_dimGray,
    KnownColours_lightSlateGray,
    KnownColours_slateGray,
    KnownColours_darkSlateGray,
    KnownColours_black
};

static const char* const KnownColours__names[]
    = { [KnownColours_indianRed] = "indianRed",
          [KnownColours_lightCoral] = "lightCoral",
          [KnownColours_salmon] = "salmon",
          [KnownColours_darkSalmon] = "darkSalmon",
          [KnownColours_lightSalmon] = "lightSalmon",
          [KnownColours_crimson] = "crimson",
          [KnownColours_red] = "red",
          [KnownColours_fireBrick] = "fireBrick",
          [KnownColours_darkRed] = "darkRed",
          [KnownColours_pink] = "pink",
          [KnownColours_lightPink] = "lightPink",
          [KnownColours_hotPink] = "hotPink",
          [KnownColours_deepPink] = "deepPink",
          [KnownColours_mediumVioletRed] = "mediumVioletRed",
          [KnownColours_paleVioletRed] = "paleVioletRed",
          [KnownColours_coral] = "coral",
          [KnownColours_tomato] = "tomato",
          [KnownColours_orangeRed] = "orangeRed",
          [KnownColours_darkOrange] = "darkOrange",
          [KnownColours_orange] = "orange",
          [KnownColours_gold] = "gold",
          [KnownColours_yellow] = "yellow",
          [KnownColours_lightYellow] = "lightYellow",
          [KnownColours_lemonChiffon] = "lemonChiffon",
          [KnownColours_lightGoldenrodYellow] = "lightGoldenrodYellow",
          [KnownColours_papayaWhip] = "papayaWhip",
          [KnownColours_moccasin] = "moccasin",
          [KnownColours_peachPuff] = "peachPuff",
          [KnownColours_paleGoldenrod] = "paleGoldenrod",
          [KnownColours_khaki] = "khaki",
          [KnownColours_darkKhaki] = "darkKhaki",
          [KnownColours_lavender] = "lavender",
          [KnownColours_thistle] = "thistle",
          [KnownColours_plum] = "plum",
          [KnownColours_violet] = "violet",
          [KnownColours_orchid] = "orchid",
          [KnownColours_fuchsia] = "fuchsia",
          [KnownColours_magenta] = "magenta",
          [KnownColours_mediumOrchid] = "mediumOrchid",
          [KnownColours_mediumPurple] = "mediumPurple",
          [KnownColours_blueViolet] = "blueViolet",
          [KnownColours_darkViolet] = "darkViolet",
          [KnownColours_darkOrchid] = "darkOrchid",
          [KnownColours_darkMagenta] = "darkMagenta",
          [KnownColours_purple] = "purple",
          [KnownColours_rebeccaPurple] = "rebeccaPurple",
          [KnownColours_indigo] = "indigo",
          [KnownColours_mediumSlateBlue] = "mediumSlateBlue",
          [KnownColours_slateBlue] = "slateBlue",
          [KnownColours_darkSlateBlue] = "darkSlateBlue",
          [KnownColours_greenYellow] = "greenYellow",
          [KnownColours_chartreuse] = "chartreuse",
          [KnownColours_lawnGreen] = "lawnGreen",
          [KnownColours_lime] = "lime",
          [KnownColours_limeGreen] = "limeGreen",
          [KnownColours_paleGreen] = "paleGreen",
          [KnownColours_lightGreen] = "lightGreen",
          [KnownColours_mediumSpringGreen] = "mediumSpringGreen",
          [KnownColours_springGreen] = "springGreen",
          [KnownColours_mediumSeaGreen] = "mediumSeaGreen",
          [KnownColours_seaGreen] = "seaGreen",
          [KnownColours_forestGreen] = "forestGreen",
          [KnownColours_green] = "green",
          [KnownColours_darkGreen] = "darkGreen",
          [KnownColours_yellowGreen] = "yellowGreen",
          [KnownColours_oliveDrab] = "oliveDrab",
          [KnownColours_olive] = "olive",
          [KnownColours_darkOliveGreen] = "darkOliveGreen",
          [KnownColours_mediumAquamarine] = "mediumAquamarine",
          [KnownColours_darkSeaGreen] = "darkSeaGreen",
          [KnownColours_lightSeaGreen] = "lightSeaGreen",
          [KnownColours_darkCyan] = "darkCyan",
          [KnownColours_teal] = "teal",
          [KnownColours_aqua] = "aqua",
          [KnownColours_cyan] = "cyan",
          [KnownColours_lightCyan] = "lightCyan",
          [KnownColours_paleTurquoise] = "paleTurquoise",
          [KnownColours_aquamarine] = "aquamarine",
          [KnownColours_turquoise] = "turquoise",
          [KnownColours_mediumTurquoise] = "mediumTurquoise",
          [KnownColours_darkTurquoise] = "darkTurquoise",
          [KnownColours_cadetBlue] = "cadetBlue",
          [KnownColours_steelBlue] = "steelBlue",
          [KnownColours_lightSteelBlue] = "lightSteelBlue",
          [KnownColours_powderBlue] = "powderBlue",
          [KnownColours_lightBlue] = "lightBlue",
          [KnownColours_skyBlue] = "skyBlue",
          [KnownColours_lightSkyBlue] = "lightSkyBlue",
          [KnownColours_deepSkyBlue] = "deepSkyBlue",
          [KnownColours_dodgerBlue] = "dodgerBlue",
          [KnownColours_cornflowerBlue] = "cornflowerBlue",
          [KnownColours_royalBlue] = "royalBlue",
          [KnownColours_blue] = "blue",
          [KnownColours_mediumBlue] = "mediumBlue",
          [KnownColours_darkBlue] = "darkBlue",
          [KnownColours_navy] = "navy",
          [KnownColours_midnightBlue] = "midnightBlue",
          [KnownColours_cornsilk] = "cornsilk",
          [KnownColours_blanchedAlmond] = "blanchedAlmond",
          [KnownColours_bisque] = "bisque",
          [KnownColours_navajoWhite] = "navajoWhite",
          [KnownColours_wheat] = "wheat",
          [KnownColours_burlyWood] = "burlyWood",
          [KnownColours_tan] = "tan",
          [KnownColours_rosyBrown] = "rosyBrown",
          [KnownColours_sandyBrown] = "sandyBrown",
          [KnownColours_goldenrod] = "goldenrod",
          [KnownColours_darkGoldenrod] = "darkGoldenrod",
          [KnownColours_peru] = "peru",
          [KnownColours_chocolate] = "chocolate",
          [KnownColours_saddleBrown] = "saddleBrown",
          [KnownColours_sienna] = "sienna",
          [KnownColours_brown] = "brown",
          [KnownColours_maroon] = "maroon",
          [KnownColours_white] = "white",
          [KnownColours_snow] = "snow",
          [KnownColours_honeydew] = "honeydew",
          [KnownColours_mintCream] = "mintCream",
          [KnownColours_azure] = "azure",
          [KnownColours_aliceBlue] = "aliceBlue",
          [KnownColours_ghostWhite] = "ghostWhite",
          [KnownColours_whiteSmoke] = "whiteSmoke",
          [KnownColours_seashell] = "seashell",
          [KnownColours_beige] = "beige",
          [KnownColours_oldLace] = "oldLace",
          [KnownColours_floralWhite] = "floralWhite",
          [KnownColours_ivory] = "ivory",
          [KnownColours_antiqueWhite] = "antiqueWhite",
          [KnownColours_linen] = "linen",
          [KnownColours_lavenderBlush] = "lavenderBlush",
          [KnownColours_mistyRose] = "mistyRose",
          [KnownColours_gainsboro] = "gainsboro",
          [KnownColours_lightGray] = "lightGray",
          [KnownColours_silver] = "silver",
          [KnownColours_darkGray] = "darkGray",
          [KnownColours_gray] = "gray",
          [KnownColours_dimGray] = "dimGray",
          [KnownColours_lightSlateGray] = "lightSlateGray",
          [KnownColours_slateGray] = "slateGray",
          [KnownColours_darkSlateGray] = "darkSlateGray",
          [KnownColours_black] = "black" };

static const Colour KnownColours__values[]
    = { [KnownColours_indianRed] = (Colour) { .value = 0xCD5C5C },
          [KnownColours_lightCoral] = (Colour) { .value = 0xF08080 },
          [KnownColours_salmon] = (Colour) { .value = 0xFA8072 },
          [KnownColours_darkSalmon] = (Colour) { .value = 0xE9967A },
          [KnownColours_lightSalmon] = (Colour) { .value = 0xFFA07A },
          [KnownColours_crimson] = (Colour) { .value = 0xDC143C },
          [KnownColours_red] = (Colour) { .value = 0xFF0000 },
          [KnownColours_fireBrick] = (Colour) { .value = 0xB22222 },
          [KnownColours_darkRed] = (Colour) { .value = 0x8B0000 },
          [KnownColours_pink] = (Colour) { .value = 0xFFC0CB },
          [KnownColours_lightPink] = (Colour) { .value = 0xFFB6C1 },
          [KnownColours_hotPink] = (Colour) { .value = 0xFF69B4 },
          [KnownColours_deepPink] = (Colour) { .value = 0xFF1493 },
          [KnownColours_mediumVioletRed] = (Colour) { .value = 0xC71585 },
          [KnownColours_paleVioletRed] = (Colour) { .value = 0xDB7093 },
          [KnownColours_coral] = (Colour) { .value = 0xFF7F50 },
          [KnownColours_tomato] = (Colour) { .value = 0xFF6347 },
          [KnownColours_orangeRed] = (Colour) { .value = 0xFF4500 },
          [KnownColours_darkOrange] = (Colour) { .value = 0xFF8C00 },
          [KnownColours_orange] = (Colour) { .value = 0xFFA500 },
          [KnownColours_gold] = (Colour) { .value = 0xFFD700 },
          [KnownColours_yellow] = (Colour) { .value = 0xFFFF00 },
          [KnownColours_lightYellow] = (Colour) { .value = 0xFFFFE0 },
          [KnownColours_lemonChiffon] = (Colour) { .value = 0xFFFACD },
          [KnownColours_lightGoldenrodYellow] = (Colour) { .value = 0xFAFAD2 },
          [KnownColours_papayaWhip] = (Colour) { .value = 0xFFEFD5 },
          [KnownColours_moccasin] = (Colour) { .value = 0xFFE4B5 },
          [KnownColours_peachPuff] = (Colour) { .value = 0xFFDAB9 },
          [KnownColours_paleGoldenrod] = (Colour) { .value = 0xEEE8AA },
          [KnownColours_khaki] = (Colour) { .value = 0xF0E68C },
          [KnownColours_darkKhaki] = (Colour) { .value = 0xBDB76B },
          [KnownColours_lavender] = (Colour) { .value = 0xE6E6FA },
          [KnownColours_thistle] = (Colour) { .value = 0xD8BFD8 },
          [KnownColours_plum] = (Colour) { .value = 0xDDA0DD },
          [KnownColours_violet] = (Colour) { .value = 0xEE82EE },
          [KnownColours_orchid] = (Colour) { .value = 0xDA70D6 },
          [KnownColours_fuchsia] = (Colour) { .value = 0xFF00FF },
          [KnownColours_magenta] = (Colour) { .value = 0xFF00FF },
          [KnownColours_mediumOrchid] = (Colour) { .value = 0xBA55D3 },
          [KnownColours_mediumPurple] = (Colour) { .value = 0x9370DB },
          [KnownColours_blueViolet] = (Colour) { .value = 0x8A2BE2 },
          [KnownColours_darkViolet] = (Colour) { .value = 0x9400D3 },
          [KnownColours_darkOrchid] = (Colour) { .value = 0x9932CC },
          [KnownColours_darkMagenta] = (Colour) { .value = 0x8B008B },
          [KnownColours_purple] = (Colour) { .value = 0x800080 },
          [KnownColours_rebeccaPurple] = (Colour) { .value = 0x663399 },
          [KnownColours_indigo] = (Colour) { .value = 0x4B0082 },
          [KnownColours_mediumSlateBlue] = (Colour) { .value = 0x7B68EE },
          [KnownColours_slateBlue] = (Colour) { .value = 0x6A5ACD },
          [KnownColours_darkSlateBlue] = (Colour) { .value = 0x483D8B },
          [KnownColours_greenYellow] = (Colour) { .value = 0xADFF2F },
          [KnownColours_chartreuse] = (Colour) { .value = 0x7FFF00 },
          [KnownColours_lawnGreen] = (Colour) { .value = 0x7CFC00 },
          [KnownColours_lime] = (Colour) { .value = 0x00FF00 },
          [KnownColours_limeGreen] = (Colour) { .value = 0x32CD32 },
          [KnownColours_paleGreen] = (Colour) { .value = 0x98FB98 },
          [KnownColours_lightGreen] = (Colour) { .value = 0x90EE90 },
          [KnownColours_mediumSpringGreen] = (Colour) { .value = 0x00FA9A },
          [KnownColours_springGreen] = (Colour) { .value = 0x00FF7F },
          [KnownColours_mediumSeaGreen] = (Colour) { .value = 0x3CB371 },
          [KnownColours_seaGreen] = (Colour) { .value = 0x2E8B57 },
          [KnownColours_forestGreen] = (Colour) { .value = 0x228B22 },
          [KnownColours_green] = (Colour) { .value = 0x008000 },
          [KnownColours_darkGreen] = (Colour) { .value = 0x006400 },
          [KnownColours_yellowGreen] = (Colour) { .value = 0x9ACD32 },
          [KnownColours_oliveDrab] = (Colour) { .value = 0x6B8E23 },
          [KnownColours_olive] = (Colour) { .value = 0x808000 },
          [KnownColours_darkOliveGreen] = (Colour) { .value = 0x556B2F },
          [KnownColours_mediumAquamarine] = (Colour) { .value = 0x66CDAA },
          [KnownColours_darkSeaGreen] = (Colour) { .value = 0x8FBC8F },
          [KnownColours_lightSeaGreen] = (Colour) { .value = 0x20B2AA },
          [KnownColours_darkCyan] = (Colour) { .value = 0x008B8B },
          [KnownColours_teal] = (Colour) { .value = 0x008080 },
          [KnownColours_aqua] = (Colour) { .value = 0x00FFFF },
          [KnownColours_cyan] = (Colour) { .value = 0x00FFFF },
          [KnownColours_lightCyan] = (Colour) { .value = 0xE0FFFF },
          [KnownColours_paleTurquoise] = (Colour) { .value = 0xAFEEEE },
          [KnownColours_aquamarine] = (Colour) { .value = 0x7FFFD4 },
          [KnownColours_turquoise] = (Colour) { .value = 0x40E0D0 },
          [KnownColours_mediumTurquoise] = (Colour) { .value = 0x48D1CC },
          [KnownColours_darkTurquoise] = (Colour) { .value = 0x00CED1 },
          [KnownColours_cadetBlue] = (Colour) { .value = 0x5F9EA0 },
          [KnownColours_steelBlue] = (Colour) { .value = 0x4682B4 },
          [KnownColours_lightSteelBlue] = (Colour) { .value = 0xB0C4DE },
          [KnownColours_powderBlue] = (Colour) { .value = 0xB0E0E6 },
          [KnownColours_lightBlue] = (Colour) { .value = 0xADD8E6 },
          [KnownColours_skyBlue] = (Colour) { .value = 0x87CEEB },
          [KnownColours_lightSkyBlue] = (Colour) { .value = 0x87CEFA },
          [KnownColours_deepSkyBlue] = (Colour) { .value = 0x00BFFF },
          [KnownColours_dodgerBlue] = (Colour) { .value = 0x1E90FF },
          [KnownColours_cornflowerBlue] = (Colour) { .value = 0x6495ED },
          [KnownColours_royalBlue] = (Colour) { .value = 0x4169E1 },
          [KnownColours_blue] = (Colour) { .value = 0x0000FF },
          [KnownColours_mediumBlue] = (Colour) { .value = 0x0000CD },
          [KnownColours_darkBlue] = (Colour) { .value = 0x00008B },
          [KnownColours_navy] = (Colour) { .value = 0x000080 },
          [KnownColours_midnightBlue] = (Colour) { .value = 0x191970 },
          [KnownColours_cornsilk] = (Colour) { .value = 0xFFF8DC },
          [KnownColours_blanchedAlmond] = (Colour) { .value = 0xFFEBCD },
          [KnownColours_bisque] = (Colour) { .value = 0xFFE4C4 },
          [KnownColours_navajoWhite] = (Colour) { .value = 0xFFDEAD },
          [KnownColours_wheat] = (Colour) { .value = 0xF5DEB3 },
          [KnownColours_burlyWood] = (Colour) { .value = 0xDEB887 },
          [KnownColours_tan] = (Colour) { .value = 0xD2B48C },
          [KnownColours_rosyBrown] = (Colour) { .value = 0xBC8F8F },
          [KnownColours_sandyBrown] = (Colour) { .value = 0xF4A460 },
          [KnownColours_goldenrod] = (Colour) { .value = 0xDAA520 },
          [KnownColours_darkGoldenrod] = (Colour) { .value = 0xB8860B },
          [KnownColours_peru] = (Colour) { .value = 0xCD853F },
          [KnownColours_chocolate] = (Colour) { .value = 0xD2691E },
          [KnownColours_saddleBrown] = (Colour) { .value = 0x8B4513 },
          [KnownColours_sienna] = (Colour) { .value = 0xA0522D },
          [KnownColours_brown] = (Colour) { .value = 0xA52A2A },
          [KnownColours_maroon] = (Colour) { .value = 0x800000 },
          [KnownColours_white] = (Colour) { .value = 0xFFFFFF },
          [KnownColours_snow] = (Colour) { .value = 0xFFFAFA },
          [KnownColours_honeydew] = (Colour) { .value = 0xF0FFF0 },
          [KnownColours_mintCream] = (Colour) { .value = 0xF5FFFA },
          [KnownColours_azure] = (Colour) { .value = 0xF0FFFF },
          [KnownColours_aliceBlue] = (Colour) { .value = 0xF0F8FF },
          [KnownColours_ghostWhite] = (Colour) { .value = 0xF8F8FF },
          [KnownColours_whiteSmoke] = (Colour) { .value = 0xF5F5F5 },
          [KnownColours_seashell] = (Colour) { .value = 0xFFF5EE },
          [KnownColours_beige] = (Colour) { .value = 0xF5F5DC },
          [KnownColours_oldLace] = (Colour) { .value = 0xFDF5E6 },
          [KnownColours_floralWhite] = (Colour) { .value = 0xFFFAF0 },
          [KnownColours_ivory] = (Colour) { .value = 0xFFFFF0 },
          [KnownColours_antiqueWhite] = (Colour) { .value = 0xFAEBD7 },
          [KnownColours_linen] = (Colour) { .value = 0xFAF0E6 },
          [KnownColours_lavenderBlush] = (Colour) { .value = 0xFFF0F5 },
          [KnownColours_mistyRose] = (Colour) { .value = 0xFFE4E1 },
          [KnownColours_gainsboro] = (Colour) { .value = 0xDCDCDC },
          [KnownColours_lightGray] = (Colour) { .value = 0xD3D3D3 },
          [KnownColours_silver] = (Colour) { .value = 0xC0C0C0 },
          [KnownColours_darkGray] = (Colour) { .value = 0xA9A9A9 },
          [KnownColours_gray] = (Colour) { .value = 0x808080 },
          [KnownColours_dimGray] = (Colour) { .value = 0x696969 },
          [KnownColours_lightSlateGray] = (Colour) { .value = 0x778899 },
          [KnownColours_slateGray] = (Colour) { .value = 0x708090 },
          [KnownColours_darkSlateGray] = (Colour) { .value = 0x2F4F4F },
          [KnownColours_black] = (Colour) { .value = 0x000000 } };

static const char* const KnownColours__groupNames[]
    = { [KnownColours_indianRed] = "Reds",
          [KnownColours_lightCoral] = "Reds",
          [KnownColours_salmon] = "Reds",
          [KnownColours_darkSalmon] = "Reds",
          [KnownColours_lightSalmon] = "Reds",
          [KnownColours_crimson] = "Reds",
          [KnownColours_red] = "Reds",
          [KnownColours_fireBrick] = "Reds",
          [KnownColours_darkRed] = "Reds",
          [KnownColours_pink] = "Pinks",
          [KnownColours_lightPink] = "Pinks",
          [KnownColours_hotPink] = "Pinks",
          [KnownColours_deepPink] = "Pinks",
          [KnownColours_mediumVioletRed] = "Pinks",
          [KnownColours_paleVioletRed] = "Pinks",
          [KnownColours_coral] = "Oranges",
          [KnownColours_tomato] = "Oranges",
          [KnownColours_orangeRed] = "Oranges",
          [KnownColours_darkOrange] = "Oranges",
          [KnownColours_orange] = "Oranges",
          [KnownColours_gold] = "Yellows",
          [KnownColours_yellow] = "Yellows",
          [KnownColours_lightYellow] = "Yellows",
          [KnownColours_lemonChiffon] = "Yellows",
          [KnownColours_lightGoldenrodYellow] = "Yellows",
          [KnownColours_papayaWhip] = "Yellows",
          [KnownColours_moccasin] = "Yellows",
          [KnownColours_peachPuff] = "Yellows",
          [KnownColours_paleGoldenrod] = "Yellows",
          [KnownColours_khaki] = "Yellows",
          [KnownColours_darkKhaki] = "Yellows",
          [KnownColours_lavender] = "Purples",
          [KnownColours_thistle] = "Purples",
          [KnownColours_plum] = "Purples",
          [KnownColours_violet] = "Purples",
          [KnownColours_orchid] = "Purples",
          [KnownColours_fuchsia] = "Purples",
          [KnownColours_magenta] = "Purples",
          [KnownColours_mediumOrchid] = "Purples",
          [KnownColours_mediumPurple] = "Purples",
          [KnownColours_blueViolet] = "Purples",
          [KnownColours_darkViolet] = "Purples",
          [KnownColours_darkOrchid] = "Purples",
          [KnownColours_darkMagenta] = "Purples",
          [KnownColours_purple] = "Purples",
          [KnownColours_rebeccaPurple] = "Purples",
          [KnownColours_indigo] = "Purples",
          [KnownColours_mediumSlateBlue] = "Purples",
          [KnownColours_slateBlue] = "Purples",
          [KnownColours_darkSlateBlue] = "Purples",
          [KnownColours_greenYellow] = "Greens",
          [KnownColours_chartreuse] = "Greens",
          [KnownColours_lawnGreen] = "Greens",
          [KnownColours_lime] = "Greens",
          [KnownColours_limeGreen] = "Greens",
          [KnownColours_paleGreen] = "Greens",
          [KnownColours_lightGreen] = "Greens",
          [KnownColours_mediumSpringGreen] = "Greens",
          [KnownColours_springGreen] = "Greens",
          [KnownColours_mediumSeaGreen] = "Greens",
          [KnownColours_seaGreen] = "Greens",
          [KnownColours_forestGreen] = "Greens",
          [KnownColours_green] = "Greens",
          [KnownColours_darkGreen] = "Greens",
          [KnownColours_yellowGreen] = "Greens",
          [KnownColours_oliveDrab] = "Greens",
          [KnownColours_olive] = "Greens",
          [KnownColours_darkOliveGreen] = "Greens",
          [KnownColours_mediumAquamarine] = "Greens",
          [KnownColours_darkSeaGreen] = "Greens",
          [KnownColours_lightSeaGreen] = "Greens",
          [KnownColours_darkCyan] = "Greens",
          [KnownColours_teal] = "Greens",
          [KnownColours_aqua] = "Blues",
          [KnownColours_cyan] = "Blues",
          [KnownColours_lightCyan] = "Blues",
          [KnownColours_paleTurquoise] = "Blues",
          [KnownColours_aquamarine] = "Blues",
          [KnownColours_turquoise] = "Blues",
          [KnownColours_mediumTurquoise] = "Blues",
          [KnownColours_darkTurquoise] = "Blues",
          [KnownColours_cadetBlue] = "Blues",
          [KnownColours_steelBlue] = "Blues",
          [KnownColours_lightSteelBlue] = "Blues",
          [KnownColours_powderBlue] = "Blues",
          [KnownColours_lightBlue] = "Blues",
          [KnownColours_skyBlue] = "Blues",
          [KnownColours_lightSkyBlue] = "Blues",
          [KnownColours_deepSkyBlue] = "Blues",
          [KnownColours_dodgerBlue] = "Blues",
          [KnownColours_cornflowerBlue] = "Blues",
          [KnownColours_royalBlue] = "Blues",
          [KnownColours_blue] = "Blues",
          [KnownColours_mediumBlue] = "Blues",
          [KnownColours_darkBlue] = "Blues",
          [KnownColours_navy] = "Blues",
          [KnownColours_midnightBlue] = "Blues",
          [KnownColours_cornsilk] = "Browns",
          [KnownColours_blanchedAlmond] = "Browns",
          [KnownColours_bisque] = "Browns",
          [KnownColours_navajoWhite] = "Browns",
          [KnownColours_wheat] = "Browns",
          [KnownColours_burlyWood] = "Browns",
          [KnownColours_tan] = "Browns",
          [KnownColours_rosyBrown] = "Browns",
          [KnownColours_sandyBrown] = "Browns",
          [KnownColours_goldenrod] = "Browns",
          [KnownColours_darkGoldenrod] = "Browns",
          [KnownColours_peru] = "Browns",
          [KnownColours_chocolate] = "Browns",
          [KnownColours_saddleBrown] = "Browns",
          [KnownColours_sienna] = "Browns",
          [KnownColours_brown] = "Browns",
          [KnownColours_maroon] = "Browns",
          [KnownColours_white] = "Whites",
          [KnownColours_snow] = "Whites",
          [KnownColours_honeydew] = "Whites",
          [KnownColours_mintCream] = "Whites",
          [KnownColours_azure] = "Whites",
          [KnownColours_aliceBlue] = "Whites",
          [KnownColours_ghostWhite] = "Whites",
          [KnownColours_whiteSmoke] = "Whites",
          [KnownColours_seashell] = "Whites",
          [KnownColours_beige] = "Whites",
          [KnownColours_oldLace] = "Whites",
          [KnownColours_floralWhite] = "Whites",
          [KnownColours_ivory] = "Whites",
          [KnownColours_antiqueWhite] = "Whites",
          [KnownColours_linen] = "Whites",
          [KnownColours_lavenderBlush] = "Whites",
          [KnownColours_mistyRose] = "Whites",
          [KnownColours_gainsboro] = "Greys",
          [KnownColours_lightGray] = "Greys",
          [KnownColours_silver] = "Greys",
          [KnownColours_darkGray] = "Greys",
          [KnownColours_gray] = "Greys",
          [KnownColours_dimGray] = "Greys",
          [KnownColours_lightSlateGray] = "Greys",
          [KnownColours_slateGray] = "Greys",
          [KnownColours_darkSlateGray] = "Greys",
          [KnownColours_black] = "Greys" };

#define jet_countof(x) (sizeof(x) / sizeof(x[0]))
int power2(int a) { return a * a; }

#include <math.h>

double ColourDistance(Colour e1, Colour e2)
{
    long rmean = ((long)e1.red + (long)e2.red) / 2;
    long r = ((long)e1.red - (long)e2.red);
    long g = ((long)e1.green - (long)e2.green);
    long b = ((long)e1.blue - (long)e2.blue);
    return sqrt((((512 + rmean) * r * r) >> 8) + 4 * g * g
        + (((767 - rmean) * b * b) >> 8));
}

typedef struct {
    int L, a, b;
} LabColour;

LabColour rgb2lab(Colour col)
{
    // http://www.brucelindbloom.com

    float r, g, b, X, Y, Z, fx, fy, fz, xr, yr, zr;
    float Ls, as, bs;
    float eps = 216.f / 24389.f;
    float k = 24389.f / 27.f;

    float Xr = 0.964221f; // reference white D50
    float Yr = 1.0f;
    float Zr = 0.825211f;

    // RGB to XYZ
    r = col.red / 255.f; // R 0..1
    g = col.green / 255.f; // G 0..1
    b = col.blue / 255.f; // B 0..1

    // assuming sRGB (D65)
    if (r <= 0.04045)
        r = r / 12;
    else
        r = (float)pow((r + 0.055) / 1.055, 2.4);

    if (g <= 0.04045)
        g = g / 12;
    else
        g = (float)pow((g + 0.055) / 1.055, 2.4);

    if (b <= 0.04045)
        b = b / 12;
    else
        b = (float)pow((b + 0.055) / 1.055, 2.4);

    X = 0.436052025f * r + 0.385081593f * g + 0.143087414f * b;
    Y = 0.222491598f * r + 0.71688606f * g + 0.060621486f * b;
    Z = 0.013929122f * r + 0.097097002f * g + 0.71418547f * b;

    // XYZ to Lab
    xr = X / Xr;
    yr = Y / Yr;
    zr = Z / Zr;

    if (xr > eps)
        fx = (float)pow(xr, 1 / 3.);
    else
        fx = (float)((k * xr + 16.) / 116.);

    if (yr > eps)
        fy = (float)pow(yr, 1 / 3.);
    else
        fy = (float)((k * yr + 16.) / 116.);

    if (zr > eps)
        fz = (float)pow(zr, 1 / 3.);
    else
        fz = (float)((k * zr + 16.) / 116);

    Ls = (116 * fy) - 16;
    as = 500 * (fx - fy);
    bs = 200 * (fy - fz);

    return (LabColour) {
        .L = (int)(2.55 * Ls + .5), .a = (int)(as + .5), .b = (int)(bs + .5)
    };
}

/**
 * Computes the difference between two RGB colors by converting them to the
 * L*a*b scale and comparing them using the CIE76 algorithm {
 * http://en.wikipedia.org/wiki/Color_difference#CIE76}
 */
double getLabColorDifferenceSq(Colour a, Colour b)
{
    //    int r1, g1, b1, r2, g2, b2;
    //    r1 = a.red;
    //    g1 = a.green;
    //    b1 = a.blue;
    //    r2 = b.red;
    //    g2 = b.green;
    //    b2 = b.blue;
    LabColour lab1 = rgb2lab(a);
    LabColour lab2 = rgb2lab(b);
    return pow(lab2.L - lab1.L, 2) + pow(lab2.a - lab1.a, 2)
        + pow(lab2.b - lab1.b, 2);
}

enum KnownColours closestKnown(Colour col)
{
    //    unsigned long long dsq = UINT64_MAX;
    double dsq = 1e100;
    int ret = -1;
    for (int i = 0; i < jet_countof(KnownColours__names); i++) {
        Colour kc = KnownColours__values[i];
        //        unsigned long long dsqi = 0;
        // may need to promote to wider int before subtracting
        //        double dsqi=ColourDistance(kc, col);
        double dsqi = getLabColorDifferenceSq(kc, col);
        int kcred = kc.red;
        int kcgreen = kc.green;
        int kcblue = kc.blue;
        int colred = col.red;
        int colgreen = col.green;
        int colblue = col.blue;
        //
        //        dsqi += power2(1+colred)*power2(kcred-colred);
        //        dsqi +=  power2(1+colgreen)*power2(kcgreen-colgreen);
        //        dsqi +=  power2(1+colblue)*power2(kcblue-colblue);
        if (dsqi < dsq) {
            dsq = dsqi;
            ret = i;
            //            printf("%llu %llu : %d %d %d - %d %d %d - %s\n",dsq,
            //            dsqi,kcred,kcgreen,kcblue,colred,colgreen,colblue,KnownColours__names[i]);
        }
    }
    return ret;
}

int maisn()
{
    unsigned int kcols[] = { 0x08653e, 0xfedcba, 0x128E9A, 0x586264 };
    for (int i = 0; i < jet_countof(kcols); i++) {
        puts("----");
        Colour c = Colour_new(kcols[i]);
        rgb2lab(c);
        Colour_print(c);
        Colour_printRGBA(c);
        enum KnownColours kc = closestKnown(c);
        printf("closest: %s (%s) ", KnownColours__names[kc],
            KnownColours__groupNames[kc]);
        Colour_print(KnownColours__values[kc]);
    }
    return 0;
}