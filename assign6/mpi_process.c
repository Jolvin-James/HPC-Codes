#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int world_rank, world_size, name_len;
    // Buffer for processor name must be at least MPI_MAX_PROCESSOR_NAME
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv); // Initialize
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // Get total processes
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Get rank
    
    // Retrieve processor name
    MPI_Get_processor_name(processor_name, &name_len);

     printf("Hello from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);

    MPI_Finalize(); // Clean up
    return 0;
}
