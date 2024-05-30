#include <stdio.h>
#include <omp.h>

int main() {
    int shared_var = 0;

#pragma omp parallel num_threads(4)
    {
        int private_var = 0;

#pragma omp for
        for(int i = 0; i < 10; ++i) {
            private_var++;
#pragma omp atomic
            shared_var++;
        }

        printf("Thread %d, private_var = %d\n", omp_get_thread_num(), private_var);
    }

    printf("shared_var = %d\n", shared_var);
    return 0;
}
