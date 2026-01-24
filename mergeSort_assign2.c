#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/* ---------- MERGE FUNCTION ---------- */
void merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

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

/* ---------- SERIAL ITERATIVE MERGE SORT ---------- */
void serialMergeSort(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));

    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n - 1; left += 2 * size) {
            int mid = left + size - 1;
            if (mid >= n - 1) mid = n - 1;

            int right = left + 2 * size - 1;
            if (right >= n - 1) right = n - 1;

            merge(arr, temp, left, mid, right);
        }
    }

    free(temp);
}

/* ---------- PARALLEL ITERATIVE MERGE SORT ---------- */
void parallelMergeSort(int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));

    for (int size = 1; size < n; size *= 2) {
        #pragma omp parallel for
        for (int left = 0; left < n - 1; left += 2 * size) {
            int mid = left + size - 1;
            if (mid >= n - 1) mid = n - 1;

            int right = left + 2 * size - 1;
            if (right >= n - 1) right = n - 1;

            merge(arr, temp, left, mid, right);
        }
    }

    free(temp);
}

/* ---------- GENERATE RANDOM DATA ---------- */
void generateArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

/* ---------- MAIN ---------- */
int main() {
    int sizes[] = {500, 1000, 10000, 30000, 50000, 70000, 100000};
    int tests = sizeof(sizes) / sizeof(sizes[0]);

    printf("Data Size\tSerial Time (s)\tParallel Time (s)\n");

    for (int i = 0; i < tests; i++) {
        int n = sizes[i];

        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));

        generateArray(arr1, n);
        for (int j = 0; j < n; j++)
            arr2[j] = arr1[j];

        double start, end;

        start = omp_get_wtime();
        serialMergeSort(arr1, n);
        end = omp_get_wtime();
        double serialTime = end - start;

        start = omp_get_wtime();
        parallelMergeSort(arr2, n);
        end = omp_get_wtime();
        double parallelTime = end - start;

        printf("%d\t\t%f\t%f\n", n, serialTime, parallelTime);

        free(arr1);
        free(arr2);
    }

    return 0;
}
