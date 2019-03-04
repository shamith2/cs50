#include <stdio.h>
#include <cs50.h>
int main()
{
    long int number = 0,number2 = 0,number3 = 0,sum = 0,sum2= 0,sum3 = 0,temp,temp2,temp3,temp4,count = 0;
    do
    {
        number = get_long("Number: ");
    } while(0);
    number3 = number;
    while(number3 != 0)
    {
        temp3 = number3 % 10;
        if(number3 >= 10)
        {
            temp4 = number3 % 100;
        }
        number3 = number3 / 10;
        count = count + 1;
    }
    number2 = number;
    while(number != 0)
    {
        temp = number % 100;
        temp = temp / 10;
        number = number / 100;
        sum = 0;
        sum += temp * 2;
        if(sum >= 10)
        {
            sum3 = sum;
            sum = sum % 10;
            sum2 += sum;
            sum3 = sum3/10;
            sum2 += sum3;
        }
        else
        {
            sum2 += sum;
        }
    }
    while(number2 != 0)
    {
        temp2 = number2 % 10;
        number2 = number2 / 100;
        sum2 += temp2;  
    }
    if(sum2 % 10 == 0)
    {
        if(temp3 == 4 && (count == 13 || count == 16))
        {
            printf("VISA\n");
        }
        else if((temp4 == 51||temp4 == 52||temp4 == 53||temp4 == 54||temp4 == 55) && (count == 16))
        {
            printf("MASTERCARD\n");
        }
        else if((temp4 == 34 || temp4 == 37) && (count == 15))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}
