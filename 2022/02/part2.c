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
            sum += 0;
            switch (a)
            {
            case 'A':
                sum += 3;
                break;
            case 'B':
                sum += 1;
                break;
            case 'C':
                sum += 2;
                break;
            }
            break;
        case 'Y':
            sum += 3;
            switch (a)
            {
            case 'A':
                sum += 1;
                break;
            case 'B':
                sum += 2;
                break;
            case 'C':
                sum += 3;
                break;
            }
            break;
        case 'Z':
            sum += 6;
            switch (a)
            {
            case 'A':
                sum += 2;
                break;
            case 'B':
                sum += 3;
                break;
            case 'C':
                sum += 1;
                break;
            }
            break;
        }
    }

    printf("%d\n", sum);

    return 0;
}