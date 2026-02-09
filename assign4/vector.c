#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function Prototypes
void vector_add_serial(double *a, double *b, double *c, int n);
void vector_add_parallel(double *a, double *b, double *c, int n);

int main() {
    int num_threads = 8; 

    omp_set_num_threads(num_threads);

    int sizes[] = {500, 1000, 10000, 30000, 50000, 70000, 100000, 1000000};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);

    printf("Running with %d Threads...\n", num_threads);
    printf("    Data Size           Serial Time          Parallel Time     \n");

    for (int t = 0; t < num_tests; t++) {
        int n = sizes[t];

        // 1. Allocate memory for the current size
        double *A = (double*)malloc(n * sizeof(double));
        double *B = (double*)malloc(n * sizeof(double));
        double *C = (double*)malloc(n * sizeof(double));

        if (A == NULL || B == NULL || C == NULL) {
            printf("Memory allocation failed for size %d\n", n);
            return 1;
        }

        // 2. Initialize vectors (not timed)
        for (int i = 0; i < n; i++) {
            A[i] = i * 1.0;
            B[i] = i * 2.0;
        }

        double start_time, end_time;
        double serial_duration, parallel_duration;

        // --- SERIAL RUN ---
        start_time = omp_get_wtime();
        vector_add_serial(A, B, C, n);
        end_time = omp_get_wtime();
        serial_duration = end_time - start_time;

        // --- PARALLEL RUN ---
        start_time = omp_get_wtime();
        vector_add_parallel(A, B, C, n);
        end_time = omp_get_wtime();
        parallel_duration = end_time - start_time;

        printf("%15d %20f %20f \n", 
               n, serial_duration, parallel_duration);

        free(A);
        free(B);
        free(C);
    }

    return 0;
}

// --- Serial Implementation ---
void vector_add_serial(double *a, double *b, double *c, int n) {
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

// --- Parallel Implementation ---
void vector_add_parallel(double *a, double *b, double *c, int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}