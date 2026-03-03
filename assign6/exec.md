mpicc -o a mpi_process.md
mpirun -np 6 ./a

scp a node1://home/computer

mpirun -np 6 --hostfile mpi.txt ./a
