#include <cs50.h>
#include <stdio.h>

void left_draw(int);
void right_draw(int, char);

int main(void)
{   
    int height = 0;

    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height >= 9);

    // draw right triangle
    right_draw(height, ' ');

    return 0;
}

// draws triangle towards right
void right_draw(int h, char symbol)
{
    for (int row = 0; row < h; ++row)
    {
        for (int col = 0; col < h; ++col)
        {
            if (col < h - row - 1)
            {
                printf("%c",symbol);
            }

            else
            {
                printf("#");
            }
        }

        printf("\n");
    }
}

// draws triangle towards left
void left_draw(int h)
{
    for (int row = 0; row < h; ++row)
    {
        for (int col = 0; col <= row; ++col)
        {
            printf("#");
        }

        printf("\n");
    }
}
