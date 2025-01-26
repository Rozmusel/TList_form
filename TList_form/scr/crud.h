#pragma once

typedef enum {
	CREATE = 1,
	READ = 2,
	UPDATE = 3,
	DEL = 4,
	IMPORT = 5,
	EXPORT = 6,
	HELP = 7
} CRUD;

int get_CRUD(char*);