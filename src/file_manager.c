#include "../include/file_manager.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int GetContentFile(const char *path, char lines[MAX_LINES][MAX_CHAR_LINES])
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t len = 0;
    int read;
    int max_lines = 0;
    while ((read = getline(&line, &len, file)) != -1)
    {
        if (!IsLineEmpty(line))
        {
            if (max_lines < MAX_LINES)
            {
                strcpy(lines[max_lines++], line);
            }
        }
    }

    for (int i = 0; lines[i][0] != '\0'; i++)
    {
        if (i == max_lines-1) {
            printf("└──\033[34m%s\033[0m\n", lines[i]);
        } else{
            printf("├──\033[34m%s\033[0m\n", lines[i]);
        }
    }

    printf("\n");

    fclose(file);

    return max_lines;
}


bool IsLineEmpty(char *line)
{
    int j = 0;
    for (size_t i = 0; line[i] != '\0'; ++i)
    {
        if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
        {
            line[j++] = line[i];
        }
    }
    line[j] = '\0';
    return (j == 0);
}
