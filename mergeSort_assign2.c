#include <stdio.h>
#include <omp.h>

/* ---------- COMMON MERGE FUNCTION ---------- */
void merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (int x = left; x <= right; x++)
        arr[x] = temp[x];
}

/* ---------- RECURSIVE MERGE SORT ---------- */
void recursiveMergeSort(int arr[], int temp[], int left, int right) {
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    recursiveMergeSort(arr, temp, left, mid);
    recursiveMergeSort(arr, temp, mid + 1, right);

    merge(arr, temp, left, mid, right);
}

/* ---------- NON RECURSIVE (ITERATIVE) MERGE SORT ---------- */
void iterativeMergeSort(int arr[], int n) {
    int temp[n];

    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n - 1; left += 2 * size) {
            int mid = left + size - 1;
            if (mid >= n - 1)
                mid = n - 1;

            int right = left + 2 * size - 1;
            if (right >= n - 1)
                right = n - 1;

            merge(arr, temp, left, mid, right);
        }
    }
}

/* ---------- PRINT FUNCTION ---------- */
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/* ---------- MAIN ---------- */
int main() {
    int arr1[] = {38, 27, 43, 3, 9, 82, 10};
    int arr2[] = {38, 27, 43, 3, 9, 82, 10};

    int n = sizeof(arr1) / sizeof(arr1[0]);
    int temp[n];

    printf("Original Array:\n");
    printArray(arr1, n);

    double start = omp_get_wtime();
    recursiveMergeSort(arr1, temp, 0, n - 1);
    double end = omp_get_wtime();

    printf("\nAfter Recursive Merge Sort:\n");
    printArray(arr1, n);
    printf("Recursive Merge Sort Time: %f seconds\n", end - start);

    start = omp_get_wtime();
    iterativeMergeSort(arr2, n);
    end = omp_get_wtime();

    printf("\nAfter Non Recursive Merge Sort:\n");
    printArray(arr2, n);
    printf("Non Recursive Merge Sort Time: %f seconds\n", end - start);

    return 0;
}
