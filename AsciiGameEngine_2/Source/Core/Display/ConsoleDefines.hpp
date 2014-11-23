#pragma once

#include <Windows.h>

// Utility
#define f_intense (FOREGROUND_INTENSITY)
#define b_intense (BACKGROUND_INTENSITY)

// Shades
#define f_black 0
#define b_black 0

#define f_darkGray (f_intense)
#define b_darkGray (b_intense)

#define f_lightGray (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define b_lightGray (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)

#define f_white (f_intense | f_lightGray)
#define b_white (b_intense | b_lightGray)

// Red
#define f_halfRed (FOREGROUND_RED)
#define f_fullRed (f_intense | FOREGROUND_RED)
#define b_halfRed (BACKGROUND_RED)
#define b_fullRed (b_intense | BACKGROUND_RED)

// Green
#define f_halfGreen (FOREGROUND_GREEN)
#define f_fullGreen (f_intense | f_halfGreen)
#define b_halfGreen (BACKGROUND_GREEN)
#define b_fullGreen (b_intense | b_halfGreen)

// Blue
#define f_halfBlue (FOREGROUND_BLUE)
#define f_fullBlue (f_intense | f_halfBlue)
#define b_halfBlue (BACKGROUND_BLUE)
#define b_fullBlue (b_intense | b_halfBlue)

// Yellow
#define f_halfYellow (f_halfRed | f_halfGreen)
#define f_fullYellow (f_intense | f_halfYellow)
#define b_halfYellow (b_halfRed | b_halfGreen)
#define b_fullYellow (b_intense | b_halfYellow)

// Cyan
#define f_halfCyan (f_halfGreen | f_halfBlue)
#define f_fullCyan (f_intense | f_halfCyan)
#define b_halfCyan (b_halfGreen | b_halfBlue)
#define b_fullCyan (b_intense | b_halfCyan)

// Purple
#define f_halfPurple (f_halfRed | f_halfBlue)
#define f_fullPurple (f_intense | f_halfPurple)
#define b_halfPurple (b_halfRed | b_halfBlue)
#define b_fullPurple (b_intense | b_halfPurple)