#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINES 200
#define MAX_CHAR_LINE 150

typedef struct Node {
    size_t childrens_count;
    int index_start_line;
    int index_end_line;
    char id[30];
    char type[20];
    struct Node *childrens[];
} Node;

Node* createNode(const char *e_id, const char *type, int i_start_line){
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL){
        return NULL;
    }

    strncpy(new_node->id, e_id, sizeof(new_node->id)-1);
    new_node->id[strlen(new_node->id)-1] = '\0';
    strncpy(new_node->type, type, sizeof(new_node->type)-1);
    new_node->type[strlen(new_node->type)-1] = '\0';
    // strncpy(new_node->value, value, sizeof(new_node->value) -1);
    // new_node->value[strlen(new_node->value)-1] = '\0';

    new_node->index_start_line = i_start_line;
    new_node->index_end_line = 0;

    printf("Creation of an new node:\n  --id: %s\n  --type: %s\n --starting line index: %d\n  --ending line index: %d\n",
                                        e_id, type, i_start_line, 0);

    return new_node;
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

int GetContentFile(char *path, char lines[MAX_LINES][MAX_CHAR_LINE])
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
    while (read = getline(&line, &len, file) != -1)
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

void GetNodeLineIndexById(char *node_id, char lines[MAX_LINES][MAX_CHAR_LINE], size_t size, Node nodes[]){
    int index_line_begins_div = -1;
    int index_lines_ends_div = -1;
    int index_node = 0;

    Node *node;
    node = malloc(sizeof(Node));

    for(int i = 0; lines[i][0] != '\0'; i++){
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
                break;
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

    if (node){
        free(node);
    }

    Node new_node = nodes[0];
    printf("new node information:\n  - starting line: %d\n  - ending line: %d\n  - type: %s\n  - id: %s\n",
            new_node.index_start_line, new_node.index_end_line, new_node.type, new_node.id);



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

int main(size_t argc, char **argv)
{
    if (argc != 4)
    {
        printf("Usage: <./app 'index.html' 'styles.css' 'node_to_find'>\n");
        exit(EXIT_FAILURE);
    }
    char htmlLines[MAX_LINES][MAX_CHAR_LINE] = {0};

    char *html_src = argv[1];
    char *css_src = argv[2];
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