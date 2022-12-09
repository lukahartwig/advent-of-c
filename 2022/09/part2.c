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
    int pos[10][2] = {0};
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
            switch (direction)
            {
            case 'U':
                pos[0][1]++;
                break;
            case 'D':
                pos[0][1]--;
                break;
            case 'R':
                pos[0][0]++;
                break;
            case 'L':
                pos[0][0]--;
                break;
            }

            for (int j = 1; j < 10; j++)
            {
                int dx = pos[j - 1][0] - pos[j][0];
                int dy = pos[j - 1][1] - pos[j][1];

                if ((dx == -2 && dy == 1) || (dx == -1 && dy == 2) || (dx == -2 && dy == 2))
                {
                    pos[j][0]--;
                    pos[j][1]++;
                }
                else if (dx == -2 && dy == 0)
                {
                    pos[j][0]--;
                }
                else if ((dx == -2 && dy == -1) || (dx == -1 && dy == -2) || (dx == -2 && dy == -2))
                {
                    pos[j][0]--;
                    pos[j][1]--;
                }
                else if (dx == 0 && dy == -2)
                {
                    pos[j][1]--;
                }
                else if ((dx == 1 && dy == -2) || (dx == 2 && dy == -1) || (dx == 2 && dy == -2))
                {
                    pos[j][0]++;
                    pos[j][1]--;
                }
                else if (dx == 2 && dy == 0)
                {
                    pos[j][0]++;
                }
                else if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2) || (dx == 2 && dy == 2))
                {
                    pos[j][0]++;
                    pos[j][1]++;
                }
                else if (dx == 0 && dy == 2)
                {
                    pos[j][1]++;
                }
            }

            int tail_x = pos[9][0];
            int tail_y = pos[9][1];

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