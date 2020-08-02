#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long creditNumber = get_long("What's your chedit card number? ");

    // AMEX

    if (creditNumber >= 340000000000000 && creditNumber <= 380000000000000)
    {
        int start = floor(creditNumber / 10000000000000);
        if (start == 34 || start == 37)
        {
            // sum of evey other
            int sum = 0;
            for (long i = 100; i <= 100000000000000; i = i * 100)
            {
                long current = floor((creditNumber % i) / (i / 10));
                int timesTwo = (current * 2);
                if (timesTwo > 9)
                {
                    sum += (timesTwo % 10);
                    sum += floor(timesTwo / 10);
                }
                else
                {
                    sum += timesTwo;
                }
            }
            for (long j = 10; j <= 1000000000000000; j = j * 100)
            {
                long digit = floor((creditNumber % j) / (j / 10));
                sum += digit;
            }
            if (sum % 10 == 0)
            {
                printf("AMEX\n");
                return 0;
            }
            else
            {
                printf("INVALID\n");
                return 0;
            }
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }

    }
    // MASTERCARD
    else if (creditNumber > 5100000000000000 && creditNumber < 5600000000000000)
    {
        int sum = 0;
        for (long i = 100; i <= 10000000000000000; i = i * 100)
        {
            long current = floor((creditNumber % i) / (i / 10));
            int timesTwo = (current * 2);
            if (timesTwo > 9)
            {
                sum += (timesTwo % 10);
                sum += floor(timesTwo / 10);
            }
            else
            {
                sum += timesTwo;
            }
        }
        for (long j = 10; j <= 1000000000000000; j = j * 100)
        {
            long digit = floor((creditNumber % j) / (j / 10));
            sum += digit;
        }
        if (sum % 10 == 0)
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    // VISA 13
    else if (creditNumber > 4000000000000 && creditNumber < 5000000000000)
    {
        int sum = 0;
        for (long i = 100; i <= 1000000000000; i = i * 100)
        {
            long current = floor((creditNumber % i) / (i / 10));
            int timesTwo = (current * 2);
            if (timesTwo > 9)
            {
                sum += (timesTwo % 10);
                sum += floor(timesTwo / 10);
            }
            else
            {
                sum += timesTwo;
            }
        }
        for (long j = 10; j <= 10000000000000; j = j * 100)
        {
            long digit = floor((creditNumber % j) / (j / 10));
            sum += digit;
        }
        if (sum % 10 == 0)
        {
            printf("VISA\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    // VISA 16
    else if (creditNumber > 4000000000000000 && creditNumber < 5000000000000000)
    {
        int sum = 0;
        for (long i = 100; i <= 10000000000000000; i = i * 100)
        {
            long current = floor((creditNumber % i) / (i / 10));
            int timesTwo = (current * 2);
            if (timesTwo > 9)
            {
                sum += (timesTwo % 10);
                sum += floor(timesTwo / 10);
            }
            else
            {
                sum += timesTwo;
            }
        }
        for (long j = 10; j <= 1000000000000000; j = j * 100)
        {
            long digit = floor((creditNumber % j) / (j / 10));
            sum += digit;
        }
        if (sum % 10 == 0)
        {
            printf("VISA\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}