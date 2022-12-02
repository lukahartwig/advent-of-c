#include <stdio.h>
#include <string.h>

int main(void)
{
    char a, b;
    int sum = 0;

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
        sscanf(line, "%c %c", &a, &b);

        switch (b)
        {
        case 'X':
            sum += 1;
            switch (a)
            {
            case 'A':
                sum += 3;
                break;
            case 'B':
                sum += 0;
                break;
            case 'C':
                sum += 6;
                break;
            }
            break;
        case 'Y':
            sum += 2;
            switch (a)
            {
            case 'A':
                sum += 6;
                break;
            case 'B':
                sum += 3;
                break;
            case 'C':
                sum += 0;
                break;
            }
            break;
        case 'Z':
            sum += 3;
            switch (a)
            {
            case 'A':
                sum += 0;
                break;
            case 'B':
                sum += 6;
                break;
            case 'C':
                sum += 3;
                break;
            }
            break;
        }
    }

    printf("%d\n", sum);

    return 0;
}