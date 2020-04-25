#include <cs50.h>
#include <stdio.h>

void draw(int, char, int);

int main(void)
{   
    int height = 0;

    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height >= 9);

    // draw triangle
    draw(height, ' ', height);
    
    return 0;
}

void draw(int h, char symbol, int height)
{
    // base case
    if (h == 0)
    {
        return;
    }

    // recursion
    draw(h - 1, ' ', height);

    // hth height
    for (int col = 0; col < height * 2 + 2; ++col)
    {
        // symbols in left triangle
        if (col < height - h)
        {
            printf("%c", symbol);
        }

        // '#' in left triangle
        else if (col >= height - h && col < height)
        {
            printf("#");
        }

        // symbols in between triangles
        else if (col >= height && col < height + 2)
        {
            printf("%c", symbol);
        }

        // '#' in right triangles
        else if (col >= height + 2 && col < (height * 2 + 2) - (height - h))
        {
            printf("#");
        }
    }

    printf("\n");
}
