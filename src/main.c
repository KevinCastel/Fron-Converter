#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/file_manager.h"
#include "../include/node.h"


int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Usage: <./app 'index.html' 'styles.css' 'node_to_find'>\n");
        exit(EXIT_FAILURE);
    }
    char htmlLines[MAX_LINES][MAX_CHAR_LINES] = {0};

    char *html_src = argv[1];
    // char *css_src = argv[2];
    char *node_id = argv[3];

    printf("\033[94m@\033[35mreading\033[0m:\033[32m%s\033[0m\n", html_src);

    size_t sizeHtmlLines = GetContentFile("index.html", htmlLines);

    printf("\033[94m@\033[35msearching\033[0m:\033[32m%s\033[97m~%s\033[0m\n", node_id, html_src);

    // Node childrens[] = {0};
    Node *childrens = malloc(sizeof(Node)*300);

    GetNodeLineIndexById(node_id, htmlLines, sizeHtmlLines, childrens);

    if (childrens){
        free(childrens);
    }

    return 0;
}