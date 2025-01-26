#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <string.h> 
#include <windows.h>
#include "multimedia.h"

void print_color(HANDLE hConsole, const char* text, COLORS c) {
	SetConsoleTextAttribute(hConsole, c);
	printf(text);
}

void start_logo(HANDLE hConsole) {
	print_color(
		hConsole,
		"                    @@@@@@@@@@@@@@@ @@@@@@@@@     @@@                                           \n"
		"                     @@@@@@@@@@@@@@  @@@@@@@@    @@@@                                           \n"
		"                               @@@@              @@@@                                           \n"
		"                               @@@@              @@@@                                           \n"
		"                               @@@@              @@@@                                           \n"
		"                               @@@@              @@@@                                           \n"
		"                               @@@@              @@@@                                           \n"
		"                               @@@@              @@@@                                           \n"
		"                               @@@@              @@@@                                           \n"
		"                               @@@@              @@@@                                           \n"
		"                               @@@@              @@@@                  @@@@                     \n"
		"                               @@@@              @@@@@                @@@@@                     \n"
		"                               @@@@               @@@@@@@@@@@@@@@@@@@@@@@@                      \n"
		"                               @@@@                 @@@@@@@@@@@@@@@@@@@@                        \n"
		"                                                                                                \n"
		"                                                                                                \n"
		"     @@@@@@@@@@@   @@@@@ @@@@@   @@@@@@@@@@@   @@@            @@@  @@@@@@@@@@@@  @@@@@@@@@@@    \n"
		"    @@            @@         @@ @@         @@  @@@@         @@@@@  @@            @@        @@   \n"
		"    @@            @@         @@ @@         @@     @@@     @@@      @@            @@        @@   \n"
		"    @@            @@         @@ @@         @@  @@   @@@ @@@    @@  @@            @@        @@   \n"
		"    @@@@@@@@@@@   @@         @@ @@         @@  @@     @@@      @@  @@@@@@@@@@    @@        @@   \n"
		"    @@            @@         @@ @@@@@@@@@@@@   @@      @@      @@  @@            @@@@@@@@@@@    \n"
		"    @@            @@         @@ @@    @@@      @@      @@      @@  @@            @@    @@@      \n"
		"    @@            @@@       @@@ @@      @@@    @@      @@      @@  @@            @@     @@@     \n"
		"    @@             @@@@@ @@@@@  @@        @@@  @@      @@      @@   @@@@@@@@@@@  @@       @@@   \n"
		"                                                                                                \n"
		"                                     Press ENTER to continue                                    \n"
		"\n\n",
		DARK_YELLOW
	);
}

void waiting() {
	char c = 0;
	unsigned int retTime = time(0) + 2;
	bool f = true;

	while (c != '\r') {
		if (_kbhit()) {
			c = _getch();
		}

		if (time(0) > retTime) {
			f = true;
			retTime = time(0) + 1;
			printf("\033[27;37HPress ENTER to continue\033[28;0H");
		}
		if (time(0) > retTime - 1 && f) {
			f = false;
			printf("\033[27;0H\33[K\033[28;0H");
		}
	}
}

void draw_menu() {
	printf("%c", 201);
	for (int i = 0; i < 47; i++)
		printf("%c", 205);
	printf("%c", 209);
	for (int i = 0; i < 70; i++)
		printf("%c", 205);
	printf("%c\n", 187);

	for (int i = 0; i < 21; i++)
		printf("%c                                               %c                                                                      %c\n", 186, 179, 186);

	printf("%c", 204);
	for (int i = 0; i < 47; i++)
		printf("%c", 205);
	printf("%c", 207);
	for (int i = 0; i < 70; i++)
		printf("%c", 205);
	printf("%c\n", 185);
	
	for (int i = 0; i < 5; i++)
		printf("%c                                                                                                                      %c\n", 186, 186);

	printf("%c", 200);
	for (int i = 0; i < 118; i++)
		printf("%c", 205);
	printf("%c\n", 188);
	printf("\033[1;21H");
	printf("%cINPUT%c", 181, 198);
	printf("\033[1;81H");
	printf("%cOUTPUT%c", 181, 198);
	printf("\033[2;2H");
	printf("\\ ");
}

int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}

bool isalpha_rus(unsigned char c) {
	return c >= 128 && c <= 175 || c >= 224 && c <= 243;
}


int key_type(unsigned char c) {
	static bool flag = 0;
	static unsigned int timer;
	switch ((int)c) {
	case 8:
		return BACKSPACE;

	case 13:
		return ENTER;

	case 224:
		flag = true;
		timer = time(0);
		return ALPHANUMERIC_KEYS;

	case 0:
		return FUNCTION_KEYS;

	default:
		if (time(0) < timer + 1 && flag && strchr("HKPMSIRQ", c)) {
			flag = false;
			return NAVIGATION_KEYS;
		}
		if (isalpha(c) || isalpha_rus(c) || isdigit(c) || c == 32)
			return ALPHANUMERIC_KEYS;
		return 0;
	}
}

int bounded_input(char input[], const int l) {
	int start = wherex();
	unsigned char c = 0;
	int i = 0;
	while (true) {
		if (_kbhit()) {
			c = _getch();
			switch (key_type(c)) {
			case ALPHANUMERIC_KEYS:
				if (wherex() - start < l) {
					printf("%c", c);
					input[i] = c;
					i++;
				}
				break;

			case BACKSPACE:
				if (i > 0) {
					printf("\033[1D");
					printf(" ");
					printf("\033[1D");
					i--;
				}
				break;

			case ENTER:
				input[i] = '\0';
				return ALPHANUMERIC_KEYS;

			case NAVIGATION_KEYS:
				printf("\033[1D");
				printf(" ");
				printf("\033[1D");
				input[0] = c;
				return NAVIGATION_KEYS;

			case FUNCTION_KEYS:
				input[0] = _getch();
				return FUNCTION_KEYS;

			default:
				continue;
			}
		}
	}
}

void splash(char* text) {
	printf("\033[26;%dH", (int)(59 - strlen(text)/2));
	printf("%s", text);
}

void clr_splash() {
	printf("\033[26;2H");
	printf("\33[K");
	printf("\033[26;120H");
	printf("%c", 186);
}