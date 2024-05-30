#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
double step;
#define NUM_THREADS 2

int main() {
    int i;
    double pi = 0.0;
    step = 1.0 / (double) num_steps;
    omp_set_num_threads(NUM_THREADS);
    double start_time = omp_get_wtime();
#pragma omp parallel
    {
        double x;
        int id = omp_get_thread_num();
        double partial_sum = 0.0;
#pragma omp for
        for (i = 0; i < num_steps; i++) {
            x = (i + 0.5) * step;
            partial_sum += 4.0 / (1.0 + x * x);
        }
#pragma omp critical
        pi += partial_sum * step;
    }

    double end_time = omp_get_wtime();
    printf("Value of Pi = %.16f\n", pi);
    printf("Time taken: %.8f seconds\n", end_time - start_time);
    return 0;
}
