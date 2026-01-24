#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define THRESHOLD 1000   // cutoff to avoid too many tasks

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

/* ---------- SERIAL RECURSIVE MERGE SORT ---------- */
void serialMergeSort(int arr[], int temp[], int left, int right) {
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    serialMergeSort(arr, temp, left, mid);
    serialMergeSort(arr, temp, mid + 1, right);
    merge(arr, temp, left, mid, right);
}

/* ---------- PARALLEL MERGE SORT ---------- */
void parallelMergeSort(int arr[], int temp[], int left, int right) {
    if (left >= right)
        return;

    if (right - left < THRESHOLD) {
        serialMergeSort(arr, temp, left, right);
        return;
    }

    int mid = (left + right) / 2;

    #pragma omp task shared(arr, temp)
    parallelMergeSort(arr, temp, left, mid);

    #pragma omp task shared(arr, temp)
    parallelMergeSort(arr, temp, mid + 1, right);

    #pragma omp taskwait
    merge(arr, temp, left, mid, right);
}

/* ---------- GENERATE RANDOM ARRAY ---------- */
void generateArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

/* ---------- MAIN ---------- */
int main() {
    int sizes[] = {500, 1000, 10000, 30000, 50000, 70000, 100000};
    int numTests = sizeof(sizes) / sizeof(sizes[0]);

    printf("\n-----------------------------------------------------------\n");
    printf("Data Size\tSerial Time (s)\tParallel Time (s)\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < numTests; i++) {
        int n = sizes[i];

        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));
        int *temp = (int *)malloc(n * sizeof(int));

        generateArray(arr1, n);

        for (int j = 0; j < n; j++)
            arr2[j] = arr1[j];

        double start, end;

        /* Serial timing */
        start = omp_get_wtime();
        serialMergeSort(arr1, temp, 0, n - 1);
        end = omp_get_wtime();
        double serialTime = end - start;

        /* Parallel timing */
        start = omp_get_wtime();
        #pragma omp parallel
        {
            #pragma omp single
            parallelMergeSort(arr2, temp, 0, n - 1);
        }
        end = omp_get_wtime();
        double parallelTime = end - start;

        printf("%d\t\t%f\t%f\n", n, serialTime, parallelTime);

        free(arr1);
        free(arr2);
        free(temp);
    }

    printf("-----------------------------------------------------------\n");
    return 0;
}
