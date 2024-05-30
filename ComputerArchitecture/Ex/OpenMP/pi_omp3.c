#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
double step;
#define NUM_THREADS 2

int main() {
    int i, id;
    double x, sum, pi = 0.0;
    step = 1.0 / (double) num_steps;
    omp_set_num_threads(NUM_THREADS);
    double start_time = omp_get_wtime();
#pragma omp parallel private(i, id, x, sum)
    {
        id = omp_get_thread_num();
        sum = 0.0;
        for (i = id; i < num_steps; i += NUM_THREADS) {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
#pragma omp critical
        pi += sum * step;
    }
    double end_time = omp_get_wtime();
    printf("Pi = %.16f\n", pi);
    printf("Time taken: %.8f seconds\n", end_time - start_time);
    return 0;
}
