#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char *name;
    size_t size;
    struct node *parent;
    struct node **children;
} node;

node *new_node(char *name)
{
    node *n = malloc(sizeof(node));
    n->name = name;
    n->size = 0;
    n->parent = NULL;
    n->children = NULL;
    return n;
}

void append_child(node *parent, node *child)
{
    int i = 0;
    while (parent->children[i] != NULL)
    {
        i++;
    }
    parent->children[i] = child;
    child->parent = parent;
}

node *parse_file(char *line)
{
    char *name;
    size_t size;
    sscanf(line, "%d %s", &size, name);
    node *n = new_node(name);
    n->size = size;
    return n;
}

node *parse_directory(char *line)
{
    char *name;
    sscanf(line, "dir %s", name);
    node *n = new_node(name);
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
        // cd
        char *arg;
        sscanf(line, "$ cd %s", arg);
        return new_cd_cmd(arg);
    }
    else if (c == 'l')
    {
        // ls
        return new_ls_cmd();
    }
}

void print_cwd(node *cwd)
{
    if (cwd->parent != NULL)
    {
        print_cwd(cwd->parent);

        if (cwd->name != "/")
        {
            printf("/");
        }
    }
    printf("%s", cwd->name);
}

void handle_command(cmd *command, node *cwd)
{
    if (command->name == "cd")
    {
        char *arg = command->arg;

        if (arg == "..")
        {
            if (cwd->parent != NULL)
            {
                *cwd = *cwd->parent;
            }
        }
        else
        {
            node *child;
            int i = 0;
            while ((child = cwd->children[i]) != NULL)
            {
                if (child->name == arg)
                {
                    *cwd = *child;
                    break;
                }
                i++;
            }
        }

        print_cwd(cwd);
    }
}

int main(void)
{
    FILE *fp = fopen("input.txt", "r");
    char *line = NULL;
    size_t len = 0;

    node *root = new_node("/");
    node *cwd = root;

    print_cwd(cwd);

    while (getline(&line, &len, fp) != -1)
    {
        char c = line[0];

        if (c == '$')
        {
            // is command
            cmd *command = parse_command(line);
            handle_command(command, cwd);
        }
        else if ('1' <= c && c <= '9')
        {
            // is file
            node *file = parse_file(line);
            append_child(cwd, file);
        }
        else if (c == 'd')
        {
            // is directory
            node *dir = parse_directory(line);
            append_child(cwd, dir);
        }
    }

    return 0;
}