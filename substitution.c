#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

void substitute(string p, string k);
bool check_key(string k);
char lower(char l);
char upper(char u);

int main(int argc, char **argv)
{
    // inappropriate key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // inappropriate key length
    if (strlen(argv[1]) != 26 || atoi(argv[1]) != 0)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // inappropriate character
    if (!check_key(argv[1]))
    {
        printf("Key contains invalid or duplicate characters.\n");
        return 1;
    }

    // text to be substituted
    string text = get_string("plaintext: ");

    // convert and print ciphertext
    substitute(text, argv[1]);
    printf("ciphertext: %s\n", text);

    return 0;
}

// create ciphertext from plaintext
void substitute(string p, string k)
{
    for (int i = 0; p[i] != '\0'; ++i)
    {
        if (p[i] >= 'a' && p[i] <= 'z')
        {
            p[i] = lower(k[p[i] - 'a']);
        }

        else if (p[i] >= 'A' && p[i] <= 'Z')
        {
            p[i] = upper(k[p[i] - 'A']);
        }
    }
}

bool check_key(string k)
{
    // make characters in key into a single case
    for (int i = 0; k[i] != '\0'; ++i)
    {
        k[i] = lower(k[i]);
    }

    // check for invalid characters
    for (int i = 0; k[i] != '\0'; ++i)
    {
        // if character is not lower case
        if (!(k[i] >= 'a' && k[i] <= 'z'))
        {
            return false;
        }
    }

    // check for duplicate characters
    for (int counter = 0; k[counter] != '\0'; ++counter)
    {
        for (int i = 0; k[i] != '\0'; ++i)
        {
            if (k[counter] == k[i] && i != counter)
            {
                return false;
            }
        }
    }

    return true;
}

char lower(char l)
{
    // converts upper case to lower case
    if (l >= 'A' && l <= 'Z')
    {
        l += ('a' - 'A');
    }

    return l;
}

char upper(char u)
{
    // converts lower case to upper case
    if (u >= 'a' && u <= 'z')
    {
        u -= ('a' - 'A');
    }

    return u;
}
