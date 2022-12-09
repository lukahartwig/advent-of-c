#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node *sibling;
    struct node *child;
};

struct node *create_node(int value)
{
    struct node *node = malloc(sizeof(struct node));
    node->value = value;
    node->sibling = NULL;
    node->child = NULL;
    return node;
}

struct node *create_tree(int x, int y)
{
    struct node *root = create_node(x);
    struct node *child = create_node(y);
    root->child = child;
    return root;
}

int insert(struct node *root, int x, int y)
{
    struct node *x_node = root;

    while (x_node->value != x && x_node->sibling != NULL)
        x_node = x_node->sibling;

    if (x_node->value == x)
    {
        struct node *y_node = x_node->child;

        while (y_node->value != y && y_node->sibling != NULL)
            y_node = y_node->sibling;

        if (y_node->value == y)
        {
            return 0;
        }
        else
        {
            y_node->sibling = create_node(y);
            return 1;
        }
    }
    else
    {
        x_node->sibling = create_node(x);
        x_node->sibling->child = create_node(y);
        return 1;
    }
}

int main(void)
{
    char direction;
    int steps;
    int head_x = 0, head_y = 0, tail_x = 0, tail_y = 0;
    int unique_pos = 1;
    struct node *root = NULL;

    FILE *fp = fopen("input.txt", "r");
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, fp) != -1)
    {
        sscanf(line, "%c %d", &direction, &steps);

        for (int i = 0; i < steps; i++)
        {
            int dx = head_x - tail_x;
            int dy = head_y - tail_y;

            if (dx == 0 && dy == 0)
            {
                // head and tail is in the same position
                switch (direction)
                {
                case 'U':
                    head_y++;
                    break;
                case 'D':
                    head_y--;
                    break;
                case 'R':
                    head_x++;
                    break;
                case 'L':
                    head_x--;
                    break;
                }
            }
            else if (dx == -1 && dy == 0)
            {
                // head is to the left of tail
                switch (direction)
                {
                case 'U':
                    head_y++;
                    break;
                case 'D':
                    head_y--;
                    break;
                case 'R':
                    head_x++;
                    break;
                case 'L':
                    head_x--;
                    tail_x--;
                    break;
                }
            }
            else if (dx == 1 && dy == 0)
            {
                // head is to the right of tail
                switch (direction)
                {
                case 'U':
                    head_y++;
                    break;
                case 'D':
                    head_y--;
                    break;
                case 'R':
                    head_x++;
                    tail_x++;
                    break;
                case 'L':
                    head_x--;
                    break;
                }
            }
            else if (dx == 0 && dy == -1)
            {
                // head is below tail
                switch (direction)
                {
                case 'U':
                    head_y++;
                    break;
                case 'D':
                    head_y--;
                    tail_y--;
                    break;
                case 'R':
                    head_x++;
                    break;
                case 'L':
                    head_x--;
                    break;
                }
            }
            else if (dx == 0 && dy == 1)
            {
                // head is above tail
                switch (direction)
                {
                case 'U':
                    head_y++;
                    tail_y++;
                    break;
                case 'D':
                    head_y--;
                    break;
                case 'R':
                    head_x++;
                    break;
                case 'L':
                    head_x--;
                    break;
                }
            }
            else if (dx == -1 && dy == -1)
            {
                // head is to the left and below tail
                switch (direction)
                {
                case 'U':
                    head_y++;
                    break;
                case 'D':
                    head_y--;
                    tail_x--;
                    tail_y--;
                    break;
                case 'R':
                    head_x++;
                    break;
                case 'L':
                    head_x--;
                    tail_x--;
                    tail_y--;
                    break;
                }
            }
            else if (dx == -1 && dy == 1)
            {
                // head is to the left and above tail
                switch (direction)
                {
                case 'U':
                    head_y++;
                    tail_x--;
                    tail_y++;
                    break;
                case 'D':
                    head_y--;
                    break;
                case 'R':
                    head_x++;
                    break;
                case 'L':
                    head_x--;
                    tail_x--;
                    tail_y++;
                    break;
                }
            }
            else if (dx == 1 && dy == -1)
            {
                // head is to the right and below tail
                switch (direction)
                {
                case 'U':
                    head_y++;
                    break;
                case 'D':
                    head_y--;
                    tail_x++;
                    tail_y--;
                    break;
                case 'R':
                    head_x++;
                    tail_x++;
                    tail_y--;
                    break;
                case 'L':
                    head_x--;
                    break;
                }
            }
            else if (dx == 1 && dy == 1)
            {
                // head is to the right and above tail
                switch (direction)
                {
                case 'U':
                    head_y++;
                    tail_x++;
                    tail_y++;
                    break;
                case 'D':
                    head_y--;
                    break;
                case 'R':
                    head_x++;
                    tail_x++;
                    tail_y++;
                    break;
                case 'L':
                    head_x--;
                    break;
                }
            }

            if (root == NULL)
            {
                root = create_tree(tail_x, tail_y);
            }
            else
            {
                unique_pos += insert(root, tail_x, tail_y);
            }
        }
    }

    printf("%d\n", unique_pos);
    return 0;
}