#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sorting_test.h"

#define MIN -2147483647
#define MAX 2147483647

void sorting_test(void (*sorting_f))
{
    for (int i = 1; i < 102; i++)
    {
        if(!test(sorting_f, i, 0, 10))
        {
            return;
        }
    }
    for (int i = 1; i < 1001; i += 100)
    {
        if(!test(sorting_f, i, -10000, 10000))
        {
            return;
        }
    }
    if(!test(sorting_f, 10000, MIN, MAX))
    {
        return;
    }
    printf("Sorting successful!\n");
}

int test(void (*sorting_f)(int n, int *A), int n, int min, int max)
{
    int A[n];
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        A[i] = rand() % (max * 2) + min;
    }

    // sorting
    (*sorting_f)(n, A);

    // checking
    for (int i = 0; i < n - 1; i++)
    {
        if (A[i] > A[i + 1])
        {
            printf("Fail with:\n");
            printf("n = %d\n", n);
            printf("i = %d\n", i);
            printf("A[i]   = %d\n", A[i]);
            printf("A[i+1] = %d\n\n", A[i + 1]);
            return 0;
        }
    }
    return 1;
}
