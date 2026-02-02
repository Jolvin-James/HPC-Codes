#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void parallelBubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n; i++) {
        // Even phase
        #pragma omp parallel for private(temp)
        for (j = 0; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
        // Odd phase
        #pragma omp parallel for private(temp)
        for (j = 1; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int sizes[] = {500, 1000, 10000, 30000, 50000, 70000, 100000};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);
    
    printf(" %-10s  %-15s  %-15s \n", "Data Size", "Serial (sec)", "Parallel (sec)");

    for (int k = 0; k < num_tests; k++) {
        int n = sizes[k];
        
        int *data_serial = malloc(n * sizeof(int));
        int *data_parallel = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            data_serial[i] = rand() % 100000;
        }
        memcpy(data_parallel, data_serial, n * sizeof(int));

        double start = omp_get_wtime();
        bubbleSort(data_serial, n);
        double end = omp_get_wtime();
        double serial_time = end - start;

        start = omp_get_wtime();
        parallelBubbleSort(data_parallel, n);
        end = omp_get_wtime();
        double parallel_time = end - start;

        // Print Row
        printf(" %-10d  %-15f  %-15f \n", n, serial_time, parallel_time);

        free(data_serial);
        free(data_parallel);
    }
    
    return 0;
}