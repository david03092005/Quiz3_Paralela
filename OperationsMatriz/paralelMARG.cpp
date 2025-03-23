#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void generateMatrix(int *matrix, int size);
void printMatrix(int *matrix, int size);
void mSum(int *A, int *B, int *Sum, int size);
void mMul(int *A, int *B, int *Mul, int size);
void mTranspose(int *A, int *TransposeA, int size);

int main(int argc, char *argv[]) {
    int rank, num_procs, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if (argc != 2) {
        if (rank == 0)
            printf("Uso: %s <tamaño de la matriz>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    size = atoi(argv[1]);
    if (size <= 0) {
        if (rank == 0)
            printf("El tamaño de la matriz debe ser mayor que 0.\n");
        MPI_Finalize();
        return 1;
    }

    int *A, *B, *Sum, *Mul, *TransposeA;

    if (rank == 0) {
        // Genera matrices en el proceso 0
        A = (int *)malloc(size * size * sizeof(int));
        B = (int *)malloc(size * size * sizeof(int));
        Sum = (int *)malloc(size * size * sizeof(int));
        Mul = (int *)malloc(size * size * sizeof(int));
        TransposeA = (int *)malloc(size * size * sizeof(int));

        generateMatrix(A, size);
        generateMatrix(B, size);

        printf("Matrix A:\n");
        printMatrix(A, size);
        printf("\nMatrix B:\n");
        printMatrix(B, size);

        // Enviar A y B a los procesos 1 y 2
        MPI_Send(A, size * size, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(B, size * size, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Send(A, size * size, MPI_INT, 2, 0, MPI_COMM_WORLD);
        MPI_Send(B, size * size, MPI_INT, 2, 0, MPI_COMM_WORLD);

        // Enviar solo A al proceso 3
        MPI_Send(A, size * size, MPI_INT, 3, 0, MPI_COMM_WORLD);

        // Recibir los resultados de cada proceso
        MPI_Recv(Sum, size * size, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(Mul, size * size, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(TransposeA, size * size, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Imprimir resultados
        printf("\nMatrix Sum (A + B):\n");
        printMatrix(Sum, size);
        printf("\nMatrix Product (A * B):\n");
        printMatrix(Mul, size);
        printf("\nTranspose of Matrix A:\n");
        printMatrix(TransposeA, size);

        // Liberar memoria
        free(A);
        free(B);
        free(Sum);
        free(Mul);
        free(TransposeA);
    } else if (rank == 1) { 
        // Proceso 1 - Calcula la suma
        A = (int *)malloc(size * size * sizeof(int));
        B = (int *)malloc(size * size * sizeof(int));
        Sum = (int *)malloc(size * size * sizeof(int));

        MPI_Recv(A, size * size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(B, size * size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        mSum(A, B, Sum, size);

        MPI_Send(Sum, size * size, MPI_INT, 0, 0, MPI_COMM_WORLD);

        free(A);
        free(B);
        free(Sum);
    } else if (rank == 2) { 
        // Proceso 2 - Calcula la multiplicación
        A = (int *)malloc(size * size * sizeof(int));
        B = (int *)malloc(size * size * sizeof(int));
        Mul = (int *)malloc(size * size * sizeof(int));

        MPI_Recv(A, size * size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(B, size * size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        mMul(A, B, Mul, size);

        MPI_Send(Mul, size * size, MPI_INT, 0, 0, MPI_COMM_WORLD);

        free(A);
        free(B);
        free(Mul);
    } else if (rank == 3) { 
        // Proceso 3 - Calcula la transposición
        A = (int *)malloc(size * size * sizeof(int));
        TransposeA = (int *)malloc(size * size * sizeof(int));

        MPI_Recv(A, size * size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        mTranspose(A, TransposeA, size);

        MPI_Send(TransposeA, size * size, MPI_INT, 0, 0, MPI_COMM_WORLD);

        free(A);
        free(TransposeA);
    }

    MPI_Finalize();
    return 0;
}

// Generar matriz con valores aleatorios
void generateMatrix(int *matrix, int size) {
    for (int i = 0; i < size * size; i++)
        matrix[i] = rand() % 10;
}

// Imprimir matriz
void printMatrix(int *matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i * size + j]);
        }
        printf("\n");
    }
}

// Suma de matrices
void mSum(int *A, int *B, int *Sum, int size) {
    for (int i = 0; i < size * size; i++)
        Sum[i] = A[i] + B[i];
}

// Multiplicación de matrices
void mMul(int *A, int *B, int *Mul, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Mul[i * size + j] = 0;
            for (int k = 0; k < size; k++)
                Mul[i * size + j] += A[i * size + k] * B[k * size + j];
        }
    }
}

// Transposición de la matriz
void mTranspose(int *A, int *TransposeA, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            TransposeA[j * size + i] = A[i * size + j];
}

