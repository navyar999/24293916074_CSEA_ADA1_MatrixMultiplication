#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** allocateMatrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void addMatrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}


void matrixmul(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    
    if (n == 2) {
        C[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
        C[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
        C[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
        C[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
        return;
    }
    
    int newSize = n / 2;
    
    int** A11 = allocateMatrix(newSize);
    int** A12 = allocateMatrix(newSize);
    int** A21 = allocateMatrix(newSize);
    int** A22 = allocateMatrix(newSize);
    
    int** B11 = allocateMatrix(newSize);
    int** B12 = allocateMatrix(newSize);
    int** B21 = allocateMatrix(newSize);
    int** B22 = allocateMatrix(newSize);
    
    int** C11 = allocateMatrix(newSize);
    int** C12 = allocateMatrix(newSize);
    int** C21 = allocateMatrix(newSize);
    int** C22 = allocateMatrix(newSize);
    
    int** temp1 = allocateMatrix(newSize);

    
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }
    
    matrixmul(A11, B11, C11, newSize);
    matrixmul(A12, B21, temp1, newSize);
    addMatrix(C11, temp1, C11, newSize);
    
    matrixmul(A11, B12, C12, newSize);
    matrixmul(A12, B22, temp1, newSize);
    addMatrix(C12, temp1, C12, newSize);
    
    matrixmul(A21, B11, C21, newSize);
    matrixmul(A22, B21, temp1, newSize);
    addMatrix(C21, temp1, C21, newSize);
    
    matrixmul(A21, B12, C22, newSize);
    matrixmul(A22, B22, temp1, newSize);
    addMatrix(C22, temp1, C22, newSize);
    
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
    
    freeMatrix(A11, newSize); freeMatrix(A12, newSize);
    freeMatrix(A21, newSize); freeMatrix(A22, newSize);
    freeMatrix(B11, newSize); freeMatrix(B12, newSize);
    freeMatrix(B21, newSize); freeMatrix(B22, newSize);
    freeMatrix(C11, newSize); freeMatrix(C12, newSize);
    freeMatrix(C21, newSize); freeMatrix(C22, newSize);
    freeMatrix(temp1, newSize); 
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int input_sizes[6] = {2, 4, 8, 16, 32, 64};
    
    for(int i = 0; i < 6; i++){
        int n = input_sizes[i];
        
        double total_time = 0;
        int iterations = 1000;
        
        for(int iter = 0; iter < iterations; iter++) {
            int **A = allocateMatrix(n);
            int **B = allocateMatrix(n);
            int **C = allocateMatrix(n);
            
            for (int row = 0; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    A[row][col] = rand() % 100;
                    B[row][col] = rand() % 100;
                    C[row][col] = 0;
                }
            }
            
            clock_t start = clock();
            matrixmul(A, B, C, n);
            clock_t end = clock();
            
            total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
            
            freeMatrix(A, n);
            freeMatrix(B, n);
            freeMatrix(C, n);
        }
        
        printf("Size: %dx%d, Total time: %lf seconds\n", n, n, total_time);
    }
    return 0;
}