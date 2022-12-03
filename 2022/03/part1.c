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

    int set_a[52] = {0};
    int set_b[52] = {0};

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

        for (int i = 0; i < l / 2; i++)
        {
            set_a[c_to_v(line[i])]++;
        }

        for (int i = l / 2; i < l; i++)
        {
            set_b[c_to_v(line[i])]++;
        }

        for (int i = 0; i < 52; i++)
        {
            if (set_a[i] > 0 && set_b[i] > 0)
            {
                sum = sum + i + 1;
            }
        }

        memset(set_a, 0, 52 * sizeof(int));
        memset(set_b, 0, 52 * sizeof(int));
    }

    printf("%d\n", sum);

    return 0;
}