/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

enum KEYBOARD
{
    UNHANDLED_KEY = -1,
    NO_KEY = 0,

    /* Letter keys */
    A, // a A
    B, // b B
    C, // c C
    D, // d D
    E, // e E
    F, // f F
    G, // g G
    H, // h H
    I, // i I
    J, // j J
    K, // k K
    L, // l L
    M, // m M
    N, // n N
    O, // o O
    P, // p P
    Q, // q Q
    R, // r R
    S, // s S
    T, // t T
    U, // u U
    V, // v V
    W, // w W
    X, // x X
    Y, // y Y
    Z, // z Z

    /* Number keys */
    NUM_0, // 0 )
    NUM_1, // 1 !
    NUM_2, // 2 @
    NUM_3, // 3 #
    NUM_4, // 4 $
    NUM_5, // 5 %
    NUM_6, // 6 ^
    NUM_7, // 7 &
    NUM_8, // 8 *
    NUM_9, // 9 (

    /* Arrow keys */
    ARROW_LEFT,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,

    /* Numpad Keys */
    NUMPAD_0,
    NUMPAD_1,
    NUMPAD_2,
    NUMPAD_3,
    NUMPAD_4,
    NUMPAD_5,
    NUMPAD_6,
    NUMPAD_7,
    NUMPAD_8,
    NUMPAD_9,

    NUMPAD_ADD,
    NUMPAD_SUBTRACT,
    NUMPAD_MULTIPLY,
    NUMPAD_DIVIDE,
    NUMPAD_DECIMAL,

    /* Other Keys */
    BACKSPACE,
    TAB,
    INSERT,
    DEL,
    HOME,
    END,
    PAGE_UP,
    PAGE_DOWN,
    MENU,
    PRINT_SCREEN,
    PAUSE,
    ESCAPE,

    GRAVE, // ` ~
    SPACE,
    SLASH_FORWARD, // / ?
    SLASH_BACKWARD, // \ |
    COMMA, // , <
    PERIOD, // . >
    SEMICOLON, // ; :
    APOSTROPHE, // ' "
    HYPHEN, // - _
    EQUALS, // = +
    SQUARE_BRACKET_LEFT, // [ {
    SQUARE_BRACKET_RIGHT, // ] }

    /* Lock keys */
    CAPS_LOCK,
    NUM_LOCK,
    SCROLL_LOCK,

    /* F Keys */
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,

    /* Control Keys */
    ALT,
    ALT_LEFT,
    ALT_RIGHT,

    CONTROL,
    CONTROL_LEFT,
    CONTROL_RIGHT,

    SHIFT,
    SHIFT_LEFT,
    SHIFT_RIGHT,

    SYSTEM,
    SYSTEM_LEFT,
    SYSTEM_RIGHT,
    
    END_OF_ENUM
};