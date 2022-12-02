#include <stdio.h>
#include <string.h>

int main(void)
{
    int calories;
    int tmp_sum = 0;
    int total_sum = 0;
    int max[3] = {0, 0, 0};
    int tmp = 0;

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
        if (strcmp(line, "\n") == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                if (tmp_sum > max[i])
                {
                    tmp = max[i];
                    max[i] = tmp_sum;

                    for (int j = i + 1; j < 3; j++)
                    {
                        tmp_sum = max[j];
                        max[j] = tmp;
                        tmp = tmp_sum;
                    }
                }
            }

            tmp_sum = 0;
        }
        else
        {
            sscanf(line, "%d", &calories);
            tmp_sum += calories;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        total_sum += max[i];
    }

    printf("%d\n", total_sum);

    return 0;
}