#include "LUFA/Drivers/USB/USB.h"

int tablegen[] = {
    0, 0, HID_KEYBOARD_SC_ESCAPE,
    0, 1, HID_KEYBOARD_SC_1_AND_EXCLAMATION,
    0, 2, HID_KEYBOARD_SC_2_AND_AT,
    0, 3, HID_KEYBOARD_SC_3_AND_HASHMARK,
    0, 4, HID_KEYBOARD_SC_4_AND_DOLLAR,
    0, 5, HID_KEYBOARD_SC_5_AND_PERCENTAGE,
    0, 6, HID_KEYBOARD_SC_6_AND_CARET,
    0, 7, HID_KEYBOARD_SC_7_AND_AMPERSAND,
    0, 8, HID_KEYBOARD_SC_8_AND_ASTERISK,
    0, 9, HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS,
    0, 10, HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS,
    0, 11, HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE,
    0, 12, HID_KEYBOARD_SC_EQUAL_AND_PLUS,
    0, 13, HID_KEYBOARD_SC_BACKSPACE,
    1, 0, HID_KEYBOARD_SC_TAB,
    1, 1, HID_KEYBOARD_SC_Q,
    1, 2, HID_KEYBOARD_SC_W,
    1, 3, HID_KEYBOARD_SC_E,
    1, 4, HID_KEYBOARD_SC_R,
    1, 5, HID_KEYBOARD_SC_T,
    1, 6, HID_KEYBOARD_SC_Y,
    1, 7, HID_KEYBOARD_SC_U,
    1, 8, HID_KEYBOARD_SC_I,
    1, 9, HID_KEYBOARD_SC_O,
    1, 10, HID_KEYBOARD_SC_P,
    1, 11, HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE,
    1, 12, HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE,
    1, 13, HID_KEYBOARD_SC_BACKSLASH_AND_PIPE,
    2, 0, HID_KEYBOARD_SC_CAPS_LOCK,
    2, 1, HID_KEYBOARD_SC_A,
    2, 2, HID_KEYBOARD_SC_S,
    2, 3, HID_KEYBOARD_SC_D,
    2, 4, HID_KEYBOARD_SC_F,
    2, 5, HID_KEYBOARD_SC_G,
    2, 6, HID_KEYBOARD_SC_H,
    2, 7, HID_KEYBOARD_SC_J,
    2, 8, HID_KEYBOARD_SC_K,
    2, 9, HID_KEYBOARD_SC_L,
    2, 10, HID_KEYBOARD_SC_SEMICOLON_AND_COLON,
    2, 11, HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE,
    2, 12, HID_KEYBOARD_SC_ENTER,
    3, 0, HID_KEYBOARD_SC_LEFT_SHIFT,
    3, 1, HID_KEYBOARD_SC_Z,
    3, 2, HID_KEYBOARD_SC_X,
    3, 3, HID_KEYBOARD_SC_C,
    3, 4, HID_KEYBOARD_SC_V,
    3, 5, HID_KEYBOARD_SC_B,
    3, 6, HID_KEYBOARD_SC_N,
    3, 7, HID_KEYBOARD_SC_M,
    3, 8, HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN,
    3, 9, HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN,
    3, 10, HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK,
    3, 11, HID_KEYBOARD_SC_RIGHT_SHIFT,
    3, 12, HID_KEYBOARD_SC_UP_ARROW,
    4, 13, HID_KEYBOARD_SC_RIGHT_SHIFT,

    4, 0, HID_KEYBOARD_SC_LEFT_CONTROL,
    4, 1, HID_KEYBOARD_SC_LEFT_GUI,
    4, 2, HID_KEYBOARD_SC_LEFT_ALT,
    4, 5, HID_KEYBOARD_SC_SPACE,
    4, 8, HID_KEYBOARD_SC_RIGHT_GUI,
    4, 9, HID_KEYBOARD_SC_RIGHT_ALT,
    4, 10, HID_KEYBOARD_SC_LEFT_ARROW,
    4, 11, HID_KEYBOARD_SC_DOWN_ARROW,
    4, 12, HID_KEYBOARD_SC_RIGHT_ARROW
};

void init_layout(int *layout, int rows, int cols) {
    int len = sizeof(tablegen)/sizeof(tablegen[0]);

    // set everything to -1
    for (int i = 0; i < rows*cols; i++) {
        layout[i] = -1;
    }

    for (int i = 0; i < len; i += 3) {
        int r = tablegen[i], c = tablegen[i + 1];

        layout[r*rows + c] = tablegen[i + 2];
    }
}
