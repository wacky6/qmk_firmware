#include "xd60.h"
#include "action_layer.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // 0: Base Layer, Windows Layer
  #define WIN_LAYER (0)
  KEYMAP(
      F(24),   KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_GRV,   KC_BSPC,   \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC,           KC_BSLS,   \
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_NO,             KC_ENT,    \
      KC_LSFT, KC_NO,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,    KC_DEL,    \
      KC_NO,   KC_LGUI, KC_LALT,                             KC_SPC,                       KC_RCTL, F(0),     KC_LEFT, KC_DOWN,  KC_RIGHT),

  //
  // TODO: Windows ALT Layer to emulate Mac OS X Cmd+? keys
  //       May consume lots of FN keys ??
  //

  // 1: Base Layer, Mac OS
  #define MAC_LAYER (1)
  KEYMAP(
      F(24),   KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_GRV,   KC_BSPC,    \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC,           KC_BSLS,   \
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_NO,             KC_ENT,    \
      KC_LSFT, KC_NO,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,    KC_DEL,    \
      KC_CAPS, KC_LALT, KC_LGUI,                          KC_SPC,                          KC_RGUI, F(0),     KC_LEFT, KC_DOWN,  KC_RIGHT),

  // 2: Function Layer
  #define FN_LAYER (2)
  KEYMAP(
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_F13,   KC_DEL,    \
      F(16),   KC_WH_U, KC_UP,   KC_WH_D, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_MPRV,  KC_MNXT,           KC_TRNS,   \
      KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,           LCTL(KC_ENTER),   \
      KC_LSFT, KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE,  KC_TRNS, KC_PGUP,  F(8),   \
      KC_TRNS, KC_TRNS, KC_TRNS,                          F(31),                                KC_TRNS, F(0),     KC_HOME, KC_PGDN,  KC_END),

};

enum function_id {
    ESC_TILD,
    TOGGLE_X3_REPAIR,
    BASE_LAYER_MAC,
    INTELI_LEFT,
    INTELI_RIGHT,
    TOGGLE_BACKLIGHT
};

// Custom Actions
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(FN_LAYER),    // Toggle Fn overlay
    [8] = ACTION_FUNCTION(TOGGLE_X3_REPAIR),   // Toggle Ctrl / Ctrl-J Press (Play X3 Happily!)
    [16] = ACTION_FUNCTION(BASE_LAYER_MAC),    // Set base layer to mac
    [24] = ACTION_FUNCTION(ESC_TILD),
    [31] = ACTION_FUNCTION(TOGGLE_BACKLIGHT)
};

// Macros
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) { register_code(KC_RSFT); }
      else { unregister_code(KC_RSFT); }
      break;
  }

  return MACRO_NONE;
};

#define default_layer_is_on(layer) ( default_layer_state & (1<<layer) )
uint8_t determine_backlit_base(void) {
    if (default_layer_is_on(MAC_LAYER))
        return 1;
    return 0;
}

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK  (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL))
#define MODS_ALT_MASK   (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))
#define IS_SHIFT        ( get_mods() & MODS_SHIFT_MASK )
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    static uint8_t registered_esc_tild;
    static uint8_t x3_super_repair = 0;
    switch (id) {
        case ESC_TILD:
            if (record->event.pressed) {
                registered_esc_tild = IS_SHIFT ? KC_GRV : KC_ESC;
                register_code(registered_esc_tild);
            } else {
                unregister_code(registered_esc_tild);
            }
        break;
        case BASE_LAYER_MAC:
            if (record->event.pressed) {
                default_layer_xor(1UL << MAC_LAYER);
                backlit_base = determine_backlit_base();
                set_backlit();
            }
        break;
        case TOGGLE_BACKLIGHT:
            if (record->event.pressed) {
                rgblight_toggle();
            }
        break;
        case TOGGLE_X3_REPAIR:
            // Ctrl is alway pressed (Fire repair laser)
            // If Alt is pressed when toggling on, also hold J (SETA Acceleration)
            if (record->event.pressed) {
                if (!x3_super_repair) {
                    register_code(KC_LCTL);
                    x3_super_repair = 1;
                    if (get_mods() & MODS_ALT_MASK) {
                        register_code(KC_J);
                        x3_super_repair = 2;
                    }
                } else {
                    unregister_code(KC_LCTL);
                    if (x3_super_repair & 2) {
                        unregister_code(KC_J);
                    }
                    x3_super_repair = 0;
                }
            }
        break;
    }
}

// Loop
void matrix_scan_user(void) {
    backlit_base = determine_backlit_base();
    set_backlit();
};
