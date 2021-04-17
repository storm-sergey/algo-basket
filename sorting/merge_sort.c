#include "sorting_test.h"

void merge_sort(int n, int *A);
void sort(int left, int mid, int right, int *A, int *Buff);
void merge(int left, int mid, int right, int *A, int *Buff);

int main()
{
    sorting_test(merge_sort);
    return 0;
}

void merge_sort(int n, int *A)
{
    if (n > 1)
    {
        int left = 0;
        int right = n;
        int mid = (int) right / 2;
        int Buff[n];
        sort(left, mid, right, A, Buff);
    }
}

void sort(int left, int mid, int right, int *A, int *Buff)
{
    if (right - left > 1)
    {
        sort(left, (int)(left + (mid - left) / 2), mid, A, Buff);
        sort(mid, (int)(mid + (right - mid) / 2), right, A, Buff);
        merge(left, mid, right, A, Buff);
    }
}

void merge(int left, int mid, int right, int *A, int *Buff)
{
    int i = left;
    int l = left;
    int m = mid;
    while (l < mid && m < right)
    {
        if (A[l] > A[m])
        {
            Buff[i++] = A[m++];
        }
        else
        {
            Buff[i++] = A[l++];
        }
    }
    while (l < mid)
    {
        Buff[i++] = A[l++];
    }
    while (m < right)
    {
        Buff[i++] = A[m++];
    }
    for (int j = left; j < right; j++)
    {
        A[j] = Buff[j];
    }
}
