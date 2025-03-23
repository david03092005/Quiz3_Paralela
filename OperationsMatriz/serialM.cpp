#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 40

void generateMatrix(int matrix[SIZE][SIZE]);
void printMatrix(int matrix[SIZE][SIZE]);
void mSum(int A[SIZE][SIZE], int B[SIZE][SIZE], int Sum[SIZE][SIZE]);
void mMul(int A[SIZE][SIZE], int B[SIZE][SIZE], int Mul[SIZE][SIZE]);
void mTranspose(int A[SIZE][SIZE], int TransposeA[SIZE][SIZE]);

int main() {
    int A[SIZE][SIZE], B[SIZE][SIZE];
    int Sum[SIZE][SIZE], Mul[SIZE][SIZE], TransposeA[SIZE][SIZE];

    srand(time(NULL));

    generateMatrix(A);
    generateMatrix(B);

    printf("Matrix A:\n");
    printMatrix(A);

    printf("\nMatrix B:\n");
    printMatrix(B);

    mSum(A, B, Sum);
    mMul(A, B, Mul);
    mTranspose(A, TransposeA);

    printf("\nMatrix Sum (A + B):\n");
    printMatrix(Sum);

    printf("\nMatrix Product (A * B):\n");
    printMatrix(Mul);

    printf("\nTranspose of Matrix A:\n");
    printMatrix(TransposeA);

    return 0;
}

void generateMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            matrix[i][j] = rand() % 10;
}

void printMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void mSum(int A[SIZE][SIZE], int B[SIZE][SIZE], int Sum[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            Sum[i][j] = A[i][j] + B[i][j];
}

void mMul(int A[SIZE][SIZE], int B[SIZE][SIZE], int Mul[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            Mul[i][j] = 0;
            for (int k = 0; k < SIZE; k++)
                Mul[i][j] += A[i][k] * B[k][j];
        }
}

void mTranspose(int A[SIZE][SIZE], int TransposeA[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            TransposeA[j][i] = A[i][j];
}

