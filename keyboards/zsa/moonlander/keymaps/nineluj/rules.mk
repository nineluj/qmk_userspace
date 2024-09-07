# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
ORYX_ENABLE = no
RGB_MATRIX_CUSTOM_KB = yes
SPACE_CADET_ENABLE = no
CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes


RGB_MATRIX_ENABLE = IS31FL3731

# custom
SRC += features/achordion.c
# RGB_MATRIX_CUSTOM_USER = yes

