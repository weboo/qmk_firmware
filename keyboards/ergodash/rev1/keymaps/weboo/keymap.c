#include QMK_KEYBOARD_H
#include "version.h"
#include "nicola.h"
NGKEYS nicola_keys;

extern keymap_config_t keymap_config;

enum keymap_layers {
  _QWERTY_WIN,
  _QWERTY_MAC,
  _NICOLA,
  _LOWER,
  _RAISE,
  _ADJUST,
};

static uint16_t key_timer;

enum custom_keycodes {
  QWERTY_WIN = NG_SAFE_RANGE,
  QWERTY_MAC,
  LOWER,
  RAISE,
  VRSN,
  G_CX,
  C_CX,
  KANA,
  EISU,
};

// Tap Dance definitions
enum {
  TD_COPY_CUT,
};
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_COPY_CUT] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_C), LCTL(KC_X)),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty for Windows
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |   `  |                    |   =  |   6  |   7  |   8  |   9  |   0  |  -   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   [  |                    |   ]  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | LCtrl|   A  |   S  |   D  |   F  |   G  |   [  |                    |   ]  |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |      | Next |      | ^C/X |      |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-------------+------+------+------+------+      +------+------+------+      +------+------+------+------+-------------|
   * | PgUp | PgDn |  Win | EISU |||||||| Lower| Space| Win+S|||||||| Enter| RCtrl| Raise|||||||| KANA |  BS  | Home | End  |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY_WIN] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,                          KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                         KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,                         KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            LCTL(KC_TAB), TD(TD_COPY_CUT),    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    KC_PGUP,KC_PGDOWN,KC_LGUI, EISU,            LOWER,    KC_SPC, LGUI(KC_S),   KC_ENTER,  KC_RCTL, RAISE,             KANA,    KC_BSPC, KC_HOME, KC_END   \
  ),

  /* Qwerty for Mac
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |   `  |                    |   =  |   6  |   7  |   8  |   9  |   0  |  -   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   [  |                    |   ]  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |   [  |                    |   ]  |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |      | Next |      | G+C/X|      |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-------------+------+------+------+------+      +------+------+------+      +------+------+------+------+-------------|
   * | PgUp | PgDn |  Alt |  GUI |||||||| Lower| Space| G+Spc|||||||| Enter| LANG1| Raise|||||||| GUI  |  BS  | Home | End  |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY_MAC] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,                          KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,                         KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,                         KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            LCTL(KC_TAB), G_CX,               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    KC_PGUP,KC_PGDOWN,ALT_T(KC_F1), KC_LGUI,     LOWER,   KC_SPC, LGUI(KC_SPC), KC_ENTER, KC_LANG1, RAISE,            KC_RGUI, KC_BSPC, KC_HOME, KC_END   \
  ),

  /* NICOLA
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |   .  |  ka  |  ta  |  ko  |  sa  |      |                    |      |  ra  |  ti  |  ku  |  tu  |   ,  |      |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |   u  |  si  |  te  |  ke  |  se  |      |                    |      |  ha  |  to  |  ki  |   i  |  nn  |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |   .  |  hi  |  su  |  hu  |  he  |      |      |      |      |      |  me  |  so  |  ne  |  ho  |   /  |      |
   * |-------------+------+------+------+------+      +------+------+------+      +------+------+------+------+-------------|
   * |      |      |      |      ||||||||      | OyaL |      ||||||||      | OyaR |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_NICOLA] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, \
    _______, NG_Q,    NG_W,    NG_E,    NG_R,    NG_T,    _______,                   _______, NG_Y,    NG_U,    NG_I,    NG_O,    NG_P,    _______, \
    _______, NG_A,    NG_S,    NG_D,    NG_F,    NG_G,    _______,                   _______, NG_H,    NG_J,    NG_K,    NG_L,    NG_SCLN, _______, \
    _______, NG_Z,    NG_X,    NG_C,    NG_V,    NG_B,              _______,_______,          NG_N,    NG_M,    NG_COMM, NG_DOT,  NG_SLSH, _______, \
    _______, _______, _______, _______,          _______, NG_SHFTL, _______,_______,NG_SHFTR, _______,          _______, _______, _______, _______ \
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |                    |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      | Home | PgUp | PgDn | End  |      |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      | Left | Down |  Up  | Right|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      | Shift| Prev |      | Paste|      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+   +  +------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      | Space|      ||||||||      |      |      ||||||||      | Del  |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  _______,                       _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
    _______, _______, _______, _______, _______, _______,_______,                       _______, KC_HOME, KC_PGUP,KC_PGDOWN,KC_END,  _______, KC_F12,  \
    _______, _______, _______, _______, _______, _______,_______,                       _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    _______, _______, _______, _______, _______, _______,LCTL(LSFT(KC_TAB)),         LCTL(KC_V), _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______,LSFT(KC_SPC),_______,  _______,_______, _______,          _______, KC_DEL,  _______, _______  \
  ),

  /* Raise
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |                    |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      | Home | PgUp | PgDn | End  |      |  F12 |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      | Left | Down |  Up  | Right|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      | Shift| Prev |      | Paste|      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+   +  +------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      | Space|      ||||||||      |      |      ||||||||      | Del  |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_RAISE] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  _______,                       _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
    _______, _______, _______, _______, _______, _______,_______,                       _______, KC_HOME, KC_PGUP,KC_PGDOWN,KC_END,  _______, KC_F12,  \
    _______, _______, _______, _______, _______, _______,_______,                       _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
    _______, _______, _______, _______, _______, _______,LCTL(LSFT(KC_TAB)),         LCTL(KC_V), _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______,LSFT(KC_SPC),_______,  _______,_______, _______,          _______, KC_DEL,  _______, _______  \
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
    RESET,QWERTY_WIN,QWERTY_MAC,_______,_______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    VRSN,    _______, _______, KC_MS_U, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,_______,                       _______, _______, _______, _______, _______, _______, KC_MPLY, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, KC_MPRV, KC_MNXT, _______, \
    _______, _______, KC_BTN1, KC_BTN2,          _______,_______,_______,       _______,KC_WBAK, _______,          KC_VOLU, KC_VOLD, KC_MUTE, _______  \
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void matrix_init_user(void) {
  set_nicola(_NICOLA);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY_WIN:
      if (record->event.pressed) {
        print("mode just switched to windows and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY_WIN);
      }
      return false;
    case QWERTY_MAC:
      if (record->event.pressed) {
        print("mode just switched to mac and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY_MAC);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
    case G_CX:
      if (record->event.pressed) {
        key_timer = timer_read();
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          SEND_STRING(SS_LGUI("c"));
        } else {
          SEND_STRING(SS_LGUI("x"));
        }
      }
      return false;
    case C_CX:
      if (record->event.pressed) {
        key_timer = timer_read();
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          SEND_STRING(SS_LCTRL("c"));
        } else {
          SEND_STRING(SS_LCTRL("x"));
        }
      }
      return false;
    case KANA:
      // 長押しでAlt、単押しでAlt+F14かつNICOLAレイヤーに切り替え
      // Alt+F14を変換キーに割り当てること
      if (record->event.pressed) {
        key_timer = timer_read();
        register_code(KC_RALT);
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          nicola_on();
          tap_code(KC_F14);
        } else {
          // メニューにフォーカスが当たるのを防ぐ
          tap_code(KC_LSFT);
        }
        unregister_code(KC_RALT);
      }
      return false;
    case EISU:
      // 長押しでAlt、単押しでAlt+F15かつNICOLAレイヤーから戻る
      // Alt+F15を無変換キーに割り当てること
      if (record->event.pressed) {
        key_timer = timer_read();
        register_code(KC_LALT);
      } else {
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          nicola_off();
          tap_code(KC_F15);
        } else {
          // メニューにフォーカスが当たるのを防ぐ
          tap_code(KC_LSFT);
        }
        unregister_code(KC_LALT);
      }
      return false;
  }

  bool processed = true;
  if (nicola_state()) {
    nicola_mode(keycode, record);
    processed = process_nicola(keycode, record);
  }
  if (processed == false) return false;

  return true;
}
