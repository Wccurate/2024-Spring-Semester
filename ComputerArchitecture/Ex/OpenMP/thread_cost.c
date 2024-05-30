#include <stdio.h>
#include <omp.h>

int main() {
#pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();
        if(id < 2) {
            printf("Thread %d finished quickly.\n", id);
        } else {
            for(long i = 0; i < 100000000; ++i) {}
            printf("Thread %d finished later.\n", id);
        }
    }
    return 0;
}
