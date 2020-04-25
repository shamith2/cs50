#include "helpers.h"
#include <math.h>

int cap(int);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            // compute average of RGB and assign to org_pixels
            RGBTRIPLE *pixel = &image[j][i];
            BYTE avg = round((pixel->rgbtBlue + pixel->rgbtGreen + pixel->rgbtRed) / 3.0);
            pixel->rgbtBlue = avg;
            pixel->rgbtGreen = avg;
            pixel->rgbtRed = avg;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width / 2; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            // initialization
            RGBTRIPLE *pixel = &image[j][i];
            RGBTRIPLE *new_pixel = &image[j][width - (i + 1)];
            BYTE temp_pixel[3] = {pixel->rgbtBlue, pixel->rgbtGreen, pixel->rgbtRed};

            // swap
            pixel->rgbtBlue = new_pixel->rgbtBlue;
            pixel->rgbtGreen = new_pixel->rgbtGreen;
            pixel->rgbtRed = new_pixel->rgbtRed;

            // assign temp_pixel to new_pixel
            new_pixel->rgbtBlue = temp_pixel[0];
            new_pixel->rgbtGreen = temp_pixel[1];
            new_pixel->rgbtRed = temp_pixel[2];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_pixels[height][width];

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            // initialization
            RGBTRIPLE *pixel = &image[j][i];
            int blue = 0;
            int green = 0;
            int red = 0;
            int pixels = 0;

            for (int x = i - 1; x <= i + 1; ++x)
            {
                for (int y = j - 1; y <= j + 1; ++y)
                {
                    // check for out of bounds
                    if ((x >= 0 && x <= width - 1) && (y >= 0 && y <= height - 1))
                    {

                        // compute sum
                        RGBTRIPLE *neighbour = &image[y][x];
                        blue += neighbour->rgbtBlue;
                        green += neighbour->rgbtGreen;
                        red += neighbour->rgbtRed;
                        ++pixels;
                    }
                }
            }

            // compute average and store in temp_pixels
            RGBTRIPLE *temp_pixel = &temp_pixels[j][i];
            temp_pixel->rgbtBlue = round(blue / (pixels * 1.0));
            temp_pixel->rgbtGreen = round(green / (pixels * 1.0));
            temp_pixel->rgbtRed = round(red / (pixels * 1.0));
        }
    }

    //copies values from temporary table
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // copy temp_pixels to org_pixels
            RGBTRIPLE *pixel = &image[j][i];
            RGBTRIPLE *temp_pixel = &temp_pixels[j][i];
            pixel->rgbtBlue = temp_pixel->rgbtBlue;
            pixel->rgbtGreen = temp_pixel->rgbtGreen;
            pixel->rgbtRed = temp_pixel->rgbtRed;
        }
    }

    return;
}

// limits pixel values to 255
int cap(int RGB)
{
    if (RGB >= 255)
    {
        RGB = 255;
    }

    return RGB;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // sobel algorithm: Gx and Gy matrices
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE temp_pixels[height][width];

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            // initialization
            RGBTRIPLE *pixel = &image[j][i];
            int blue_x = 0;
            int blue_y = 0;
            int green_x = 0;
            int green_y = 0;
            int red_x = 0;
            int red_y = 0;

            for (int x = i - 1; x <= i + 1; ++x)
            {
                for (int y = j - 1; y <= j + 1; ++y)
                {
                    // check for out of bounds
                    if ((x >= 0 && x <= width - 1) && (y >= 0 && y <= height - 1))
                    {

                        // compute sum
                        RGBTRIPLE *neighbour = &image[y][x];

                        // blue gx and blue gy
                        blue_x += (neighbour->rgbtBlue) * Gx[y - (j - 1)][x - (i - 1)];
                        blue_y += (neighbour->rgbtBlue) * Gy[y - (j - 1)][x - (i - 1)];

                        // green gx and gy
                        green_x += (neighbour->rgbtGreen) * Gx[y - (j - 1)][x - (i - 1)];
                        green_y += (neighbour->rgbtGreen) * Gy[y - (j - 1)][x - (i - 1)];

                        // red gx and gy
                        red_x += (neighbour->rgbtRed) * Gx[y - (j - 1)][x - (i - 1)];
                        red_y += (neighbour->rgbtRed) * Gy[y - (j - 1)][x - (i - 1)];
                    }
                }
            }

            // compute sobel algorithm and store in temp_pixels
            RGBTRIPLE *temp_pixel = &temp_pixels[j][i];
            temp_pixel->rgbtBlue = cap(round(sqrt(pow(blue_x, 2) + pow(blue_y, 2))));
            temp_pixel->rgbtGreen = cap(round(sqrt(pow(green_x, 2) + pow(green_y, 2))));
            temp_pixel->rgbtRed = cap(round(sqrt(pow(red_x, 2) + pow(red_y, 2))));
        }
    }

    //copies values from temporary table
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            // copy temp_pixels to org_pixels
            RGBTRIPLE *pixel = &image[j][i];
            RGBTRIPLE *temp_pixel = &temp_pixels[j][i];
            pixel->rgbtBlue = temp_pixel->rgbtBlue;
            pixel->rgbtGreen = temp_pixel->rgbtGreen;
            pixel->rgbtRed = temp_pixel->rgbtRed;
        }
    }

    return;
}
