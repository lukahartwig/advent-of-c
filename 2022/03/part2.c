#include <stdio.h>
#include <string.h>

int c_to_v(char c)
{
    if ('a' <= c && c <= 'z')
    {
        c -= 'a';
    }
    else if ('A' <= c || c <= 'Z')
    {
        c = (c - 'A') + 26;
    }

    return c;
}

int main(void)
{
    int sum = 0, l;
    int read = 0;
    int sets[3][52] = {{0}, {0}, {0}};

    FILE *fp;
    char *line = NULL;
    size_t len = 0;

    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        return 1;
    }

    while (getline(&line, &len, fp) != -1)
    {
        l = strlen(line) - 1;

        for (int i = 0; i < l; i++)
        {
            sets[read][c_to_v(line[i])]++;
        }

        if (read == 2)
        {
            for (int i = 0; i < 52; i++)
            {
                if (sets[0][i] > 0 && sets[1][i] > 0 && sets[2][i] > 0)
                {
                    sum = sum + i + 1;
                }
            }

            for (int i = 0; i < 3; i++)
            {
                memset(sets[i], 0, 52 * sizeof(int));
            }

            read = 0;
        }
        else
        {
            read++;
        }
    }

    printf("%d\n", sum);

    return 0;
}