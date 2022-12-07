#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char *name;
    size_t size;
    struct node *parent;
    struct node *child;
    struct node *sibling;
} node_t;

node_t *new_node(char *name)
{
    node_t *n = malloc(sizeof(node_t));

    n->name = malloc(strlen(name) + 1);
    strcpy(n->name, name);

    n->size = 0;
    n->parent = NULL;
    n->child = NULL;
    n->sibling = NULL;

    return n;
}

void append_child(struct node *parent, struct node *child)
{
    if (parent->child == NULL)
    {
        parent->child = child;
    }
    else
    {
        struct node *last_child = parent->child;

        while (last_child->sibling != NULL)
            last_child = last_child->sibling;

        last_child->sibling = child;
    }

    child->parent = parent;
}

node_t *parse_file(char *line)
{
    char name[100];
    size_t size;
    sscanf(line, "%zu %s", &size, name);
    node_t *n = new_node(name);
    n->size = size;
    return n;
}

node_t *parse_directory(char *line)
{
    char name[100];
    sscanf(line, "dir %s", name);
    node_t *n = new_node(name);
    return n;
}

typedef struct cmd
{
    char *name;
    char *arg;
} cmd;

cmd *new_cd_cmd(char *arg)
{
    cmd *c = malloc(sizeof(cmd));
    c->name = "cd";
    c->arg = arg;
    return c;
}

cmd *new_ls_cmd()
{
    cmd *c = malloc(sizeof(cmd));
    c->name = "ls";
    c->arg = NULL;
    return c;
}

cmd *parse_command(char *line)
{
    char c = line[2];

    if (c == 'c')
    {
        char arg[100];
        sscanf(line, "$ cd %s", arg);
        return new_cd_cmd(arg);
    }
    else if (c == 'l')
    {
        return new_ls_cmd();
    }
}

void cd(struct node **cwd, char *path)
{
    struct node *node = *cwd;

    if (strcmp(path, "/") == 0)
    {
        while (node->parent != NULL)
        {
            node = node->parent;
        }
        *cwd = node;
    }
    else if (strcmp(path, "..") == 0)
    {
        *cwd = node->parent;
    }
    else
    {
        node_t *child = node->child;

        while (child != NULL)
        {
            if (strcmp(child->name, path) == 0)
            {
                *cwd = child;
                break;
            }

            child = child->sibling;
        }
    }
}

void handle_command(cmd *command, node_t **cwd)
{
    if (command->name == "cd")
    {
        cd(cwd, command->arg);
    }
}

long get_total_size(node_t *node)
{
    long size = node->size;

    for (node_t *child = node->child; child != NULL; child = child->sibling)
    {
        size += get_total_size(child);
    }

    if (node->size == 0 && ((size - 4804833) > 0))
    {
        printf("%ld\n", size);
    }

    return size;
}

int main(void)
{
    FILE *fp = fopen("input.txt", "r");
    char *line = NULL;
    size_t len = 0;

    node_t *root = new_node("/");
    node_t *cwd = root;

    while (getline(&line, &len, fp) != -1)
    {
        char c = line[0];

        if (c == '$')
        {
            // is command
            cmd *command = parse_command(line);
            handle_command(command, &cwd);
        }
        else if ('1' <= c && c <= '9')
        {
            // is file
            node_t *file = parse_file(line);
            append_child(cwd, file);
        }
        else if (c == 'd')
        {
            // is directory
            node_t *dir = parse_directory(line);
            append_child(cwd, dir);
        }
    }

    long total_size = get_total_size(root);
    long needed_space = 30000000 - (70000000 - total_size);

    return 0;
}