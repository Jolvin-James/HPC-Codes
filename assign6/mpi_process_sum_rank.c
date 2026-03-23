#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int rank, size, name_len;
    int global_sum = 0;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    // 1. Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // 2. Get the rank of the current process and total number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // 3. Get the hostname of the physical node running this process
    MPI_Get_processor_name(processor_name, &name_len);

    // 4. Print where each rank is executing
    printf("Hello! I am Rank %d, and I am physically running on node: %s\n", rank, processor_name);

    // (Optional) Wait for all processes to finish printing their names before continuing
    // This just makes the terminal output look much cleaner!
    MPI_Barrier(MPI_COMM_WORLD); 

    // 5. Reduce the local 'rank' value from all processes to 'global_sum' on rank 0
    MPI_Reduce(&rank, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // 6. Only the root process (rank 0) prints the final calculated result
    if (rank == 0) {
        printf("\n--- Final Results ---\n");
        printf("Total number of processes running: %d\n", size);
        printf("The sum of all ranks (0 to %d) is: %d\n", size - 1, global_sum);
    }

    // 7. Finalize the MPI environment
    MPI_Finalize();

    return 0;
}