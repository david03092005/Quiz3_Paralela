#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateMatrix(int **matrix, int size);
void printMatrix(int **matrix, int size);
void mSum(int **A, int **B, int **Sum, int size);
void mMul(int **A, int **B, int **Mul, int size);
void mTranspose(int **A, int **TransposeA, int size);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <tamaño de la matriz>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    if (size <= 0) {
        printf("El tamaño de la matriz debe ser mayor que 0.\n");
        return 1;
    }

    srand(time(NULL));

    // Reservar memoria para matrices dinámicas
    int **A = (int **)malloc(size * sizeof(int *));
    int **B = (int **)malloc(size * sizeof(int *));
    int **Sum = (int **)malloc(size * sizeof(int *));
    int **Mul = (int **)malloc(size * sizeof(int *));
    int **TransposeA = (int **)malloc(size * sizeof(int *));
    
    for (int i = 0; i < size; i++) {
        A[i] = (int *)malloc(size * sizeof(int));
        B[i] = (int *)malloc(size * sizeof(int));
        Sum[i] = (int *)malloc(size * sizeof(int));
        Mul[i] = (int *)malloc(size * sizeof(int));
        TransposeA[i] = (int *)malloc(size * sizeof(int));
    }

    generateMatrix(A, size);
    generateMatrix(B, size);

    printf("Matrix A:\n");
    printMatrix(A, size);

    printf("\nMatrix B:\n");
    printMatrix(B, size);

    mSum(A, B, Sum, size);
    mMul(A, B, Mul, size);
    mTranspose(A, TransposeA, size);

    printf("\nMatrix Sum (A + B):\n");
    printMatrix(Sum, size);

    printf("\nMatrix Product (A * B):\n");
    printMatrix(Mul, size);

    printf("\nTranspose of Matrix A:\n");
    printMatrix(TransposeA, size);

    // Liberar memoria
    for (int i = 0; i < size; i++) {
        free(A[i]);
        free(B[i]);
        free(Sum[i]);
        free(Mul[i]);
        free(TransposeA[i]);
    }
    free(A);
    free(B);
    free(Sum);
    free(Mul);
    free(TransposeA);

    return 0;
}

void generateMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = rand() % 10;
}

void printMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void mSum(int **A, int **B, int **Sum, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            Sum[i][j] = A[i][j] + B[i][j];
}

void mMul(int **A, int **B, int **Mul, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            Mul[i][j] = 0;
            for (int k = 0; k < size; k++)
                Mul[i][j] += A[i][k] * B[k][j];
        }
}

void mTranspose(int **A, int **TransposeA, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            TransposeA[j][i] = A[i][j];
}

