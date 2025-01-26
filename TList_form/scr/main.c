#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#include "multimedia.h"
#include "crud.h"

#define LEN 45

int main() {
	printf("\033]0;TList former\007");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	start_logo(hConsole);

	waiting();
	
	system("chcp 866");
	system("@cls||clear");
	draw_menu();

	int crud;
	bool result;
	char input[LEN] = {0};
	for (int i = 2;;) {
		switch (bounded_input(input, LEN)) {
		case NAVIGATION_KEYS:
			splash("N-key");
			break;

		case FUNCTION_KEYS:
			splash("F-key");
			break;

		default:

			crud = get_CRUD(input);
			clr_splash();
			switch (crud) {
			case CREATE:
				splash("CREATE COMMAND");
				break;
			case READ:
				splash("READ COMMAND");
				break;
			case UPDATE:
				splash("UPDATE COMMAND");
				break;
			case DEL:
				splash("DELETE COMMAND");
				break;
			case IMPORT:
				splash("IMPORT COMMAND");
				break;
			case EXPORT:
				splash("EXPORT COMMAND");
				break;
			case HELP:
				splash("HELP COMMAND");
				break;
			default:
				splash("UNKNOWN COMMAND");
			}
			i++;
			printf("\033[%d;2H", i);
			printf("\\ ");
		}
		
	}
}



