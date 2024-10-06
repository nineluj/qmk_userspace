/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
 * Copyright 2024 nineluj <code@nineluj.com> (@nineluj)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FUNCTION,
    LAYER_NAVIGATION,
    LAYER_MEDIA,
    LAYER_POINTER,
    LAYER_NUMERAL,
    LAYER_SYMBOLS,
};

// Automatically enable sniping-mode on the pointer layer.
// #define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// sm_td setup
#define MAX_DEFERRED_EXECUTORS 10

enum custom_keycodes {
    SMTD_KEYCODES_BEGIN = SAFE_RANGE,
    // left hand hrm
    CKC_A, // reads as C(ustom) + KC_A, but you may give any name here
    CKC_R,
    CKC_S,
    CKC_T,
    // right hand hrm
    CKC_N,
    CKC_E,
    CKC_I,
    CKC_O,
    // left thumb cluster
    /* LT_OUT, // not used due to encoder */
    LT_MID,
    LT_INR,
    // right thumb cluster
    RT_INR,
    RT_MID,
    RT_OUT,

    // pointer
    CKC_Z,
    CKC_SLSH,

    SMTD_KEYCODES_END,
};
#include "sm_td.h"

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        // left hand hrm
        SMTD_MT(CKC_A, KC_A, KC_LEFT_ALT)
        SMTD_MT(CKC_R, KC_R, KC_LEFT_GUI)
        SMTD_MT(CKC_S, KC_S, KC_LEFT_CTRL)
        SMTD_MT(CKC_T, KC_T, KC_LSFT)
        // right hand hrm
        SMTD_MT(CKC_N, KC_N, KC_LSFT)
        SMTD_MT(CKC_E, KC_E, KC_LEFT_CTRL)
        SMTD_MT(CKC_I, KC_I, KC_LEFT_GUI)
        SMTD_MT(CKC_O, KC_O, KC_LEFT_ALT)
        // left thumb cluster
        SMTD_LT(LT_MID, KC_SPACE, LAYER_NAVIGATION)
        SMTD_LT(LT_INR, KC_ESCAPE, LAYER_FUNCTION)
        // right thumb cluster
        SMTD_LT(RT_INR, KC_TAB, LAYER_MEDIA)
        SMTD_LT(RT_MID, KC_BSPC, LAYER_NUMERAL)
        SMTD_LT(RT_OUT, KC_ENTER, LAYER_SYMBOLS)
        // pointer keys
        SMTD_LT(CKC_Z, KC_Z, LAYER_POINTER)
        SMTD_LT(CKC_SLSH, KC_SLSH, LAYER_POINTER)
    }
}

// actions
#define _UNDO LGUI(KC_Z)
#define _PASTE LGUI(KC_C)
#define _COPY LGUI(KC_C)
#define _CUT LGUI(KC_X)
#define _REDO LGUI(S(KC_Y))

// clang-format off
/** \brief Colemak (DH) layout (3 rows, 10 columns). */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         KC_Q,    KC_W,     KC_F,    KC_P,   KC_B,       KC_J,    KC_L,    KC_U,   KC_Y,  KC_QUOT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         CKC_A,   CKC_R,    CKC_S,   CKC_T,   KC_G,      KC_M,   CKC_N,   CKC_E,   CKC_I,   CKC_O,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         CKC_Z,    KC_X,    KC_C,    KC_D,    KC_V,      KC_K,    KC_H, KC_COMM,  KC_DOT, CKC_SLSH,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_ESC, LT_MID, LT_INR,        RT_INR, RT_MID, RT_OUT
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

/*
 * Layers used on the Dilemma.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down and tailored for a stock experience that is meant to be fundation for
 * further personalization.
 *
 * See https://github.com/manna-harbour/miryoku for the original layout.
 */

/**
 * \brief Function layer.
 *
 * Secondary right-hand layer has function keys mirroring the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner
 * column. App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
  [LAYER_FUNCTION] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_PSCR,  KC_F7,  KC_F8,   KC_F9,  KC_F12,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, KC_ESC,      KC_SCRL,  KC_F4,  KC_F5,   KC_F6,  KC_F11,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_PAUS,  KC_F1,  KC_F2,   KC_F3,  KC_F10,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         XXXXXXX, _______, XXXXXXX,     KC_TAB,  KC_BSPC, KC_ENT
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

/**
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
  [LAYER_NAVIGATION] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    _REDO,   _PASTE,  _COPY,     _CUT,   _UNDO,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_ESC,    CW_TOGG, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         XXXXXXX, XXXXXXX, _______,     KC_TAB, KC_DEL, KC_ENT
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

/**
 * \brief Media layer.
 *
 * Tertiary left- and right-hand layer is media and RGB control.  This layer is
 * symmetrical to accomodate the left- and right-hand trackball.
 */
  [LAYER_MEDIA] = LAYOUT_split_3x5_3(
    /* XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX, */
    /* KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, */
    /* XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, */
    /*                   _______, KC_MPLY, KC_MSTP, KC_MSTP, KC_MPLY, KC_MUTE */

  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX,   XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,    KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, KC_MPLY, KC_MSTP,    XXXXXXX, _______, _______
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

/** \brief Mouse emulation and pointer functions. */
  [LAYER_POINTER] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX,  EE_CLR, QK_BOOT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       _______, DRGSCRL, SNIPING, KC_BTN3, XXXXXXX,    XXXXXXX, KC_BTN3, SNIPING, DRGSCRL, _______,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_BTN3, KC_BTN2, KC_BTN1,    KC_BTN1, KC_BTN2, KC_BTN3
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
  [LAYER_NUMERAL] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       KC_LBRC,    KC_7,    KC_8,  KC_9,  KC_RBRC,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_SCLN,    KC_4,    KC_5,  KC_6,  KC_EQL,      XXXXXXX, KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_DOT,     KC_1,    KC_2,  KC_3,  KC_BSLS,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_LPRN, KC_0,  KC_MINS,      XXXXXXX, _______, _______
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
  [LAYER_SYMBOLS] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_COLN, KC_CIRC, KC_PERC, KC_DLR,  KC_PLUS,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_TILD, KC_EXLM,  KC_AT,  KC_HASH, KC_PIPE,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_LPRN, KC_RPRN, KC_UNDS,    XXXXXXX, _______, _______
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),
};

// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef ENCODER_MAP_ENABLE
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_BASE]       = {ENCODER_CCW_CW(KC_WH_U, KC_WH_D)},
    [LAYER_FUNCTION]   = {ENCODER_CCW_CW(KC_DOWN, KC_UP)},
    [LAYER_NAVIGATION] = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP)},
    [LAYER_MEDIA]      = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP)},
    [LAYER_POINTER]    = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [LAYER_NUMERAL]    = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [LAYER_SYMBOLS]    = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
};
// clang-format on
#endif // ENCODER_MAP_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }
    return true;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to the next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        // I have a dedicated underscore key, so no need to shift KC_MINS.
        case KC_MINS:
        case KC_UNDS:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}
