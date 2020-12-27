#include <time.h>
#include <stdlib.h>
#include "sorting_test.h"

typedef struct Pivot {
    int left;
    int right;
} piv;

void quick_sort(int, int*);
void _qsort(int, int, int*);
piv partition(int, int, int*);
void swap(int*, int*);

int buff;

int main()
{
    sorting_test(quick_sort);
    return 0;
}

void quick_sort(int n, int *A)
{
    srand(time(0));
    _qsort(0, n, A);
}

void _qsort(int left, int right, int *A)
{
    if (left < right - 1) {
        piv p = partition(left, right, A);
        _qsort(left, p.left, A);
        _qsort(p.right + 1, right, A);
    }
}

piv partition(int left, int right, int *A)
{
    int rand_i = rand() % (right - left) + left;
    int pivot = A[rand_i];
    piv p;
    p.left = rand_i;
    p.right = rand_i;
    for (int i = left; i < right;) {
        if (A[i] < pivot) {
            if (i < p.left) {
                i++;
            } else if (i > p.left && i < p.right) {
                swap(&A[i], &A[p.left]);
                p.left++;
                i++;
            } else if (i > p.right) {
                swap(&A[p.left], &A[i]);
                p.right++;
                p.left++;
                swap(&A[p.right], &A[i]);
            }
        } else if (A[i] > pivot) {
            if (i < p.left) {
                swap(&A[i], &A[p.right]);
                p.right--;
                p.left--;
                swap(&A[i], &A[p.left]);
            } if (i > p.left && i < p.right) {
                swap(&A[i], &A[p.right]);
                p.right--;
                i++;
            } if (i > p.right) {
                i++;
            }
        } else if (A[i] == pivot) {
            if (i < p.left) {
                p.left--;
                swap(&A[i], &A[p.left]);
            } else if (i >= p.left && i <= p.right) {
                i++;
            } else if (i > p.right) {
                p.right++;
                swap(&A[i], &A[p.right]);
            }
        }
    }
    return p;
}

void swap(int *a, int *b)
{
    buff = *a;
    *a = *b;
    *b = buff;
}

