#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h>
#include "file_manager.h"

typedef struct Node{
    size_t childrens_count;
    int index_start_line;
    int index_end_line;
    char id[40];
    char type[20];
    struct Node *childrens[];
} Node;

void GetNodeLineIndexById(char *node_id, char lines[MAX_LINES][MAX_CHAR_LINES], size_t size, Node nodes[]);

char* GetTypeElement(const char* line);

Node* createNode(const char *e_id, const char *type, int i_start_line);

#endif
