#include <stdio.h>

int main()
{
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

        if (c == '(')
        {
            floor++;
        }
        else if (c == ')')
        {
            floor--;
        }
        else if (c == EOF)
        {
            break;
        }
    };

    printf("%d\n", floor);

    return 0;
}