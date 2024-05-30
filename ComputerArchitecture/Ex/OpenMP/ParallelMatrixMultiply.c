#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void generateMatrix(double* matrix, int size) {
    for (int i = 0; i < size * size; i++) {
        matrix[i] = rand() % 10;
    }
}

void multiplyMatrices(double* a, double* b, double* result, int size) {
    int i,j,k;
#pragma omp parallel for shared(a, b, result) private(i, j, k) schedule(dynamic, 10) num_threads(32)
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            double sum = 0.0;
            for (k = 0; k < size; k++) {
                sum += a[i * size + k] * b[k * size + j];
            }
            result[i * size + j] = sum;
        }
    }
}

int main() {
    srand(time(NULL));

    int sizes[] = {1000, 2000, 3000};
    for (int index = 0; index < 3; index++) {
        int size = sizes[index];
        printf("Generating and multiplying matrices of size %dx%d.\n", size, size);

        double* a = malloc(size * size * sizeof(double));
        double* b = malloc(size * size * sizeof(double));
        double* result = malloc(size * size * sizeof(double));

        if (a == NULL || b == NULL || result == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }

#pragma omp parallel for collapse(2)
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                a[i * size + j] = rand() % 10;
                b[i * size + j] = rand() % 10;
            }
        }
        double start = omp_get_wtime();
        multiplyMatrices(a, b, result, size);
        double end = omp_get_wtime();

        double time_spent = end - start;
        printf("Done with size %dx%d. Time: %.2f seconds.\n", size, size, time_spent);

        free(a);
        free(b);
        free(result);
    }

    return 0;
}
