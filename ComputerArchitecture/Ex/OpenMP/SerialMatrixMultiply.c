#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateMatrix(double* matrix, int size) {
    for (int i = 0; i < size * size; i++) {
        matrix[i] = rand() % 10;
    }
}

void multiplyMatrices(double* a, double* b, double* result, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            double sum = 0.0;
            for (int k = 0; k < size; k++) {
                sum += a[row * size + k] * b[k * size + col];
            }
            result[row * size + col] = sum;
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
        generateMatrix(a, size);
        generateMatrix(b, size);
        clock_t start = clock();
        multiplyMatrices(a, b, result, size);
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC; // 计算运行时间
        printf("Done with size %dx%d. Time: %.2f seconds.\n", size, size, time_spent);
        free(a);
        free(b);
        free(result);
    }
    return 0;
}

