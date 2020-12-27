#include QMK_KEYBOARD_H
#include "version.h"

extern keymap_config_t keymap_config;

#define _QWERTY_WIN 0
#define _QWERTY_MAC 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 16

static uint16_t key_timer;

enum custom_keycodes {
  QWERTY_WIN = SAFE_RANGE,
  QWERTY_MAC,
  LOWER,
  RAISE,
  ADJUST,
  VRSN,
  G_CX,
  C_CX,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty for Windows
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |   `  |                    |   =  |   6  |   7  |   8  |   9  |   0  |  -   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   [  |                    |   ]  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |   [  |                    |   ]  |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |      | Next |      |  Fn  |      |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-------------+------+------+------+------+      +------+------+------+      +------+------+------+------+-------------|
   * | C_CX | Paste|  Win | LAlt |||||||| Lower| Space| Win+S|||||||| Enter|  F14 | Raise|||||||| RAlt |  BS  | Home | End  |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY_WIN] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,                          KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                         KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,                         KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              LCTL(KC_TAB), KC_HELP,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    C_CX, LCTL(KC_V), KC_LGUI, ALT_T(KC_F15),        LOWER, KC_SPC, LGUI(KC_S),   KC_ENTER, KC_F14, RAISE,      ALT_T(KC_F14), KC_BSPC, KC_HOME, KC_END   \
  ),

  /* Qwerty for Mac
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |   `  |                    |   =  |   6  |   7  |   8  |   9  |   0  |  -   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   [  |                    |   ]  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |   [  |                    |   ]  |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |      | Next |      |  Fn  |      |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-------------+------+------+------+------+      +------+------+------+      +------+------+------+------+-------------|
   * | G_CX | Paste|  Alt |  GUI |||||||| Lower| Space| G+Spc|||||||| Enter| LANG1| Raise|||||||| GUI  |  BS  | Home | End  |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY_MAC] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,                          KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                         KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,                         KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              LCTL(KC_TAB), KC_HELP,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    G_CX, LGUI(KC_V), ALT_T(KC_F1), KC_LGUI,         LOWER, KC_SPC, LGUI(KC_SPC), KC_ENTER, KC_LANG1, RAISE,          KC_RGUI, KC_BSPC, KC_HOME, KC_END   \
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |                    |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      | Left | Down |  Up  | Right|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      | Shift| Prev |      |      |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+   +  +------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      | Space|      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  _______,                       _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, KC_F12,  \
    _______, _______, _______, _______, _______, _______,_______,                       _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    _______, _______, _______, _______, _______, _______,LCTL(LSFT(KC_TAB)),            _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______,LSFT(KC_SPC),_______,  _______,_______, _______,          _______, _______, _______, _______  \
  ),

  /* Raise
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |                    |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      | Left | Down |  Up  | Right|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      | Shift| Prev |      |      |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+   +  +------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      | Space|      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_RAISE] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  _______,                       _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, KC_F12,  \
    _______, _______, _______, _______, _______, _______,_______,                       _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    _______, _______, _______, _______, _______, _______,LCTL(LSFT(KC_TAB)),            _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______,LSFT(KC_SPC),_______,  _______,_______, _______,          _______, _______, _______, _______  \
  ),

  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | Reset| Win  | mac  |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Ver  |      |      |  MsUp|      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |MsLeft|MsDown|MsRght|      |      |                    |      |      |      |      |      |      | Play |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      | Prev | Next |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      | Lclk | Rclk ||||||||      |      |      ||||||||      |      |      |||||||| VolUp| VolDn| Mute |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    RESET,QWERTY_WIN,QWERTY_MAC,_______,_______, _______,_______,                      _______, _______, _______, _______, _______, _______, _______, \
    VRSN,    _______, _______, KC_MS_U, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,_______,                       _______, _______, _______, _______, _______, _______, KC_MPLY, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, KC_MPRV, KC_MNXT, _______, \
    _______, _______, KC_BTN1, KC_BTN2,          _______,_______,_______,       _______,KC_WBAK, _______,          KC_VOLU, KC_VOLD, KC_MUTE, _______  \
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY_WIN:
      if (record->event.pressed) {
        print("mode just switched to windows and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY_WIN);
      }
      return false;
      break;
    case QWERTY_MAC:
      if (record->event.pressed) {
        print("mode just switched to mac and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY_MAC);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
    case G_CX:
      if (record->event.pressed) {
        key_timer = timer_read(); // if the key is being pressed, we start the timer.
      } else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
        if (timer_elapsed(key_timer) < 200) {
          SEND_STRING(SS_LGUI("c"));
        } else {
          SEND_STRING(SS_LGUI("x"));
        }
      }
      return false;
    case C_CX:
      if (record->event.pressed) {
        key_timer = timer_read(); // if the key is being pressed, we start the timer.
      } else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
        if (timer_elapsed(key_timer) < 200) {
          SEND_STRING(SS_LCTRL("c"));
        } else {
          SEND_STRING(SS_LCTRL("x"));
        }
      }
      return false;
  }
  return true;
}
