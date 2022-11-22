#include <stdio.h>
#include <time.h>

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
    {
        ;
    }
}

void flushStdout(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\b");
    }
}

// Progress [] 100%

int main(int argc, char **argv)
{
    // for (int i = 0; i < 100; i++)
    // {
    //     flushStdout()
    // }
    printf("[");
    for (int i = 0; i < 50; i++)
    {
        printf("#");
        delay(500);
    }
    printf("]\n");
}