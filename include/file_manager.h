#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINES 200
#define MAX_CHAR_LINES 150

int GetContentFile(const char *path, char lines[MAX_LINES][MAX_CHAR_LINES]);

bool IsLineEmpty(char *line);

#endif
