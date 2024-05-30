#include <omp.h>
#include <stdio.h>

static long num_steps = 99999;
double step;
#define NUM_THREADS 2

int main() {
    int i;
    double x, pi, sum[NUM_THREADS];
    step = 1.0 / (double) num_steps;
    omp_set_num_threads(NUM_THREADS);
    int cnt[NUM_THREADS];
    double start_time = omp_get_wtime(); // 开始计时

#pragma omp parallel private(x, i)
    {
        int id = omp_get_thread_num();
        for (i = (id==1)?0:1, sum[id] = 0.0, cnt[id] = 0; i < num_steps; i = i + NUM_THREADS) {
            cnt[id]++;
            x = (i + 0.5) * step;
            sum[id] += 4.0 / (1.0 + x * x);
        }
    }

    for (i = 0, pi = 0.0; i < NUM_THREADS; i++)
        pi += sum[i] * step;

    double end_time = omp_get_wtime(); // 结束计时

    printf("Pi = %.16f\n", pi);
    printf("Time taken: %.8f seconds\n", end_time - start_time);
    printf("Thread1: %d\n",cnt[0]);
    printf("Thread2: %d",cnt[1]);
    return 0;
}
