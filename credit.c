/* Program to compute change
 * Copyright: Shamith Achanta 
 */

#include <stdio.h>
#include <math.h>
#include <cs50.h>

string luhn_algo(long int);
string which_card(int, int, bool);
int break_sum(int);

int main(void)
{
    // accept card number from user
    long int number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);

    // compute card
    printf("%s\n", luhn_algo(number));

    return 0;
}

// compute if card is valid
string luhn_algo(long int num)
{
    // variables
    long int n = num;          // copy of number
    int sum = 0;              // sum
    int f = 0;               // first two digits
    int len = 0;            // length
    int i = 0;             // counter
    int j = 0;            // counter
    int d = 0;           // digit
    bool visa = false;  // visa card

    // compute length
    while (n > 0)
    {
        n /= 10;
        ++len;
    }

    // compute if card is valid
    while (i < len) // or (num > 0)
    {
        // digit
        d = num % 10;

        // Step 0: First Two digits of the number
        if (i >= len - 2)
        {
            // check for VISA
            if ((i == len - 1) && d == 4)
            {
                visa = true;
            }

            f += d * pow(10, j);
            ++j;    // ten's power
        }

        // Step 1: Multiply every other digit by 2,
        // starting with the number’s second-to-last digit,
        // and then add those products’ digits together
        if (i % 2 == 0)
        {
            sum += d;
        }

        // Step 2: Add the sum to the sum of the digits
        // that weren’t multiplied by 2
        else if (i % 2 != 0)
        {
            sum += break_sum(d);
        }

        // for next digit
        num /= 10;
        ++i;
    }

    // Step 3: If the total’s last digit is 0,
    // the number is valid!
    if (sum % 10 == 0)
    {
        return which_card(f, len, visa);
    }

    return "INVALID";
}

// sum of digits
// for digits > 4
int break_sum(int d)
{
    int s = d * 2;
    int r = 0;

    if (s > 8)
    {
        while (s > 0)
        {
            r += s % 10;
            s /= 10;
        }

        return r;
    }

    return s;
}

// compute whether the card
// is VISA, AMEX or MASTERCARD
string which_card(int digits, int len, bool visa)
{
    // check if AMEX card
    if ((digits == 34 || digits == 37) && len == 15)
    {
        return "AMEX";
    }

    // check if VISA
    else if (visa && (len == 13 || len == 16))
    {
        return "VISA";
    }

    // check if MASTERCARD
    else if (digits >= 51 && digits <= 55 && len == 16)
    {
        return "MASTERCARD";
    }

    // check if INVALID
    else
    {
        return "INVALID";
    }
}
