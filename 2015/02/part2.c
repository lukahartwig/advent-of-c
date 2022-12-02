#include <stdio.h>
#include <stdlib.h>

int main()
{
    int l, w, h, result = 0;

    FILE *f;
    char *line = NULL;
    size_t len = 0;

    f = fopen("input.txt", "r");
    if (f == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    while ((getline(&line, &len, f)) != -1)
    {
        sscanf(line, "%dx%dx%d", &l, &w, &h);
        result += l * w * h;

        if (l + w < w + h && l + w < h + l)
        {
            result += 2 * l + 2 * w;
        }
        else if (w + h < h + l)
        {
            result += 2 * w + 2 * h;
        }
        else
        {
            result += 2 * h + 2 * l;
        }
    }

    printf("Result: %d\n", result);
    return 0;
}