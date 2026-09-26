#include QMK_KEYBOARD_H
#include "keymap_dvorak.h"
#include "keymap_plover.h"

#include "sendstring_dvorak.h"

#if __has_include("macro.h")
#include "macro.h"
#else
#include "macro_example.h"
#endif

enum custom_keycodes {
  FWDBACK = SAFE_RANGE,

  PLOVER,

  MACRO_MIN,
  MACRO_Q,
  MACRO_L,
  MACRO_K,
  MACRO_D,
  MACRO_P,
  MACRO_MAX,

  TOGGLE_SHIFT_MIN,
  TOGGLE_SHIFT_KC_1,
  TOGGLE_SHIFT_KC_2,
  TOGGLE_SHIFT_KC_3,
  TOGGLE_SHIFT_KC_4,
  TOGGLE_SHIFT_KC_5,
  TOGGLE_SHIFT_KC_6,
  TOGGLE_SHIFT_KC_7,
  TOGGLE_SHIFT_KC_8,
  TOGGLE_SHIFT_KC_9,
  TOGGLE_SHIFT_KC_0,
  TOGGLE_SHIFT_MAX,

  NEW_SAFE_RANGE, // set new safe range
};

_Static_assert(NEW_SAFE_RANGE <= (uint16_t) QK_USER_MAX,
        "Too many codes, they don't fit in the allotted space");

/* TMK limits this to 32 */
/* Most actions limit to 16 */
enum layer_id {
    LAYER_BASE = 0,
    LAYER_TRANSPARENT = 1,
    LAYER_HARDWARE_DVORAK = 2,
    LAYER_QWERTY = 3,
    LAYER_PLOVER = 4,
    LAYER_NUMPAD = 5,
    LAYER_MOVEMENT = 6,
    LAYER_BLUESHIFT = 7,
    LAYER_FKEYS = 8,
};

#define TSFT_1  TOGGLE_SHIFT_KC_1
#define TSFT_2  TOGGLE_SHIFT_KC_2
#define TSFT_3  TOGGLE_SHIFT_KC_3
#define TSFT_4  TOGGLE_SHIFT_KC_4
#define TSFT_5  TOGGLE_SHIFT_KC_5
#define TSFT_6  TOGGLE_SHIFT_KC_6
#define TSFT_7  TOGGLE_SHIFT_KC_7
#define TSFT_8  TOGGLE_SHIFT_KC_8
#define TSFT_9  TOGGLE_SHIFT_KC_9
#define TSFT_0  TOGGLE_SHIFT_KC_0

// Tri-layer is handled for these in post_process_record_user, so use LT macros
// to make these codes different from the single TT ones.
#define TWOLAYER_NUM_FN LT(LAYER_NUMPAD,    KC_NO)
#define TWOLAYER_BLU_FN LT(LAYER_BLUESHIFT, KC_NO)

#define NUM_FN TWOLAYER_NUM_FN
#define BLU_FN TWOLAYER_BLU_FN

#define TO_BASE TO(LAYER_BASE)
#define TT_BLUE TT(LAYER_BLUESHIFT)
#define TT_NUM TT(LAYER_NUMPAD)
#define LT_MOVE LT(LAYER_MOVEMENT, KC_F21)
#define ALTTAB LGUI(KC_TAB)

#define LCURLY LSFT(DV_LBRC)
#define RCURLY LSFT(DV_RBRC)

#define SCRNSVR LCTL(LGUI(DV_O))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Default Layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |   ~    |   1  |   2  |   3  |   4  |   5  |   \  |           |   '  |   6  |   7  |   8  |   9  |   0  |   =    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   W  |   E  |   R  |   T  | ~Fn1 |           | ~Fn3 |   Y  |   U  |   I  |   O  |   P  |   [    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | LShift |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | RShift |
     * |--------+------+------+------+------+------|  Fn0 |           | ~Fn4 |------+------+------+------+------+--------|
     * | LCtrl  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RCtrl  |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | ~Fn1 | ~Fn2 | Caps | LAlt | LGui |                                       |  Lft |  Up  |  Dn  | Rght | ~Fn4 |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | +Fn2 | Home |       | PgUp | Del  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |  End |       | PgDn |      |      |
     *                                 | BkSp |  ESC |------|       |------| Enter| Space|
     *                                 |      |      |  Spc |       | Ins  |      |      |
     *                                 `--------------------'       `--------------------'
     */

    // BASE LAYERS

    [LAYER_BASE] = LAYOUT_ergodox(  // software Dvorak, with symbol row reversed
        // left hand
        KC_ESC, TSFT_1,     TSFT_2,     TSFT_3,     TSFT_4,     TSFT_5, KC_F17,
        KC_TAB, DV_QUOT,    DV_COMM,    DV_DOT,     DV_P,       DV_Y,   LT_MOVE,
        KC_LSFT,SFT_T(DV_A),CTL_T(DV_O),ALT_T(DV_E),GUI_T(DV_U),DV_I,
        KC_LCTL,DV_SCLN,    DV_Q,       DV_J,       DV_K,       DV_X,   KC_DEL,
        NUM_FN, BLU_FN,     KC_LCTL,    KC_LALT,    KC_LGUI,
                                                PLOVER, QK_LEAD,
                                                        KC_F16,
                                        KC_BSPC,KC_LSFT,NUM_FN,
        // right hand
                KC_F18, TSFT_6, TSFT_7,     TSFT_8,     TSFT_9,     TSFT_0,     KC_MPLY,
                TT_NUM, DV_F,   DV_G,       DV_C,       DV_R,       DV_L,       FWDBACK,
                        DV_D,   GUI_T(DV_H),ALT_T(DV_T),CTL_T(DV_N),SFT_T(DV_S),KC_RSFT,
                KC_DEL, DV_B,   DV_M,       DV_W,       DV_V,       DV_Z,       KC_RCTL,
                                KC_RGUI,    KC_RALT,    KC_RCTL,    ALTTAB,     LT_MOVE,
        SCRNSVR,KC_MPLY,
        KC_F14,
        KC_ENT, TT_BLUE,KC_SPC
    ),

    [LAYER_TRANSPARENT] = LAYOUT_ergodox(  // I trigger this more often than I'd like
        // left hand
        _______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,
                                                _______,_______,
                                                        _______,
                                        _______,_______,_______,
        // right hand
                _______,_______,_______,_______,_______,_______,_______,
                _______,_______,_______,_______,_______,_______,_______,
                        _______,_______,_______,_______,_______,_______,
                _______,_______,_______,_______,_______,_______,_______,
                                _______,_______,_______,_______,_______,
        _______,_______,
        _______,
        _______,_______,_______
    ),

    [LAYER_HARDWARE_DVORAK] = LAYOUT_ergodox(
        // left hand
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_BSLS,
        KC_TAB, KC_QUOT,KC_COMM,KC_DOT, KC_P,   KC_Y,   LT_MOVE,
        KC_LSFT,KC_A,   KC_O,   KC_E,   KC_U,   KC_I,
        KC_LCTL,KC_SCLN,KC_Q,   KC_J,   KC_K,   KC_X,   KC_DEL,
        NUM_FN, BLU_FN, KC_LCTL,KC_LALT,KC_LGUI,
                                                PLOVER, KC_HOME,
                                                        KC_END,
                                        KC_BSPC,KC_LSFT,KC_LGUI,
        // right hand
                KC_MINS,KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_EQL,
                TT_NUM, KC_F,   KC_G,   KC_C,   KC_R,   KC_L,   KC_SLSH,
                        KC_D,   KC_H,   KC_T,   KC_N,   KC_S,   KC_RSFT,
                KC_DEL, KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,   KC_RCTL,
                                KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,LT_MOVE,
        KC_PGUP,KC_MPLY,
        KC_PGDN,
        KC_ENT, TT_BLUE,KC_SPC
    ),

    [LAYER_QWERTY] = LAYOUT_ergodox(
        // left hand
        _______,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   _______,
        _______,KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   _______,
        _______,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
        _______,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   _______,
        _______,_______,_______,_______,_______,
                                                _______,_______,
                                                        _______,
                                        _______,_______,_______,
        // right hand
                _______,KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,
                _______,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_RBRC,
                        KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_RSFT,
                _______,KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
                                _______,_______,_______,_______,_______,
        _______,_______,
        _______,
        _______,_______,_______
    ),

    // PLOVER (SPECIAL CASE)

    [LAYER_PLOVER] = LAYOUT_ergodox(
        // transparencies are for media keys

        // left hand
        PLOVER, XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
        XXXXXXX,PV_NUM, PV_NUM, PV_NUM, PV_NUM, PV_NUM, XXXXXXX,
        _______,PV_LS,  PV_LT,  PV_LP,  PV_LH,  PV_STAR,
        XXXXXXX,PV_LS,  PV_LK,  PV_LW,  PV_LR,  PV_STAR,XXXXXXX,
        XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
                                                PLOVER, XXXXXXX,
                                                        XXXXXXX,
                                        PV_A,   PV_O,   XXXXXXX,
        // right hand
                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,
                XXXXXXX,PV_NUM, PV_NUM, PV_NUM, PV_NUM, PV_NUM, _______,
                        PV_STAR,PV_RF,  PV_RP,  PV_RL,  PV_RT,  PV_RD,
                XXXXXXX,PV_STAR,PV_RR,  PV_RB,  PV_RG,  PV_RS,  PV_RZ,
                                _______,_______,XXXXXXX,XXXXXXX,XXXXXXX,
        _______,_______,
        _______,
        XXXXXXX,PV_E,   PV_U
    ),

    // MODIFIERS THAT MIGHT BE STICKY

    [LAYER_NUMPAD] = LAYOUT_ergodox(  // mouse + numpad
        #define NUM_CLN LSFT(DV_SCLN)
        // left hand
        TO_BASE,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_PAUS,KC_PSCR,
        _______,XXXXXXX,MS_WHLU,MS_UP,  MS_WHLD,MS_BTN2,_______,
        _______,XXXXXXX,MS_LEFT,MS_DOWN,MS_RGHT,MS_BTN1,
        _______,NUM_CLN,XXXXXXX,XXXXXXX,XXXXXXX,MS_BTN3,_______,
        _______,_______,_______,_______,_______,
                                                _______,_______,
                                                        _______,
                                        _______,_______,_______,
        // right hand
                KC_SCRL,KC_NUM, KC_EQL, KC_PSLS,KC_PAST,KC_PMNS,_______,
                _______,KC_BSPC,KC_P7,  KC_P8,  KC_P9,  KC_PMNS,KC_BSPC,
                        KC_BSPC,KC_P4,  KC_P5,  KC_P6,  KC_PMNS,KC_PENT,
                KC_BSPC,KC_BSPC,KC_P1,  KC_P2,  KC_P3,  KC_PPLS,KC_PENT,
                                KC_P0,  DV_COMM,KC_PDOT,KC_PENT,KC_PENT,
        _______,_______,
        _______,
        KC_ENT, _______,_______
    ),

    [LAYER_MOVEMENT] = LAYOUT_ergodox(  // F-keys + cursor
        // left hand
        TO_BASE,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
        QK_BOOT,XXXXXXX,KC_PGUP,KC_UP,  KC_PGDN,XXXXXXX,_______,
        _______,KC_HOME,KC_LEFT,KC_DOWN,KC_RGHT,KC_END,
        _______,XXXXXXX,XXXXXXX,KC_END, KC_HOME,NK_TOGG,_______,
        _______,_______,_______,MACRO_Q,MACRO_K,
                                                _______,_______,
                                                        _______,
                                        KC_LCTL,KC_LSFT,_______,
        // right hand
                KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_MINS,
                _______,XXXXXXX,KC_PGUP,KC_UP,  KC_PGDN,XXXXXXX,QK_BOOT,
                        KC_HOME,KC_LEFT,KC_DOWN,KC_RGHT,KC_END, _______,
                _______,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,
                                KC_RGUI,KC_RALT,_______,_______,_______,
        _______,_______,
        _______, _______,KC_RSFT,KC_RCTL
    ),

    [LAYER_BLUESHIFT] = LAYOUT_ergodox(  // "BlueShift"
        // left hand
        TO_BASE,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
        _______,KC_TILD,LCURLY, RCURLY, KC_PSCR,KC_BSLS,_______,
        _______,KC_APP, KC_TAB, DV_EQL, DV_MINS,KC_INS,
        _______,_______,DV_GRV, DV_LBRC,DV_RBRC,KC_CAPS,_______,
        _______,_______,_______,_______,_______,
                                                _______,_______,
                                                        _______,
                                        KC_ESC ,_______,_______,
        // right hand
                KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, _______,
                _______,KC_PGUP,KC_HOME,KC_UP,  KC_END, DV_SLSH,_______,
                        KC_PGDN,KC_LEFT,KC_DOWN,KC_RGHT,DV_MINS,_______,
                _______,_______,XXXXXXX,KC_UP,  XXXXXXX,_______,_______,
                                KC_LEFT,KC_DOWN,KC_RGHT,_______,_______,
        _______,_______,
        _______,
        _______,_______,_______
    ),

    // MODIFIERS THAT WON'T BE STICKY

    [LAYER_FKEYS] = LAYOUT_ergodox(  // F-keys only
        // left hand
        TO_BASE,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
        _______,KC_F13, KC_F14, KC_F15, KC_F16, XXXXXXX,_______,
        _______,KC_F17, KC_F18, KC_F19, KC_F20, XXXXXXX,
        _______,KC_F21, KC_F22, KC_F23, KC_F24, XXXXXXX,_______,
        _______,_______,_______,KC_LALT,KC_LGUI,
                                                _______,_______,
                                                        _______,
                                        KC_LCTL,KC_LSFT,_______,
        // right hand
                XXXXXXX,XXXXXXX,KC_F10, KC_F11, KC_F12, XXXXXXX,_______,
                _______,XXXXXXX,KC_F7,  KC_F8,  KC_F9,  XXXXXXX,_______,
                        XXXXXXX,KC_F4,  KC_F5,  KC_F6,  XXXXXXX,_______,
                _______,XXXXXXX,KC_F1,  KC_F2,  KC_F3,  XXXXXXX,_______,
                                KC_RGUI,KC_RALT,KC_RCTL,_______,_______,
        _______,_______,
        _______,
        _______,KC_RSFT,KC_RCTL
    ),
};

void function_plover_key(keyrecord_t *record)
{
    if (record->event.pressed) return;
    layer_invert(LAYER_PLOVER);
    bool turning_on = IS_LAYER_ON(LAYER_PLOVER);
    if (turning_on) {
        // PHRO*PB
        register_code(PV_LP); register_code(PV_LH); register_code(PV_LR);
        register_code(PV_O); register_code(PV_RP); register_code(PV_RB);
        register_code(PV_STAR);
        unregister_code(PV_LP); unregister_code(PV_LH); unregister_code(PV_LR);
        unregister_code(PV_O); unregister_code(PV_RP); unregister_code(PV_RB);
        unregister_code(PV_STAR);
    } else {
        // PHRO*F
        register_code(PV_LP); register_code(PV_LH); register_code(PV_LR);
        register_code(PV_O); register_code(PV_STAR); register_code(PV_RF);
        unregister_code(PV_LP); unregister_code(PV_LH); unregister_code(PV_LR);
        unregister_code(PV_O); unregister_code(PV_STAR); unregister_code(PV_RF);
    }
}

// KEY OVERRIDES (docs/features/key_overrides.md)

// When GUI is on, ESC yields ` (MacOS window switching)
const key_override_t grave_esc_override = ko_make_basic(MOD_MASK_GUI, KC_ESC, G(KC_GRV));

// When GUI is on, apostrophe yields ` (MacOS window switching)
const key_override_t grave_apostrophe_override = ko_make_basic(MOD_MASK_GUI, DV_QUOT, G(KC_GRV));

const key_override_t *key_overrides[] = {
    &grave_esc_override,
    &grave_apostrophe_override,
};

// Mapping function to link up custom shift keycodes with the relevant key to shift.
uint8_t shift_custom_keycode_to_keycode(uint16_t param) {
    switch (param) {
        case TOGGLE_SHIFT_KC_1: return KC_1;
        case TOGGLE_SHIFT_KC_2: return KC_2;
        case TOGGLE_SHIFT_KC_3: return KC_3;
        case TOGGLE_SHIFT_KC_4: return KC_4;
        case TOGGLE_SHIFT_KC_5: return KC_5;
        case TOGGLE_SHIFT_KC_6: return KC_6;
        case TOGGLE_SHIFT_KC_7: return KC_7;
        case TOGGLE_SHIFT_KC_8: return KC_8;
        case TOGGLE_SHIFT_KC_9: return KC_9;
        case TOGGLE_SHIFT_KC_0: return KC_0;
        default: return KC_NO;
    };
};

void function_toggle_shift(keyrecord_t *record, uint16_t custom_keycode)
{
    if (!record->event.pressed) return; // tap these keys only when they're pressed
    const uint8_t keycode = shift_custom_keycode_to_keycode(custom_keycode);
    if (keycode == KC_NO) return;
    uint8_t savedmods = get_mods();
    action_t action = {.code = ACTION_MODS_KEY(savedmods ? 0 : MOD_LSFT, keycode)};
    bool shift_pressed = savedmods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
    if (shift_pressed) {
        del_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
        send_keyboard_report();
    }
    process_action(record, action);
    record->event.pressed = false;
    process_action(record, action);
    record->event.pressed = true;
    if (shift_pressed) {
        set_mods(savedmods);
        send_keyboard_report();
    }
}

void function_send_macro(keyrecord_t *record, uint16_t keycode)
{
    if (!record->event.pressed) return;
    switch (keycode) {
        case MACRO_Q: MACRO_DEF_Q;
        case MACRO_L: MACRO_DEF_L;
        case MACRO_K: MACRO_DEF_K;
        case MACRO_D: MACRO_DEF_D;
        case MACRO_P: MACRO_DEF_P;
        default:
            print("Unknown macro called\n");
            print("keycode  = "); print_hex8(keycode); print("\n");
            return;
    }
}

/* override hook */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case FWDBACK:
            // Next track, or previous track if shift is pressed.
            if (!record->event.pressed) return false;
            uint8_t savedmods = get_mods();
            bool shift_pressed = savedmods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
            if (shift_pressed) {
                del_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
                send_keyboard_report();
            }
            uint8_t fwd_or_back = shift_pressed ? KC_MEDIA_PREV_TRACK : KC_MEDIA_NEXT_TRACK;
            tap_code(fwd_or_back);
            if (shift_pressed) {
                set_mods(savedmods);
                send_keyboard_report();
            }
            return false;
        case PLOVER:
            function_plover_key(record);
            return false;
        case TOGGLE_SHIFT_MIN ... TOGGLE_SHIFT_MAX:
            function_toggle_shift(record, keycode);
            return false;
        case MACRO_MIN ... MACRO_MAX:
            function_send_macro(record, keycode);
            return false;
        default:
            return true;
    }
}

/* override hook */
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case TWOLAYER_BLU_FN:
        case TWOLAYER_NUM_FN:
            print("Before tri-layer...\n");
            xprintf("%08lX(%u)\n", (uint32_t)layer_state, get_highest_layer(layer_state));
            update_tri_layer(LAYER_BLUESHIFT, LAYER_NUMPAD, LAYER_FKEYS);
            print("After tri-layer...\n");
            xprintf("%08lX(%u)\n", (uint32_t)layer_state, get_highest_layer(layer_state));
            return;
    }
}

/* override hook */
void keyboard_post_init_user(void)
{
    // blink light once
    ergodox_board_led_on();
    _delay_ms(250);
    ergodox_board_led_off();

    // Debug
    print("using macro range"); print("\n");
    print("safe_range  = "); print_hex8(SAFE_RANGE); print("\n");
    print("new safe_range  = "); print_hex8(NEW_SAFE_RANGE); print("\n");
}

/* override hook */
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t highest_layer = biton32(state);

    switch (highest_layer) {
        case 0:
            ergodox_board_led_off();
            break;
        default:
            ergodox_board_led_on();
            break;
    }

    return state;
}

void leader_end_user(void) {
    if (leader_sequence_one_key(DV_Q)) {
        MACRO_DEF_Q;
    } else if (leader_sequence_one_key(DV_SCLN)) {
        MACRO_DEF_Q_S;
    } else if (leader_sequence_one_key(DV_L)) {
        MACRO_DEF_L;
    } else if (leader_sequence_one_key(DV_D)) {
        MACRO_DEF_D;
    } else if (leader_sequence_one_key(DV_K)) {
        MACRO_DEF_K;
    } else if (leader_sequence_one_key(DV_P)) {
        MACRO_DEF_P;
    }
}

// vim:shiftwidth=4:cindent:expandtab:tabstop=4
