#include "sorting_test.h"

void insertion_sort(int, int*);
void swap(int*, int*);

int buff;

int main()
{
    sorting_test(insertion_sort);
    return 0;
}

void insertion_sort(int n, int *A)
{
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (A[j - 1] > A[j]) {
                swap(&A[j - 1], &A[j]);
            } else {
                break;
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
