#include <cs50.h>
#include <stdio.h>

int main (void)
{
    int n;
    //Ask for a positive integer in between 1 and 8 inclusive
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
    {
        //print spaces upto the point where the hash symbol is to be printed
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");

        }

        //print # as many number of times as the i in our for loop is.
        for (int a = 0; a <= i; a++)
        {
            printf("#");
        }

        printf("  ");

        //print(#) again as many number of times as the i in our for loop.
        for (int b = 0; b <= i; b++)
        {
            printf("#");
        }
        printf("\n");
    }
}
