#include <stdio.h>
#include <omp.h>

//int main() {
//#pragma omp parallel
//{
//  printf("Hello from thread %d\n", omp_get_thread_num());
//}
//return 0;
//}

//int main() {
//#pragma omp parallel 
//{
//int tid = omp_get_thread_num();
//printf("Hello threads %d\n", tid);
//}
//return 0;
//}

//int main() {
//#pragma omp parallel for
//for (int i = 0; i<5; i++){
//printf("Iteration %d executed by thread %d\n", i, omp_get_thread_num());
//}
//return 0;
//}

int main() {
#pragma omp parallel
{
printf("Hello World from thread %d\n", omp_get_thread_num());
}
return 0;
}

//gcc -fopenmp hpc1.c -o hpc_omp
//./hpc_omp