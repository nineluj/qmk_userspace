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

enum dilemma_keymap_layers { LAYER_BASE = 0, LAYER_FUNCTION, LAYER_NAVIGATION, LAYER_MEDIA, LAYER_POINTER, LAYER_NUMERAL, LAYER_SYMBOLS, LAYER_VIRT_MOUSE };

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

// single key aliases
#define LT_OUT MO(LAYER_VIRT_MOUSE)
#define MO_MOUSE MO(LAYER_VIRT_MOUSE)
#define KC_BROWSER_TAB_PREV LGUI(S(KC_LBRC))
#define KC_BROWSER_TAB_NEXT LGUI(S(KC_RBRC))
#define KC_WORKSPC_PREV LCTL(KC_LEFT)
#define KC_WORKSPC_NEXT LCTL(KC_RIGHT)
#define KC_BROWSER_ZOOM_IN LGUI(KC_EQUAL)
#define KC_BROWSER_ZOOM_OUT LGUI(KC_MINUS)
#define KC_BROWSER_ZOOM_RESET LGUI(KC_0)

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

    // multi encoder magic
    MULTI_ENC_CCW,
    MULTI_ENC_CW,
    MULT_ENC_CLK,
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
#define _REDO LGUI(S(KC_Z))

// clang-format off
/** \brief Colemak (DH) layout (3 rows, 10 columns). */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         KC_Q,    KC_W,     KC_F,    KC_P,   KC_B,       KC_J,    KC_L,    KC_U,   KC_Y,  KC_QUOT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         CKC_A,   CKC_R,    CKC_S,   CKC_T,  KC_G,       KC_M,   CKC_N,   CKC_E,   CKC_I,   CKC_O,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         CKC_Z,    KC_X,    KC_C,    KC_D,   KC_V,       KC_K,    KC_H, KC_COMM,  KC_DOT, CKC_SLSH,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          LT_OUT, LT_MID, LT_INR,        RT_INR, RT_MID, RT_OUT
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
       MO_MOUSE,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         XXXXXXX, XXXXXXX, _______,     KC_TAB, KC_DEL, KC_ENT
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

/**
 * \brief Media layer.
 */
  [LAYER_MEDIA] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX,RGB_RMOD, RGB_TOG, RGB_MOD, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                     MULT_ENC_CLK, KC_MPLY, KC_MSTP,   XXXXXXX, _______, _______
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

/** \brief Mouse emulation and pointer functions. */
  [LAYER_POINTER] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX,  EE_CLR, QK_BOOT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT,
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
       KC_GRAVE,   KC_1,    KC_2,  KC_3,  KC_BSLS,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_LPRN,  KC_0,  KC_MINS,      XXXXXXX, _______, _______
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


  [LAYER_VIRT_MOUSE] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_ESC,     XXXXXXX, MS_LEFT, MS_DOWN,  MS_UP,  MS_RGHT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, MS_WHLD, MS_WHLU, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         XXXXXXX, XXXXXXX, _______,    MS_BTN3, MS_BTN1, MS_BTN2
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),
};

// clang-format on

// -- advanced configuration starts here
const key_override_t  zero_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_0, KC_DOT);
const key_override_t *key_overrides[]   = {&zero_key_override};

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
    [LAYER_BASE]       = {ENCODER_CCW_CW(KC_WH_U, KC_WH_D)},  // vertical scrolling (regular)
    [LAYER_FUNCTION]   = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},  // hard to reach
    [LAYER_NAVIGATION] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},  // hard to reach
    [LAYER_MEDIA]      = {ENCODER_CCW_CW(MULTI_ENC_CCW, MULTI_ENC_CW)}, // enable multiple encoder fns w/ modifiers
    [LAYER_POINTER]    = {ENCODER_CCW_CW(KC_WH_L, KC_WH_R)},  // horizontal scrolling
    [LAYER_NUMERAL]    = {ENCODER_CCW_CW(_UNDO, _REDO)},      // for coding
    [LAYER_SYMBOLS]    = {ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)}, // for scrubbing through videos
    [LAYER_VIRT_MOUSE] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},  // hard to reach
};
// clang-format on
#endif // ENCODER_MAP_ENABLE

enum encoder_modifiers { ENC_NO = 0, ENC_SFT, ENC_CTL, ENC_GUI, ENC_ALT, NUM_ENC_MOD };

// clang-format off
const uint16_t PROGMEM multi_function_encoder_map[NUM_ENC_MOD][NUM_ENCODERS][3] = {
    //            CCW        CW     Click
    [ENC_NO]  = {{KC_VOLD, KC_VOLU, KC_MUTE}},
    [ENC_SFT] = {{KC_WORKSPC_PREV, KC_WORKSPC_NEXT, XXXXXXX}},
    [ENC_CTL] = {{KC_BROWSER_ZOOM_OUT, KC_BROWSER_ZOOM_IN, KC_BROWSER_ZOOM_RESET}},
    [ENC_GUI] = {{KC_LEFT, KC_RIGHT, XXXXXXX}},
    [ENC_ALT] = {{KC_BROWSER_TAB_PREV, KC_BROWSER_TAB_NEXT, XXXXXXX}},
};
// clang-format on

bool process_multi_function_encoder(uint16_t input_keycode, keyrecord_t *record) {
    if ((input_keycode != MULTI_ENC_CW && input_keycode != MULTI_ENC_CCW && input_keycode != MULT_ENC_CLK) || !record->event.pressed) {
        return true;
    }

    // Store the current modifier state
    uint8_t mods    = get_mods();
    uint8_t oneshot = get_oneshot_mods();
    uint8_t weak    = get_weak_mods();

    // Combine all modifier states
    uint8_t all_mods = mods | oneshot | weak;

    // Check individual modifier states
    bool shifted = (all_mods & MOD_MASK_SHIFT) != 0;
    bool ctled   = (all_mods & MOD_MASK_CTRL) != 0;
    bool guied   = (all_mods & MOD_MASK_GUI) != 0;
    bool alted   = (all_mods & MOD_MASK_ALT) != 0;

    uint16_t encoder_keycode;
    uint8_t  encoder_idx  = 0; // Assuming first encoder
    uint8_t  modifier_idx = input_keycode - MULTI_ENC_CCW;

    if (shifted) {
        encoder_keycode = pgm_read_word(&multi_function_encoder_map[ENC_SFT][encoder_idx][modifier_idx]);
    } else if (ctled) {
        encoder_keycode = pgm_read_word(&multi_function_encoder_map[ENC_CTL][encoder_idx][modifier_idx]);
    } else if (guied) {
        encoder_keycode = pgm_read_word(&multi_function_encoder_map[ENC_GUI][encoder_idx][modifier_idx]);
    } else if (alted) {
        encoder_keycode = pgm_read_word(&multi_function_encoder_map[ENC_ALT][encoder_idx][modifier_idx]);
    } else {
        encoder_keycode = pgm_read_word(&multi_function_encoder_map[ENC_NO][encoder_idx][modifier_idx]);
    }

    // Clear all mods temporarily
    clear_mods();
    clear_oneshot_mods();
    clear_weak_mods();

    // Send the keycode
    tap_code16(encoder_keycode);

    // Restore the original modifier state
    set_mods(mods);
    set_oneshot_mods(oneshot);
    set_weak_mods(weak);

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }

    if (!process_multi_function_encoder(keycode, record)) {
        return false;
    }

    return true;
}

uint32_t get_smtd_timeout(uint16_t keycode, smtd_timeout timeout) {
    uint32_t fallback = get_smtd_timeout_default(timeout);
    switch (keycode) {
        // thumbs
        case RT_INR:
        case RT_MID:
        case RT_OUT:
        case LT_MID:
        case LT_INR:
            if (timeout == SMTD_TIMEOUT_TAP) return fallback + (fallback * 70 / 100); // make it longer for the thumb keys and weaker keys

        case CKC_A:
        case CKC_O:
        case CKC_R:
        case CKC_I:
            if (timeout == SMTD_TIMEOUT_TAP) return fallback * 2;

        case CKC_S:
        case CKC_E:
            if (timeout == SMTD_TIMEOUT_TAP) return fallback + (fallback * 50 / 100);

        case CKC_T:
        case CKC_N:
            if (timeout == SMTD_TIMEOUT_TAP) return fallback - (fallback * 50 / 100); // make it shorter for the stronger shift keys
    }

    /* if (timeout == SMTD_TIMEOUT_RELEASE && keycode >= CKC_A && keycode <= CKC_O) return 10; */

    if (timeout == SMTD_TIMEOUT_RELEASE) {
        switch (keycode) {
            case CKC_A ... CKC_O:
                return 8;
        }
    }

    return fallback;
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

        default:
            return false; // Deactivate Caps Word.
    }
}
