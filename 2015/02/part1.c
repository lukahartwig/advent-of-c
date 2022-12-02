#include <stdio.h>

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
        result += 2 * l * w + 2 * w * h + 2 * h * l;

        if (l * w < w * h && l * w < h * l)
        {
            result += l * w;
        }
        else if (w * h < h * l)
        {
            result += w * h;
        }
        else
        {
            result += h * l;
        }
    }

    printf("Result: %d\n", result);

    return 0;
}