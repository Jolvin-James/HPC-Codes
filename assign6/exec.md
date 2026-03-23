`mpicc -o mpi_process mpi_process.c`

`mpirun -np 4 ./mpi_process`

`scp mpi_process node2://home/computer`

`mpirun -np 6 --hostfile machinefile.txt ./mpi_process`