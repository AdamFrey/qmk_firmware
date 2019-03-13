#include QMK_KEYBOARD_H
#include "led.h"

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

#include "backlight.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-------------------.
   * |Esc |TAB | FN | BS |
   * |----|----|----|----|
   * | NL | /  | *  | -  |
   * |----|----|----|----|
   * | 7  | 8  | 9  |    |
   * |----|----|----| +  |
   * | 4  | 5  | 6  |    |
   * |----|----|----|----|
   * | 1  | 2  | 3  |    |
   * |----|----|----| En |
   * | FN | 0  | .  |    |
   * `-------------------'
   */

[_BL] = LAYOUT_numpad_6x4v2(
  KC_ESC,   KC_TAB,   MO(_FL),   KC_BSPC, \
  KC_NLCK,  KC_PSLS,  KC_PAST,   KC_PMNS, \
  KC_P7,    KC_P8,    KC_P9,              \
  KC_P4,    KC_P5,    KC_P6,     KC_PPLS, \
  KC_P1,    KC_P2,    KC_P3,              \
  MO(_FL),  KC_P0,    KC_PDOT,   KC_PENT),

  /* Keymap _FL: Function Layer
   * ,-------------------.
   * |RGBT|TAB | FN | BS |
   * |----|----|----|----|
   * |RGBM|RGBP|BTOG| -  |
   * |----|----|----|----|
   * |ShTb|UP  |TAB |    |
   * |----|----|----| +  |
   * |<-  |Down|->  |    |
   * |----|----|----|----|
   * |SPC |VAS | BS |    |
   * |----|----|----| En |
   * | FN |    |RST |    |
   * `-------------------'
   */
[_FL] = LAYOUT_numpad_6x4v2(
  RGB_TOG,      KC_TAB,   KC_TRNS,   KC_BSPC, \
  RGB_MOD,      BL_DEC,  BL_TOGG,   KC_PMNS, \
  LSFT(KC_TAB), KC_UP,    KC_TAB,   \
  KC_LEFT,      KC_DOWN,  KC_RIGHT,    KC_PPLS, \
  KC_SPACE,     RGB_VAI,  KC_BSPC,              \
  KC_P0,        KC_P0,    RESET,     KC_PENT),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {
      case BL_TOGG:
         if (record->event.pressed) {
            cospad_bl_led_togg();
         }
         return false;
      case BL_ON:
         if (record->event.pressed) {
            cospad_bl_led_on();
         }
         return false;
      case BL_OFF:
         if(record->event.pressed) {
            cospad_bl_led_off();
         }
         return false;
      default:
         return true;
   }
}

void keyboard_post_init_user(void) {
  // Underglow
  rgblight_enable();
  rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
  rgblight_setrgb_purple();
  // Backlight
  backlight_level(1);
  backlight_enable();
}
