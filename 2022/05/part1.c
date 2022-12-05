#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void move(char **stacks, int count, int from, int to)
{
    // Allocate memory for the items to be moved
    char *items = malloc(sizeof(char) * (count + 1));

    // Copy the items to be moved to the allocated memory
    strcpy(items, stacks[from - 1] + strlen(stacks[from - 1]) - count);
    items[count] = '\0';

    // Remove the items from the original stack
    stacks[from - 1][strlen(stacks[from - 1]) - count] = '\0';

    // Reverse the items
    for (int i = 0; i < count / 2; i++)
    {
        char temp = items[i];
        items[i] = items[count - i - 1];
        items[count - i - 1] = temp;
    }

    // Add the items to the destination stack
    strcat(stacks[to - 1], items);

    // Free the allocated memory
    free(items);
}

int main(void)
{
    int count, from, to;

    FILE *fp;
    char *line = NULL;
    size_t len = 0;

    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        return 1;
    }

    // Read first line to get the number of stacks
    getline(&line, &len, fp);
    int stack_count = strlen(line) / 4;

    // Allocate memory for the stacks and initialize them
    char **stacks = malloc(sizeof(char *) * stack_count);
    for (int i = 0; i < stack_count; i++)
    {
        stacks[i] = malloc(sizeof(char) * 100);
        strcpy(stacks[i], "");
    }

    do
    {
        // When the line starts with a number, we've reached the end of the stacks
        if ('1' <= line[1] && line[1] <= '9')
        {
            getline(&line, &len, fp); // Skip the empty line
            break;
        }

        for (int i = 0; i < stack_count; i++)
        {
            char c = line[(i * 4) + 1];
            if (c != ' ')
            {
                strncat(stacks[i], &c, 1);
            }
        }
    } while (getline(&line, &len, fp) != -1);

    // Reverse the stacks
    for (int i = 0; i < stack_count; i++)
    {
        for (int j = 0; j < strlen(stacks[i]) / 2; j++)
        {
            char temp = stacks[i][j];
            stacks[i][j] = stacks[i][strlen(stacks[i]) - j - 1];
            stacks[i][strlen(stacks[i]) - j - 1] = temp;
        }
    }

    while (getline(&line, &len, fp) != -1)
    {
        sscanf(line, "move %d from %d to %d", &count, &from, &to);
        move(stacks, count, from, to);
    }

    for (int i = 0; i < stack_count; i++)
    {
        printf("%c", stacks[i][strlen(stacks[i]) - 1]);
    }
    printf("\n");

    return 0;
}