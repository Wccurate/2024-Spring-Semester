#include <stdio.h>
#include <omp.h>

int main() {
    double start_time = omp_get_wtime();

#pragma omp parallel num_threads(4)
    {

    }
    double time_taken = omp_get_wtime() - start_time;
    printf("Time taken for empty parallel region: %.8f seconds\n", time_taken);
    return 0;
}
