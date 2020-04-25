#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

float compute_cli(int *w_t);
int *check_text(string s);

int main(void)
{
    // enter text
    string text = get_string("Text: ");

    // compute grade
    int *which_text = check_text(text);
    float cli = compute_cli(which_text);

    // print grade
    if (cli < 1.0)
    {
        printf("Before Grade 1\n");
    }

    else if (cli >= 16.0)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", (int) cli);
    }

    // free space allocated for which_text
    free(which_text);

    return 0;
}

float compute_cli(int *w_t)
{
    // w_t = [letters, sentences, words]
    // L = (letters * 100.0) / words
    float L = (w_t[0] * 100.0) / w_t[2];

    // S = (sentences * 100.0) / words
    float S = (w_t[1] * 100.0) / w_t[2];

    return roundf(0.0588 * L - 0.296 * S - 15.8);
}

int *check_text(string s)
{
    // which_text = [letters, sentences, words]
    int *which_text = (int *) calloc(3, sizeof(int));

    for (int i = 0; s[i] != '\0'; ++i)
    {
        // check for sentences
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            ++which_text[1];
        }

        // check for words
        else if (s[i] == ' ')
        {
            ++which_text[2];
        }

        // check for letters
        else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            ++which_text[0];
        }
    }

    // accounting for the last word in the whole text
    ++which_text[2];

    return which_text;
}
