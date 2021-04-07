// gcc binary_search.c -o b

int main()
{
    int x = 4;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("%d", binary_search(x, &arr, 10));
    return 0;
}

int binary_search(int x, int* arr, int len)
{
    int low = 0;
    int high = len - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (x < arr[mid])
        {
            high = mid - 1;
        }
        else if (x > arr[mid])
        {
            low = mid + 1;
        }
        else if (x == arr[mid])
        {
            return mid;
        }
    }
}
