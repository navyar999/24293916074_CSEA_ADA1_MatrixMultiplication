#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** allocate_matrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

void free_matrix(int n, int** matrix) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void matrix_mul(int n, int** A, int** B, int** C) {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            C[i][j] = 0;
            for(int k = 0; k < n; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int input_sizes[6] = {2, 4, 8, 16, 32, 64};
    
    for(int i = 0; i < 6; i++){
        int n = input_sizes[i];
        
        double total_time = 0;
        int iterations = 1000;
        
        for(int iter = 0; iter < iterations; iter++) {
            int **A = allocate_matrix(n);
            int **B = allocate_matrix(n);
            int **C = allocate_matrix(n);
            
            for (int row = 0; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    A[row][col] = rand() % 1000;
                    B[row][col] = rand() % 1000;
                }
            }
            
            clock_t start = clock();
            matrix_mul(n, A, B, C);
            clock_t end = clock();
            
            total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
            
            free_matrix(n, A);
            free_matrix(n, B);
            free_matrix(n, C);
        }
        
        printf("Size: %dx%d, Total time: %lf seconds\n", n, n, total_time);
    }
    return 0;
}