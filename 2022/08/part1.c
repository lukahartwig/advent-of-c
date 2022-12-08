#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *read_file(char *filename)
{
    FILE *fp = fopen("input.txt", "r");
    fseek(fp, 0, SEEK_END);
    long bufsize = ftell(fp);
    char *buffer = malloc(sizeof(char) * (bufsize + 1));
    fseek(fp, 0, SEEK_SET);
    size_t len = fread(buffer, sizeof(char), bufsize, fp);
    buffer[len + 1] = '\0';
    fclose(fp);
    return buffer;
}

int main(void)
{
    char *file = read_file("input.txt");

    int height = 0;
    int width = 0;

    for (int i = 0; file[i] != '\0'; i++)
    {
        if (file[i] == '\n')
        {
            if (width == 0)
                width = i;

            height++;
        }
    }

    short grid[height * width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int file_index = row * (width + 1) + col;
            int grid_index = row * width + col;
            grid[grid_index] = file[file_index] - '0';
        }
    }

    short top[height * width];
    short bottom[height * width];
    for (int col = 0; col < width; col++)
    {
        short top_max = -1;
        short bottom_max = -1;

        for (int row = 0; row < height; row++)
        {
            int top_index = row * width + col;
            int bottom_index = (height - row - 1) * width + col;

            if (grid[top_index] > top_max)
            {
                top_max = grid[top_index];
                top[top_index] = 1;
            }
            else
            {
                top[top_index] = 0;
            }

            if (grid[bottom_index] > bottom_max)
            {
                bottom_max = grid[bottom_index];
                bottom[bottom_index] = 1;
            }
            else
            {
                bottom[bottom_index] = 0;
            }
        }
    }

    short left[height * width];
    short right[height * width];
    for (int row = 0; row < height; row++)
    {
        short left_max = -1;
        short right_max = -1;
        for (int col = 0; col < width; col++)
        {
            int left_index = row * width + col;
            int right_index = row * width + (width - col - 1);

            if (grid[left_index] > left_max)
            {
                left_max = grid[left_index];
                left[left_index] = 1;
            }
            else
            {
                left[left_index] = 0;
            }

            if (grid[right_index] > right_max)
            {
                right_max = grid[right_index];
                right[right_index] = 1;
            }
            else
            {
                right[right_index] = 0;
            }
        }
    }

    int result = 0;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int i = row * width + col;
            result += top[i] | left[i] | right[i] | bottom[i];
        }
    }

    printf("%d\n", result);

    return 0;
}