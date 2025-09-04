#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int **allocate_matrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }
    return matrix;
}

void free_matrix(int n, int **matrix) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(int n, int **matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrix(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
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
    add_matrix(new_n, A11, A12, temp1);
    strassen(new_n, temp1, B22, P2);
    
    // P3 = (A21 + A22) * B11
    add_matrix(new_n, A21, A22, temp1);
    strassen(new_n, temp1, B11, P3);
    
    // P4 = A22 * (B21 - B11)
    subtract_matrix(new_n, B21, B11, temp1);
    strassen(new_n, A22, temp1, P4);
    
    // P5 = (A11 + A22) * (B11 + B22)
    add_matrix(new_n, A11, A22, temp1);
    add_matrix(new_n, B11, B22, temp2);
    strassen(new_n, temp1, temp2, P5);
    
    // P6 = (A12 - A22) * (B21 + B22)
    subtract_matrix(new_n, A12, A22, temp1);
    add_matrix(new_n, B21, B22, temp2);
    strassen(new_n, temp1, temp2, P6);
    
    // P7 = (A11 - A21) * (B11 + B12)
    subtract_matrix(new_n, A11, A21, temp1);
    add_matrix(new_n, B11, B12, temp2);
    strassen(new_n, temp1, temp2, P7);
    
    // C11 = P5 + P4 - P2 + P6
    add_matrix(new_n, P5, P4, temp1);
    subtract_matrix(new_n, temp1, P2, temp2);
    add_matrix(new_n, temp2, P6, C11);
    
    // C12 = P1 + P2
    add_matrix(new_n, P1, P2, C12);
    
    // C21 = P3 + P4
    add_matrix(new_n, P3, P4, C21);
    
    // C22 = P5 + P1 - P3 - P7
    add_matrix(new_n, P5, P1, temp1);
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
                  A[row][col] = rand() % 100;
                  B[row][col] = rand() % 100;
              }
          }
          
          clock_t start = clock();
          strassen(n, A, B, C);
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
