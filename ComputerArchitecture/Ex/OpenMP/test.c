#include <stdio.h>
#include <omp.h>

static long num_steps = 99999;
double step;
#define NUM_THREADS 2

int main() {
    int i;
    double x, pi = 0.0, sum[NUM_THREADS];
    int cnt[NUM_THREADS];
    step = 1.0 / (double) num_steps;
    omp_set_num_threads(NUM_THREADS);
    for (i = 0; i < NUM_THREADS; i++) {
        sum[i] = 0.0;
    }
    for (i = 0; i < NUM_THREADS; i++) {
        cnt[i] = 0;
    }

    double start_time = omp_get_wtime();
#pragma omp parallel private(x, i)
    {
        int id = omp_get_thread_num();
#pragma omp for
        for (i = 0; i < num_steps; i++) {
            x = (i + 0.5) * step;
            cnt[id]++;
            sum[id] += 4.0 / (1.0 + x * x);
        }
    }
    for (i = 0, pi = 0.0; i < NUM_THREADS; i++) {
        pi += sum[i] * step;
    }
    double end_time = omp_get_wtime();
    printf("Value of Pi = %.16f\n", pi);
    printf("Time taken: %.8f seconds\n", end_time - start_time);
    printf("Thread1: %d\n",cnt[0]);
    printf("Thread2: %d",cnt[1]);
    return 0;
}
