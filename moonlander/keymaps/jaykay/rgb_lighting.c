#include QMK_KEYBOARD_H
#include "user_layers.h"

#define MOON_LED_LEVEL LED_LEVEL

extern rgb_config_t rgb_matrix_config;

void keyboard_init_rgb_matrix(void) { rgb_matrix_enable(); }

// clang-format off
const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195}, {0,15,195} },
    [1] = { {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187}, {28,175,187} },
    [2] = { {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198} },
    [3] = { {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198} },
    [4] = { {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198}, {165,249,198} },
    [5] = { {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218}, {0,222,218} },
    [6] = { {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228}, {129,70,228} },
    [7] = { {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152}, {78,209,152} },
    [8] = { {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228}, {41,218,228} },
    [9] = { {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {0,183,238}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195}, {124,179,195} },
    [10] = { {0,183,238}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {141,255,233}, {141,255,233}, {0,183,238}, {141,255,233}, {0,0,0}, {141,255,233}, {0,183,238}, {0,183,238}, {141,255,233}, {154,255,255}, {141,255,233}, {141,255,233}, {0,183,238}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {0,0,0}, {0,0,0}, {141,255,233}, {141,255,233}, {0,0,0}, {141,255,233}, {141,255,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {0,0,0}, {0,0,0}, {88,185,172}, {0,0,0}, {0,0,0}, {0,0,255} },
    [11] = { {0,183,238}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {154,255,255}, {154,255,255}, {0,0,0}, {154,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,0,0}, {0,0,0}, {88,185,172}, {0,0,0}, {0,0,0}, {0,0,0} },
    [12] = { {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188}, {22,240,188} },
};
// clang-format on

void set_layer_color(int layer)
{
    for (int i = 0; i < DRIVER_LED_TOTAL; i++)
    {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (!hsv.h && !hsv.s && !hsv.v)
        {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
        else
        {
            RGB   rgb = hsv_to_rgb(hsv);
            float f   = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        }
    }
}

void rgb_matrix_indicators_user(void)
{
    bool suspend_state = rgb_matrix_get_suspend_state();
    if (suspend_state || keyboard_config.disable_layer_led)
    {
        return;
    }
    int8_t layer = user_layer();
    switch (layer)
    {
        case LAYER_QWERTY ... LAYER_GAMER: set_layer_color(layer); break;
        default:
            if (rgb_matrix_get_flags() == LED_FLAG_NONE)
                rgb_matrix_set_color_all(0, 0, 0);
            break;
    }
}
