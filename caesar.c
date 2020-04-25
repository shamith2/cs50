#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

void cipher(string s, int k);

int main(int argc, char **argv)
{
    // check on command-line argument
    if (argc != 2 || atoi(argv[1]) <= 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // text to be ciphered
    string text = get_string("plaintext: ");

    // convert and print ciphered text
    cipher(text, atoi(argv[1])); // atoi := strtol(argv[1], NULL, 10)
    printf("ciphertext: %s\n", text);

    return 0;
}

void cipher(string p, int k)
{
    // converting text to cipher text
    for (int i = 0; p[i] != '\0'; ++i)
    {
        // convert alphabets only
        if (p[i] >= 'a' && p[i] <= 'z')
        {
            p[i] = 'a' + ((p[i] - 'a' + k) % 26);
        }

        else if (p[i] >= 'A' && p[i] <= 'Z')
        {
            p[i] = 'A' + ((p[i] - 'A' + k) % 26);
        }
    }
}
