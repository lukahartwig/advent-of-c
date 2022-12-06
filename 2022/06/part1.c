#include <stdio.h>
#include <stdbool.h>

#define MARKER_SIZE 4

bool is_unique_marker(char *marker)
{
    for (int i = 0; i < MARKER_SIZE; i++)
    {
        if (marker[i] == 0)
        {
            return false;
        }

        for (int j = i + 1; j < MARKER_SIZE; j++)
        {
            if (marker[i] == marker[j])
            {
                return false;
            }
        }
    }

    return true;
}

int main(void)
{
    int i = 0;
    char c;
    char marker[MARKER_SIZE] = {0};

    FILE *fp;

    if ((fp = fopen("input.txt", "r")) == NULL)
    {
        return 1;
    }

    while ((c = fgetc(fp)) != EOF)
    {
        marker[i % MARKER_SIZE] = c;

        if (is_unique_marker(marker))
        {
            break;
        }

        i++;
    }

    printf("%d\n", i + 1);

    return 0;
}