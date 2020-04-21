/* Program to compute change
 * Copyright: Shamith Achanta 
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// type: coin
typedef struct result
{
    int *cent;
    int len;
    int total;
} coin;

coin change_to_coins(float);
int check_change(float, int);

int main(int argc, char **argv)
{
    // error check: 1
    if (argc != 2)
    {
        printf("\n:( Usage: ./cash change. Example: for a change of $2.41, enter './cash 0.41'.\n\n");
        return 1;
    }

    // change from user
    float change = atof(argv[1]);

    // coins to be given
    coin coins = change_to_coins(change);

    // error check: 2
    if (!check_change(change, coins.total))
    {
        printf("\n:( Enter positive amounts or check usage. Example: for a change of $2.41, enter './cash 0.41'.\n\n");
        return 2;
    }

    // print result to user
    // formatted result
    printf("\nCoins:\n");
    printf("\t25c:\t10c:\t5c:\t1c:\t\n\t");
    for (int i = 0; i < coins.len; ++i)
    {
        printf("     %i\t", coins.cent[i]);
    }
    printf("\n\nTotal:\t%i", coins.total);


    // free allocated memory for coins
    free(coins.cent);

    // success message
    printf("\n\n:) Check your Change. Have a Good Day !!\n\n");
    return 0;
}

// computes the cash to be given
// greedy algorithm
coin change_to_coins(float c)
{
    // coins available: 25c, 10c 5c, 1c
    int coins[] = {25, 10, 5, 1};
    coin cash;
    cash.len = sizeof(coins)/sizeof(int);
    cash.cent = (int *) calloc(cash.len, sizeof(int));
    cash.total = 0;

    // change owed
    int cents = round(c * 100);

    // formula
    for (int i = 0; i < cash.len; ++i)
    {
        cash.cent[i] = cents / coins[i];
        cash.total += cash.cent[i];
        cents -= coins[i] * cash.cent[i];
    }

    // return result
    return cash;
}

// checks whether change is entered correctly
int check_change(float c, int t)
{
    if (c <= 0 || t == 0 || c >= 100)
    {
        return 0;
    }

    return 1;
}
