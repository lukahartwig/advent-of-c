#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;

    int calories;
    int sum = 0;
    int max = 0;

    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        return 1;
    }

    while (getline(&line, &len, fp) != -1)
    {
        if (strcmp(line, "\n") == 0)
        {
            if (sum > max)
            {
                max = sum;
            }

            sum = 0;
        }
        else
        {
            sscanf(line, "%d", &calories);
            sum += calories;
        }
    }

    printf("%d\n", max);

    return 0;
}