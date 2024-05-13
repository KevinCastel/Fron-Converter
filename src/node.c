#include "../include/node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* GetTypeElement(const char* line){

    if (strstr(line, "div")){
        return "div";
    } else if (strstr(line, "header")){
        return "header";
    } else if (strstr(line, "table")){
        return "table";
    }
    return "";
}

void GetNodeLineIndexById(char *node_id, char lines[MAX_LINES][MAX_CHAR_LINES], size_t size, Node nodes[]){
    int index_line_begins_div = -1;
    int index_lines_ends_div = -1;
    int index_node = 0;

    Node *node;
    node = malloc(sizeof(Node));

    size_t i;

    for(i = 0; lines[i][0] != '\0'; i++){
        if (strstr(lines[i], node_id)){ //node is found
            if (index_line_begins_div == -1){ //node is opened
                printf("├─┬\033[35m%s\033[0m\n", lines[i]);
                index_line_begins_div = i;
                node = createNode(node_id, GetTypeElement(lines[i]),i);
            } else if (index_lines_ends_div == -1){ //node is closed
                index_lines_ends_div = i;
                printf("│\033[93mX\033[0m└──\033[35m%s\033[0m\n│\n", lines[i]);
                node->index_end_line = i;
                nodes[index_node] = *node;
                index_node++;
                // break;
            }
        } else if (size-1 == i) {
            if (index_line_begins_div != -1 && index_lines_ends_div == -1){ //color childrens node is opened
                printf("│ └──\033[33m%s\033[0m\n│\n", lines[i]);
                
            } else {
                printf("└──\033[34m%s\033[0m\n", lines[i]);
            }
        } else if (size != i) {
            if (index_line_begins_div != -1 && index_lines_ends_div == -1){ //color children node is opened
                printf("│ ├──\033[35m%s\033[0m\n", lines[i]);
            } else {
                printf("├──\033[34m%s\033[0m\n", lines[i]);
            }
        }
    }

    // if (node){
    //     free(node);
    // }

    // Node new_node = nodes[0];
    printf("new node information:\n  - starting line: %d\n  - ending line: %d\n  - type: %s\n  - id: %s\n",
            nodes[0].index_start_line, nodes[0].index_end_line, nodes[0].type, nodes[0].id);

    
    printf("\n");

    //Manage errors
    if (index_line_begins_div == -1){
        printf("An error has occurred as the following id :'\033[35m%s\033[0m' was never open\n", node_id);
        exit(EXIT_FAILURE);
    }

    if (index_lines_ends_div == -1){
        printf("An error has occurred as the following id :'\033[35m%s\033[0m' was never close\n", node_id);
        exit(EXIT_FAILURE);
    }
}

Node* createNode(const char *e_id, const char *type, int i_start_line){
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL){
        return NULL;
    }

    strncpy(new_node->id, e_id, sizeof(new_node->id)-1);
    new_node->id[strlen(new_node->id)] = '\0';
    strncpy(new_node->type, type, sizeof(new_node->type)-1);
    new_node->type[strlen(new_node->type)] = '\0';
    // strncpy(new_node->value, value, sizeof(new_node->value) -1);
    // new_node->value[strlen(new_node->value)-1] = '\0';

    new_node->index_start_line = i_start_line;
    new_node->index_end_line = 0;

    printf("Creation of an new node:\n  --id: %s\n  --type: %s\n --starting line index: %d\n  --ending line index: %d\n",
                                        e_id, type, i_start_line, 0);

    return new_node;
}
