#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*  MERGE FUNCTION  */
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

/* SERIAL RECURSIVE MERGE SORT */
void serialRecursive(int arr[], int temp[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        serialRecursive(arr, temp, left, mid);
        serialRecursive(arr, temp, mid + 1, right);
        merge(arr, temp, left, mid, right);
    }
}

/*  PARALLEL RECURSIVE MERGE SORT */
void parallelRecursive(int arr[], int temp[], int left, int right, int depth) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        if (depth < 4) { 
            #pragma omp task
            parallelRecursive(arr, temp, left, mid, depth + 1);
            #pragma omp task
            parallelRecursive(arr, temp, mid + 1, right, depth + 1);
            #pragma omp taskwait
        } else {
            serialRecursive(arr, temp, left, mid);
            serialRecursive(arr, temp, mid + 1, right);
        }
        merge(arr, temp, left, mid, right);
    }
}

/* SERIAL ITERATIVE MERGE SORT  */
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

/* PARALLEL ITERATIVE MERGE SORT */
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

/* GENERATE RANDOM DATA */
void generateArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

int main() {
    int sizes[] = {500, 1000, 10000, 30000, 50000};
    int tests = sizeof(sizes) / sizeof(sizes[0]);

    printf("Size\tSerial(I)\tParallel(I)\tSerial(R)\tParallel(R)\n");

    for (int i = 0; i < tests; i++) {
        int n = sizes[i];
        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));
        int *arr3 = (int *)malloc(n * sizeof(int));
        int *arr4 = (int *)malloc(n * sizeof(int));
        int *temp = (int *)malloc(n * sizeof(int));

        generateArray(arr1, n);
        for (int j = 0; j < n; j++) arr4[j] = arr3[j] = arr2[j] = arr1[j];

        double start, end;

        start = omp_get_wtime();
        serialMergeSort(arr1, n);
        double s_iter = omp_get_wtime() - start;

        start = omp_get_wtime();
        parallelMergeSort(arr2, n);
        double p_iter = omp_get_wtime() - start;

        start = omp_get_wtime();
        serialRecursive(arr3, temp, 0, n - 1);
        double s_rec = omp_get_wtime() - start;

        start = omp_get_wtime();
        #pragma omp parallel
        {
            #pragma omp single
            parallelRecursive(arr4, temp, 0, n - 1, 0);
        }
        double p_rec = omp_get_wtime() - start;

        printf("%d\t%f\t%f\t%f\t%f\n", n, s_iter, p_iter, s_rec, p_rec);

        free(arr1); free(arr2); free(arr3); free(arr4); free(temp);
    }
    return 0;
}