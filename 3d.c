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
    
    int** A11 = allocate_matrix(newSize);
    int** A12 = allocate_matrix(newSize);
    int** A21 = allocate_matrix(newSize);
    int** A22 = allocate_matrix(newSize);
    
    int** B11 = allocate_matrix(newSize);
    int** B12 = allocate_matrix(newSize);
    int** B21 = allocate_matrix(newSize);
    int** B22 = allocate_matrix(newSize);
    
    int** C11 = allocate_matrix(newSize);
    int** C12 = allocate_matrix(newSize);
    int** C21 = allocate_matrix(newSize);
    int** C22 = allocate_matrix(newSize);
    
    int** temp1 = allocate_matrix(newSize);

    
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
    
    free_matrix(newSize, A11); free_matrix(newSize, A12);
    free_matrix(newSize, A21); free_matrix(newSize, A22);
    free_matrix(newSize, B11); free_matrix(newSize, B12);
    free_matrix(newSize, B21); free_matrix(newSize, B22);
    free_matrix(newSize, C11); free_matrix(newSize, C12);
    free_matrix(newSize, C21); free_matrix(newSize, C22);
    free_matrix(newSize, temp1); 
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void subtract_matrix(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen(int n, int **A, int **B, int **C) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    int new_n = n / 2;
    
    int **A11 = allocate_matrix(new_n);
    int **A12 = allocate_matrix(new_n);
    int **A21 = allocate_matrix(new_n);
    int **A22 = allocate_matrix(new_n);
    int **B11 = allocate_matrix(new_n);
    int **B12 = allocate_matrix(new_n);
    int **B21 = allocate_matrix(new_n);
    int **B22 = allocate_matrix(new_n);
    int **C11 = allocate_matrix(new_n);
    int **C12 = allocate_matrix(new_n);
    int **C21 = allocate_matrix(new_n);
    int **C22 = allocate_matrix(new_n);
    int **P1 = allocate_matrix(new_n);
    int **P2 = allocate_matrix(new_n);
    int **P3 = allocate_matrix(new_n);
    int **P4 = allocate_matrix(new_n);
    int **P5 = allocate_matrix(new_n);
    int **P6 = allocate_matrix(new_n);
    int **P7 = allocate_matrix(new_n);
    int **temp1 = allocate_matrix(new_n);
    int **temp2 = allocate_matrix(new_n);
    
    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + new_n];
            A21[i][j] = A[i + new_n][j];
            A22[i][j] = A[i + new_n][j + new_n];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + new_n];
            B21[i][j] = B[i + new_n][j];
            B22[i][j] = B[i + new_n][j + new_n];
        }
    }
    
    // P1 = A11 * (B12 - B22)
    subtract_matrix(new_n, B12, B22, temp1);
    strassen(new_n, A11, temp1, P1);
    
    // P2 = (A11 + A12) * B22
    addMatrix(A11, A12, temp1, new_n);
    strassen(new_n, temp1, B22, P2);
    
    // P3 = (A21 + A22) * B11
    addMatrix(A21, A22, temp1, new_n);
    strassen(new_n, temp1, B11, P3);
    
    // P4 = A22 * (B21 - B11)
    subtract_matrix(new_n, B21, B11, temp1);
    strassen(new_n, A22, temp1, P4);
    
    // P5 = (A11 + A22) * (B11 + B22)
    addMatrix(A11, A22, temp1, new_n);
    addMatrix(B11, B22, temp2, new_n);
    strassen(new_n, temp1, temp2, P5);
    
    // P6 = (A12 - A22) * (B21 + B22)
    subtract_matrix(new_n, A12, A22, temp1);
    addMatrix(B21, B22, temp2, new_n);
    strassen(new_n, temp1, temp2, P6);
    
    // P7 = (A11 - A21) * (B11 + B12)
    subtract_matrix(new_n, A11, A21, temp1);
    addMatrix(B11, B12, temp2, new_n);
    strassen(new_n, temp1, temp2, P7);
    
    // C11 = P5 + P4 - P2 + P6
    addMatrix(P5, P4, temp1, new_n);
    subtract_matrix(new_n, temp1, P2, temp2);
    addMatrix(temp2, P6, C11, new_n);
    
    // C12 = P1 + P2
    addMatrix(P1, P2, C12, new_n);
    
    // C21 = P3 + P4
    addMatrix(P3, P4, C21, new_n);
    
    // C22 = P5 + P1 - P3 - P7
    addMatrix(P5, P1, temp1, new_n);
    subtract_matrix(new_n, temp1, P3, temp2);
    subtract_matrix(new_n, temp2, P7, C22);
    
    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            C[i][j] = C11[i][j];
            C[i][j + new_n] = C12[i][j];
            C[i + new_n][j] = C21[i][j];
            C[i + new_n][j + new_n] = C22[i][j];
        }
    }
    
    free_matrix(new_n, A11); free_matrix(new_n, A12); free_matrix(new_n, A21); free_matrix(new_n, A22);
    free_matrix(new_n, B11); free_matrix(new_n, B12); free_matrix(new_n, B21); free_matrix(new_n, B22);
    free_matrix(new_n, C11); free_matrix(new_n, C12); free_matrix(new_n, C21); free_matrix(new_n, C22);
    free_matrix(new_n, P1); free_matrix(new_n, P2); free_matrix(new_n, P3); free_matrix(new_n, P4);
    free_matrix(new_n, P5); free_matrix(new_n, P6); free_matrix(new_n, P7);
    free_matrix(new_n, temp1); free_matrix(new_n, temp2);
}


int main(){
    int input_sizes[6] = {2, 4, 8, 16, 32, 64};
    
    // Test standard matrix multiplication
    FILE *fp1 = fopen("standard_results.txt", "w");
    if (fp1 == NULL) {
        printf("Error opening standard results file!\n");
        return 1;
    }
    fprintf(fp1, "size,time\n");
    
    // Test divide and conquer multiplication
    FILE *fp2 = fopen("divideconquer_results.txt", "w");
    if (fp2 == NULL) {
        printf("Error opening divide conquer results file!\n");
        fclose(fp1);
        return 1;
    }
    fprintf(fp2, "size,time\n");
    
    // Test Strassen multiplication
    FILE *fp3 = fopen("strassen_results.txt", "w");
    if (fp3 == NULL) {
        printf("Error opening strassen results file!\n");
        fclose(fp1);
        fclose(fp2);
        return 1;
    }
    fprintf(fp3, "size,time\n");
    
    srand(time(NULL));
    
    for(int i = 0; i < 6; i++){
        int n = input_sizes[i];
        printf("Testing matrix size: %dx%d\n", n, n);
        
        // Test standard matrix multiplication
        double total_time1 = 0;
        int iterations = 1000;
        
        for(int iter = 0; iter < iterations; iter++) {
            int **A = allocate_matrix(n);
            int **B = allocate_matrix(n);
            int **C = allocate_matrix(n);
            
            for (int row = 0; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    A[row][col] = rand() % 100;
                    B[row][col] = rand() % 100;
                }
            }
            
            clock_t start = clock();
            matrix_mul(n, A, B, C);
            clock_t end = clock();
            
            total_time1 += ((double)(end - start)) / CLOCKS_PER_SEC;
            
            free_matrix(n, A);
            free_matrix(n, B);
            free_matrix(n, C);
        }
        
        printf("Standard multiplication - Size: %dx%d, Total time: %lf seconds\n", n, n, total_time1);
        fprintf(fp1, "%d,%lf\n", n, total_time1);
        
        // Test divide and conquer multiplication
        double total_time2 = 0;
        
        for(int iter = 0; iter < iterations; iter++) {
            int **A = allocate_matrix(n);
            int **B = allocate_matrix(n);
            int **C = allocate_matrix(n);
            
            for (int row = 0; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    A[row][col] = rand() % 100;
                    B[row][col] = rand() % 100;
                }
            }
            
            clock_t start = clock();
            matrixmul(A, B, C, n);
            clock_t end = clock();
            
            total_time2 += ((double)(end - start)) / CLOCKS_PER_SEC;
            
            free_matrix(n, A);
            free_matrix(n, B);
            free_matrix(n, C);
        }
        
        printf("Divide & Conquer - Size: %dx%d, Total time: %lf seconds\n", n, n, total_time2);
        fprintf(fp2, "%d,%lf\n", n, total_time2);
        
        // Test Strassen multiplication
        double total_time3 = 0;
        
        for(int iter = 0; iter < iterations; iter++) {
            int **A = allocate_matrix(n);
            int **B = allocate_matrix(n);
            int **C = allocate_matrix(n);
            
            for (int row = 0; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    A[row][col] = rand() % 100;
                    B[row][col] = rand() % 100;
                }
            }
            
            clock_t start = clock();
            strassen(n, A, B, C);
            clock_t end = clock();
            
            total_time3 += ((double)(end - start)) / CLOCKS_PER_SEC;
            
            free_matrix(n, A);
            free_matrix(n, B);
            free_matrix(n, C);
        }
        
        printf("Strassen - Size: %dx%d, Total time: %lf seconds\n", n, n, total_time3);
        fprintf(fp3, "%d,%lf\n", n, total_time3);
        printf("---\n");
    }
    
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    printf("Results saved to standard_results.txt, divideconquer_results.txt, and strassen_results.txt\n");
    return 0;
}