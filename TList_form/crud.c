#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int get_CRUD(char* input) {
	char* com[] = {"create", "read", "update", "delete", "import", "export", "help"};
	for (int i = 0; i < 6; i++){
		if(strncmp(input, com[i], strlen(com[i])) == 0)
			return ++i;
	}
	return 0;
}