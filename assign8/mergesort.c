#include <stdio.h>

void merge(int arr[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    // Using a dynamic size to avoid buffer overflow
    int temp[right - left + 1]; 

    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Safer way to calculate mid
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSortNonRecursive(int arr[], int n) {
    int curr_size;
    int left_start;

    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = left_start + curr_size - 1;
            int right_end = (left_start + 2 * curr_size - 1 < n - 1) ? 
                             left_start + 2 * curr_size - 1 : n - 1;

            if (mid < n - 1) {
                merge(arr, left_start, mid, right_end);
            }
        }
    }
}

int main() {
    int arr1[] = {38, 27, 43, 3, 9, 82, 10};
    int n = 7;
    int arr2[] = {38, 27, 43, 3, 9, 82, 10};

    mergeSort(arr1, 0, n - 1);
    mergeSortNonRecursive(arr2, n);

    printf("Recursive Sorted array:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr1[i]); // Fixed variable name
    
    printf("\nNon-Recursive Sorted array:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr2[i]); // Fixed variable name
    printf("\n");

    return 0;
}