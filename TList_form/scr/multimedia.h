#pragma once

#include <windows.h>

typedef enum {
	WHITE = 7,
	DARK_YELLOW = 6,
	GREEN = 10,
	DARK_RED = 4,
	GRAY = 8
} COLORS;

typedef enum {
	ALPHANUMERIC_KEYS = 1,
	BACKSPACE = 2,
	ENTER = 3,
	NAVIGATION_KEYS = 4,
	FUNCTION_KEYS = 5
} KEYS;

typedef enum {
	LIST = 0,
	EXERSIZE = 1
} TYPE;

void print_color(HANDLE hConsole, char* text, COLORS c);
void start_logo(HANDLE hConsole);
void waiting();
void draw_menu();
void splash(char* text);
void clr_splash();
int bounded_input(char input[], const int l);