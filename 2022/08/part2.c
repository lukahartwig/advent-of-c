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

    int max_scenic_score = 0;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int index = row * width + col;
            short tree_height = grid[index];

            int top_score = 0;
            for (int row_offset = 1; (row - row_offset) >= 0; row_offset++)
            {
                int top_index = (row - row_offset) * width + col;
                short top_tree_height = grid[top_index];

                top_score++;

                if (top_tree_height >= tree_height)
                    break;
            }

            int bottom_score = 0;
            for (int row_offset = 1; (row + row_offset) < height; row_offset++)
            {
                int bottom_index = (row + row_offset) * width + col;
                short bottom_tree_height = grid[bottom_index];

                bottom_score++;

                if (bottom_tree_height >= tree_height)
                    break;
            }

            int left_score = 0;
            for (int col_offset = 1; (col - col_offset) >= 0; col_offset++)
            {
                int left_index = row * width + (col - col_offset);
                short left_tree_height = grid[left_index];

                left_score++;

                if (left_tree_height >= tree_height)
                    break;
            }

            int right_score = 0;
            for (int col_offset = 1; (col + col_offset) < width; col_offset++)
            {
                int right_index = row * width + (col + col_offset);
                short right_tree_height = grid[right_index];

                right_score++;

                if (right_tree_height >= tree_height)
                    break;
            }

            int scenic_score = top_score * bottom_score * left_score * right_score;
            if (scenic_score > max_scenic_score)
                max_scenic_score = scenic_score;
        }
    }

    printf("%d\n", max_scenic_score);

    return 0;
}