#include <stdio.h>

int main()
{
    int pos = 1;
    int floor = 0;

    FILE *f = fopen("input.txt", "r");

    if (f == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    while (1)
    {
        char c = fgetc(f);

        if (c == EOF)
        {
            printf("Error: Reached end of file without finding basement\n");
            return 1;
        }

        if (c == '(')
        {
            floor++;
        }
        else if (c == ')')
        {
            floor--;
        }

        if (floor < 0)
        {
            break;
        }

        pos++;
    };

    printf("%d\n", pos);

    return 0;
}