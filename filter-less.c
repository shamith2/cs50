#include "helpers.h"
#include <math.h>

int limit(int);

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

// limits pixel values to 255
int limit(int RGB)
{
    if (RGB >= 255)
    {
        RGB = 255;
    }

    return RGB;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            // initialization
            RGBTRIPLE *pixel = &image[j][i];
            BYTE org_red = pixel->rgbtRed;
            BYTE org_green = pixel->rgbtGreen;
            BYTE org_blue = pixel->rgbtBlue;

            // new_pixel values
            int new_blue = limit(round(0.272 * org_red + 0.534 * org_green + 0.131 * org_blue));
            int new_green = limit(round(0.349 * org_red + 0.686 * org_green + 0.168 * org_blue));
            int new_red = limit(round(0.393 * org_red + 0.769 * org_green  + 0.189 * org_blue));

            // assign new_pixel values to org_pixels
            pixel->rgbtBlue = new_blue;
            pixel->rgbtGreen = new_green;
            pixel->rgbtRed = new_red;
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
