#include <stdio.h>
#include <string.h>

int main(void)
{
    int a, b, c, d, count = 0;

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
        sscanf(line, "%d-%d,%d-%d", &a, &b, &c, &d);

        if (a <= d && b >= c)
        {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}