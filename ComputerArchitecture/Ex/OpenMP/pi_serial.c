#include <stdio.h>
#include <time.h>

static long num_steps = 100000;
double step;

int main() {
    int i;
    double x, pi, sum = 0.0;
    clock_t start, end;
    double cpu_time_used;
    step = 1.0 / (double)num_steps;
    start = clock();
    for (i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    pi = step * sum;
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Value of Pi = %.16f\n", pi);
    printf("Time taken: %.8f seconds\n", cpu_time_used);

    return 0;
}
