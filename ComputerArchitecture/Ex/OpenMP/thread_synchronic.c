#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    double no_sync_time, sync_time, start, end;
    long num_steps = 1000000;
    volatile int sum = 0; // 使用volatile防止编译器优化

    // 不使用同步的循环
    start = omp_get_wtime();
#pragma omp parallel for num_threads(4) private(i)
    for(i = 0; i < num_steps; ++i) {
        sum += i;
    }
    end = omp_get_wtime();
    no_sync_time = end - start;

    sum = 0; // 重置sum

    // 使用同步（critical）的循环
    start = omp_get_wtime();
#pragma omp parallel for num_threads(4) private(i)
    for(i = 0; i < num_steps; ++i) {
#pragma omp critical
        sum += i;
    }
    end = omp_get_wtime();
    sync_time = end - start;

    printf("Without synchronization: %.6f seconds\n", no_sync_time);
    printf("With synchronization: %.6f seconds\n", sync_time);
    return 0;
}

