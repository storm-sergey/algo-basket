#include "sorting_test.h"

void selection_sort(int, int*);
void swap(int*, int*);

int buff;

int main()
{
    sorting_test(selection_sort);
    return 0;
}

void selection_sort(int n, int *A)
{
    int min;
    for (int i = 0; i < n - 1; i++) {
        min = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[min]) {
                min = j;
            }
        }
        swap(&A[i], &A[min]);
    }
}

void swap(int *a, int *b)
{
    buff = *a;
    *a = *b;
    *b = buff;
}
