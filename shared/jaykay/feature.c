#include QMK_KEYBOARD_H
#include "config.h"
#include "user_keycodes.h"
#include "user_layers.h"
#include "feature.h"

enum
{
    FEATURE_CAPS        = 0x01,
    FEATURE_NUM         = 0x02,
    FEATURE_SYM         = 0x04,
    FEATURE_SYM_ONESHOT = 0x08,
    FEATURE_NAV         = 0x10,
    FEATURE_NAV_ONESHOT = 0x20,
    FEATURE_USED        = 0x40,
};

enum
{
    SMART_CAPS_OFF    = 0x00,
    SMART_CAPS_USED   = 0x02,
    SMART_CAPS_SHIFT  = 0x04,
    SMART_CAPS_HOLD   = 0x08,
    SMART_CAPS_NORMAL = 0x10,
    SMART_CAPS_CAMEL  = 0x40,
    SMART_CAPS_SNAKE  = 0x80,
};



/*
Thought Experiment: If we check `signals` can we determine state?

These are key signals, these are external signals:

- Nav
- Sym
- SymbolsUsed
- SmartCapsUsed
- SmartNumUsed

These are logic signals, logic signals happen internally:

- SymOS (OneShot)
- SmartNum
- SmartCaps

State Changes:
- NORMAL to NAV          activate the NAV layer, deactivate all other features
- NORMAL to SYM          activate the SYM layer
- NORMAL to SYMOS        activate the SYM layer
- RAISE to SmartNum      activate the NUM layer
- RAISE to SmartCaps     activate CAPS mode
- SmartNum to SYM        activate SYM layer, keep SmartNum activated
- SmartCaps to SYM       activate SYM layer, keep SmartCaps activated


Low(Nav), Low(Sym), Low(SymOS), Low|High(SmartNum), Low|High(SmartCaps)                         => State = NORMAL
LowToHigh(Nav), Low(Sym), Low(SymOs)                                                            => State = NAV, SetLow(SmartNum), SetLow(SmartCaps)
High(Nav), Low(Sym), Low(SymOS)                                                                 => State = NAV
    High(Nav), LowToHigh(Sym)                                                                       => State = RAISE, SetLow(KeysUsed)
    High(Nav), HighToLow(Sym), Low(KeysUsed)                                                        => State = SMARTNUM
    HighToLow(Nav), Low(Sym), Low(KeysUsed), High(SmartNum), Low(KeysUsed)                          => State = SMARTNUM
HighToLow(Nav), Low(Sym), Low(SymOS), Low(SmartNum), Low(SmartCaps), Low(KeysUsed)              => State = NORMAL

LowToHigh(Nav), Low(Sym), High(SymOs)                                                           => State = RAISE
High(Nav), Low(Sym), High(SymOs)                                                                => State = RAISE
Low(Nav), Low(Sym), High(SymOs)                                                                 => State = RAISE, SetLow(SymOs)

LowToHigh(Sym), Low(Nav)                                                                        => State = SYM, SetLow(SymbolsUsed)
High(Sym),      Low(Nav), Low(SymbolsUsed)                                                          => State = SYM
HighToLow(Sym), Low(Nav), Low(SymbolsUsed)                                                          => State = SYMOS

High(Sym),      Low(Nav), Low|High(SmartNum), Low|High(SmartCaps), Low(SymbolsUsed)             => State = SYM
    High(Sym), LowToHigh(Nav)                                                                       => State = RAISE
    High(Sym), HighToLow(Nav), Low(KeysUsed)                                                        => State = SMARTCAPS, SetLow(AlphasUsed)
    HighToLow(Sym), Low(Nav), Low(KeysUsed), Low(SmartNum), High(SmartCaps), Low(AlphasUsed)        => State = SMARTCAPS

*/

/*
Possible combinations with NAV and SYM:
- Tap NAV  +  Tap SYM    = unused (goes through `leader` logic)
- Tap SYM  +  Tap NAV    = RAISE Layer lock
- Hold NAV +  Tap SYM    = SmartNum  (You can now release NAV and it will stay in SmartNum mode)
- Hold SYM +  Tap NAV    = SmartCaps (You can now release SYM and it will stay in SmartCaps mode)
- Hold NAV +  Hold SYM   = RAISE Layer

Hold NAV -> Tap SYM will put the keyboard in SMARTNUM mode.
  - When you release NAV withouth having typed anything it will stay in SMARTNUM mode.
  - When you hold NAV and you type some numbers and then release NAV it will exit SMARTNUM mode.

Hold SYM -> Tap NAV will put the keyboard in SMARTCAPS mode, tapping NAV again will cycle to the next SMARTCAPS mode.
*/

#define SMART_CAPS_MAX_SEPARATORS 4

static uint8_t     s_smartcaps_state                               = 0;
static uint16_t    s_smartcaps_arr_seps[SMART_CAPS_MAX_SEPARATORS] = {KC_NO};
static int8_t      s_smartcaps_num_seps                            = 0;
static inline bool smartcaps_active_all(uint8_t features) { return (s_smartcaps_state & features) == features; }
static inline bool smartcaps_active_any(uint8_t features) { return (s_smartcaps_state & features) != 0; }

static uint8_t     s_feature_state = 0;
static inline bool features_active_all(uint8_t features) { return (s_feature_state & features) == features; }
static inline bool features_active_any(uint8_t features) { return (s_feature_state & features) != 0; }

void enable_smart_numbers(void)
{
    s_feature_state |= FEATURE_NUM;
    s_feature_state &= ~FEATURE_USED;
    user_layer_on(LAYER_NUMBERS);
}

bool process_feature_key(uint16_t kc, keyrecord_t* record)
{
    bool ret = true;
    {
        if (record->event.pressed)
        {
            if (features_active_all(FEATURE_SYM_ONESHOT | FEATURE_NAV_ONESHOT))
            {
                if (kc == KC_BSPACE || kc == KC_SPACE || kc == CC_FNUM || kc == CC_FNAV || kc == CC_FCAPS || kc == CC_FSYM)
                {
                    s_feature_state &= ~(FEATURE_SYM_ONESHOT | FEATURE_NAV_ONESHOT | FEATURE_USED);
                    user_layer_on(LAYER_QWERTY);
                }
            }

            // logic for when a key is pressed
            switch (kc)
            {
                // pressed
                case CC_SHFT:
                case CC_CTRL:
                case CC_ALT:
                case CC_CMD: break;

                case CC_UNDO ... CC_CLOSE: s_feature_state |= FEATURE_USED; break;
                
                case KC_A ... KC_Z:
                    s_feature_state |= FEATURE_USED;
                    s_smartcaps_state |= SMART_CAPS_USED;
                    break;

                case KC_MINUS ... KC_SLASH:
                case LSFT(KC_1) ... LSFT(KC_0):
                case LSFT(KC_MINUS) ... LSFT(KC_SLASH):
                    s_feature_state |= FEATURE_USED;
                    if (smartcaps_active_any(SMART_CAPS_NORMAL))
                    {
                        if (!smartcaps_active_any(SMART_CAPS_USED))
                        {
                            if (s_smartcaps_num_seps < SMART_CAPS_MAX_SEPARATORS)
                            {
                                s_smartcaps_arr_seps[s_smartcaps_num_seps] = kc;
                                s_smartcaps_num_seps++;
                            }
                            return false;
                        }
                    }
                    break;

                case KC_1 ... KC_0:
                case KC_F1 ... KC_F12: s_feature_state |= FEATURE_USED; break;

                case CC_FNAV: // pressed
                    s_feature_state &= ~(FEATURE_CAPS|FEATURE_NUM|FEATURE_USED);
                    s_smartcaps_state = 0;
                    s_smartcaps_num_seps = 0;

                    s_feature_state |= FEATURE_NAV;
                    if (features_active_all(FEATURE_NAV | FEATURE_SYM))
                    {
                        user_layer_on(LAYER_RAISE);
                    }
                    else
                    {
                        user_layer_on(LAYER_NAVIGATION);
                    }
                    break;
                case CC_FSYM: // pressed
                    if (features_active_all(FEATURE_SYM_ONESHOT))
                    {
                        s_feature_state &= ~(FEATURE_USED | FEATURE_SYM | FEATURE_SYM_ONESHOT);
                        if (features_active_all(FEATURE_NUM))
                        {
                            user_layer_on(LAYER_NUMBERS);
                        }
                        else
                        {
                            user_layer_on(LAYER_QWERTY);
                        }
                    }
                    else
                    {
                        s_feature_state |= FEATURE_SYM;
                        s_feature_state &= ~FEATURE_USED;
                        if (features_active_all(FEATURE_SYM | FEATURE_NAV))
                        {
                            user_layer_on(LAYER_RAISE);
                        }
                        else
                        {
                            user_layer_on(LAYER_SYMBOLS);
                        }
                    }
                    break;
                case CC_FNUM:
                    if (features_active_all(FEATURE_CAPS))
                    {
                        s_feature_state &= ~FEATURE_CAPS;
                        s_smartcaps_state = 0;
                        s_smartcaps_num_seps = 0;
                    }

                    if (features_active_all(FEATURE_NUM))
                    {
                        s_feature_state &= ~FEATURE_NUM;
                        user_layer_on(LAYER_QWERTY);
                    }
                    else
                    {
                        s_feature_state &= ~FEATURE_USED;
                        enable_smart_numbers();
                    }
                    break;
                case CC_FCAPS:
                    if (smartcaps_active_any(SMART_CAPS_CAMEL | SMART_CAPS_NORMAL | SMART_CAPS_SNAKE) == false)
                    {
                        s_smartcaps_state = SMART_CAPS_NORMAL;
                        s_smartcaps_num_seps = 1;
                        s_smartcaps_arr_seps[0] = KC_SCLN;
                    }
                    s_smartcaps_state &= ~SMART_CAPS_USED;
                    s_smartcaps_state |= SMART_CAPS_HOLD;
                    s_feature_state |= FEATURE_CAPS;
                    break;
            }
        }
        else
        {
            switch (kc)
            {
                case CC_SHFT:
                case CC_CTRL:
                case CC_ALT:
                case CC_CMD: break;

                case CC_UNDO ... CC_CLOSE: break;

                case KC_MINUS ... KC_SLASH:
                case LSFT(KC_MINUS) ... LSFT(KC_SLASH):
                    if (smartcaps_active_any(SMART_CAPS_NORMAL))
                    {
                        if (!smartcaps_active_any(SMART_CAPS_USED))
                        {
                            return false;
                        }
                    }

                case KC_1 ... KC_0:
                case KC_F1 ... KC_F12:
                case KC_A ... KC_Z:
                case KC_BSPACE:
                case KC_SPACE:
                    if (features_active_all(FEATURE_SYM_ONESHOT) && !features_active_all(FEATURE_NAV_ONESHOT))
                    {
                        s_feature_state &= ~FEATURE_SYM_ONESHOT;
                        user_layer_on(LAYER_QWERTY);
                        if (features_active_all(FEATURE_NUM))
                        {
                            user_layer_on(LAYER_NUMBERS);
                        }
                    }
                    break;

                case CC_FNAV: // released
                    if (features_active_all(FEATURE_NAV | FEATURE_SYM))
                    {
                        user_layer_on(LAYER_SYMBOLS);
                        if (features_active_all(FEATURE_USED))
                        {
                            s_feature_state |= FEATURE_USED;
                            s_feature_state &= ~FEATURE_NAV;
                        }
                        else
                        {
                            s_feature_state &= ~FEATURE_NAV;
                            s_feature_state |= FEATURE_CAPS;
                            s_smartcaps_state = SMART_CAPS_NORMAL;
                            s_smartcaps_state |= SMART_CAPS_HOLD;
                            s_smartcaps_num_seps = 0;
                        }
                    }
                    else if (features_active_all(FEATURE_NAV))
                    {
                        s_feature_state &= ~(FEATURE_NAV);
                        if (features_active_all(FEATURE_SYM_ONESHOT))
                        {
                            s_feature_state &= ~(FEATURE_NUM|FEATURE_CAPS);
                            s_feature_state |= FEATURE_NAV_ONESHOT;
                            user_layer_on(LAYER_RAISE);
                        }
                        else
                        {
                            if (features_active_all(FEATURE_NUM))
                            {
                                if (features_active_all(FEATURE_USED))
                                {
                                    s_feature_state &= ~(FEATURE_NUM|FEATURE_CAPS);
                                    user_layer_on(LAYER_QWERTY);
                                }
                            }
                            else
                            {
                                s_feature_state &= ~(FEATURE_NUM|FEATURE_CAPS);
                                user_layer_on(LAYER_QWERTY);
                            }
                        }
                    }

                    break;

                case CC_FSYM: // released
                    if (features_active_all(FEATURE_NAV | FEATURE_SYM))
                    {
                        s_feature_state &= ~(FEATURE_SYM | FEATURE_SYM_ONESHOT);
                        // Hold NAV + Tap SYM ?
                        if (!features_active_all(FEATURE_USED))
                        {
                            enable_smart_numbers();
                        }
                        else
                        {
                            s_feature_state &= ~(FEATURE_USED);
                            user_layer_on(LAYER_NAVIGATION);
                        }
                    }
                    else if (features_active_all(FEATURE_SYM))
                    {
                        s_feature_state &= ~(FEATURE_SYM | FEATURE_SYM_ONESHOT);
                        if (features_active_all(FEATURE_CAPS))
                        {
                            if (s_smartcaps_num_seps == 0)
                            {
                                s_smartcaps_num_seps = 1;
                                s_smartcaps_arr_seps[0] = KC_UNDS;
                            }
                            s_smartcaps_state &= ~SMART_CAPS_HOLD;
                            user_layer_on(LAYER_QWERTY);
                        }
                        else
                        {
                            if (features_active_all(FEATURE_USED))
                            {
                                s_feature_state &= ~FEATURE_USED;
                                user_layer_on(LAYER_QWERTY);
                                if (features_active_all(FEATURE_NUM))
                                {
                                    user_layer_on(LAYER_NUMBERS);
                                }
                            }
                            else
                            {
                                s_feature_state |= FEATURE_SYM_ONESHOT;
                            }
                        }
                    }
                    break;

                case CC_FNUM: // released
                    if (features_active_all(FEATURE_NUM))
                    {
                        if (features_active_all(FEATURE_USED))
                        {
                            s_feature_state &= ~FEATURE_NUM;
                            user_layer_on(LAYER_QWERTY);
                        }
                    }
                    break;

                case CC_FCAPS: // released
                    s_smartcaps_state &= ~SMART_CAPS_HOLD;
                    if (smartcaps_active_any(SMART_CAPS_USED))
                    {
                        s_feature_state &= ~FEATURE_CAPS;
                        s_smartcaps_state = 0;
                        s_smartcaps_num_seps = 0;
                    }
                    break;
            }
        }
    }

    if (features_active_all(FEATURE_NUM))
    {
        if (kc == KC_SPACE)
        {
            if (record->event.pressed)
            {
                s_feature_state &= ~(FEATURE_NUM|FEATURE_CAPS);
                if (!features_active_all(FEATURE_SYM))
                {
                    user_layer_on(LAYER_QWERTY);
                }
            }
        }
    }
    else if (features_active_all(FEATURE_CAPS))
    {
        {
            if (record->event.pressed)
            {
                // Normal Caps, all letters are emitted in 'upper' case.
                // The ';' symbol is emitted as the '_' symbol.
                // When pressing 'comma' we emit a 'space'
                // When pressing 'dot' we cycle to the next mode
                // When 'space' is pressed smart capslock is disabled.

                if (kc == KC_SPACE)
                {
                    register_keycode_press(kc);
                    // will be handled on release
                }
                else if (kc == KC_DOT)
                {
                    // will be handled on release
                }
                else if (smartcaps_active_all(SMART_CAPS_NORMAL))
                {
                    if (kc >= KC_A && kc <= KC_Z)
                    {
                        register_keycode_press_with_shift(kc);
                    }
                    else
                    {
                        if (kc == KC_COMMA)
                        {
                            kc = KC_SPACE;
                            register_keycode_press(kc);
                        }
                    }
                }
                else if (smartcaps_active_any(SMART_CAPS_CAMEL | SMART_CAPS_SNAKE))
                {
                    // Camel Case, when pressing ';' we register space and mark the next key to be registered with 'shift'.
                    // When pressing 'comma' we mark the next key to be registered with 'shift'.
                    // When pressing 'dot' we cycle to the next mode
                    // When 'space' is pressed smart capslock is disabled.

                    // Snake Case, when pressing ';' we register a '_' and continue
                    // When pressing 'dot' we cycle to the next mode
                    // When 'space' is pressed smart capslock is disabled.
                    if (kc >= KC_A && kc <= KC_Z)
                    {
                        if (smartcaps_active_all(SMART_CAPS_SHIFT))
                        {
                            register_keycode_press_with_shift(kc);
                            s_smartcaps_state &= ~(SMART_CAPS_SHIFT);
                        }
                        else
                        {
                            register_keycode_press(kc);
                        }
                    }
                    else if (kc == KC_SCLN)
                    {
                        if (smartcaps_active_all(SMART_CAPS_CAMEL))
                        {
                            s_smartcaps_state |= SMART_CAPS_SHIFT;
                        }
                    }
                    else if (kc == KC_COMMA)
                    {
                        s_smartcaps_state ^= SMART_CAPS_SHIFT;
                    }
                    else
                    {
                        register_keycode_press(kc);
                    }
                }
            }
            else // record->event.pressed == false
            {
                if (kc == KC_SPACE)
                {
                    register_keycode_release(kc);
                    if (!smartcaps_active_all(SMART_CAPS_HOLD))
                    {
                        s_feature_state &= ~FEATURE_CAPS;
                        s_smartcaps_state = 0;
                        s_smartcaps_num_seps = 0;
                    }
                }
                else if (kc == KC_DOT)
                {
                    s_feature_state &= ~FEATURE_USED;
                    s_smartcaps_num_seps = 0;
                    if (smartcaps_active_any(SMART_CAPS_SNAKE))
                    {
                        s_smartcaps_state &= ~(SMART_CAPS_CAMEL | SMART_CAPS_SHIFT | SMART_CAPS_NORMAL | SMART_CAPS_SNAKE);
                        s_smartcaps_state |= SMART_CAPS_NORMAL;
                        s_smartcaps_num_seps = 1;
                        s_smartcaps_arr_seps[0] = KC_SCLN;
                    }
                    else if (smartcaps_active_any(SMART_CAPS_CAMEL))
                    {
                        s_smartcaps_state &= ~(SMART_CAPS_CAMEL | SMART_CAPS_SHIFT | SMART_CAPS_NORMAL | SMART_CAPS_SNAKE);
                        s_smartcaps_state |= SMART_CAPS_SNAKE;
                        s_smartcaps_num_seps = 1;
                        s_smartcaps_arr_seps[0] = KC_SCLN;
                    }
                    else
                    {
                        s_smartcaps_state &= ~(SMART_CAPS_CAMEL | SMART_CAPS_SHIFT | SMART_CAPS_NORMAL | SMART_CAPS_SNAKE);
                        s_smartcaps_state |= SMART_CAPS_CAMEL;
                        s_smartcaps_state |= SMART_CAPS_SHIFT;
                        s_smartcaps_num_seps = 1;
                        s_smartcaps_arr_seps[0] = KC_SPACE;
                    }
                }
                else if (kc == KC_SCLN)
                {
                    for (int8_t i = 0; i < s_smartcaps_num_seps; ++i)
                    {
                        uint16_t kc = s_smartcaps_arr_seps[i];
                        if (kc == KC_SCLN)
                        {
                            kc = KC_UNDS;
                        }
                        register_keycode_tap(kc);
                    }
                }
                else 
                {
                    // This will unregister the keycode as it was registered when it was pressed.
                    register_keycode_release(kc);
                }
            }
        }

        ret = false;
    }

    return ret;
}
