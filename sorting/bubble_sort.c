#include "sorting_test.h"

void bubble_sort(int n, int A[]);
void swap(int *a, int *b);

int buff;

int main()
{
    sorting_test(bubble_sort);
    return 0;
}

void bubble_sort(int n, int A[])
{
    int not_sorted = 1;
    while(not_sorted) {
        not_sorted = 0;
        for (int i = 0; i < n - 1; i++) {
            if (A[i] > A[i + 1]) {
                not_sorted = 1;
                swap(&A[i], &A[i + 1]);
            }
        }
    }
}

void swap(int *a, int *b)
{
    buff = *a;
    *a = *b;
    *b = buff;
}

