/* Program to recover JPEGs from a forensic image
 * Copyright: Shamith Achanta
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
#define B 512

int main(int argc, char *argv[])
{
    // error check
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // error check
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }

    // counter for number of photos
    int photos = 0;

    // bool for checking is .jpg is open
    int jpg_open = 0; // false

    // buffer
    BYTE *arr = malloc(B * sizeof(BYTE));

    // jpeg image file
    FILE *photo = NULL;

    // read into buffer from file
    while (fread(arr, sizeof(BYTE), B, file))
    {
        // check for .jpg file
        if (arr[0] == 0xff && arr[1] == 0xd8 && arr[2] == 0xff && (arr[3] >= 0xe0 && arr[3] <= 0xef))
        {
            // name file using sprintf
            char name[8];
            sprintf(name, "%03d.jpg", photos);

            // if .jpg file is open,
            // close it
            if (jpg_open)
            {
                fclose(photo);
                jpg_open = 0;
            }

            // if valid, open file
            photo = fopen(name, "w");
            if (photo != NULL)
            {
                jpg_open = 1;
                ++photos;
            }

            // else,
            // terminate program
            else
            {
                fclose(photo);
                fclose(file);
                free(arr);
                return 1;
            }
        }

        // copy contents from buffer to .jpg file if open
        if (jpg_open)
        {
            fwrite(arr, sizeof(BYTE), B, photo);
        }
    }

    // freeing memory and closing file
    fclose(photo);
    free(arr);
    fclose(file);

    return 0;
}
