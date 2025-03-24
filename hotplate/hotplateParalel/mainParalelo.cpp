//mainParalelo.cpp

#include "hotplateParalelo.h"

int main(int argc, char* argv[]) {


    int iter = 0;
    int status1 = 1;
    int status2 = 1;
    int hot_cells = 0;
    double t_start = 0;
    double t_end = 0;
    int maxRow = atoi(argv[1]);
    int maxCol = atoi(argv[2]);

    // Crear matrices dinámicas
    std::vector<std::vector<float>> mat1(maxRow, std::vector<float>(maxCol));
    std::vector<std::vector<float>> mat2(maxRow, std::vector<float>(maxCol));

    t_start = step();

    initialize(mat1, maxRow, maxCol);
    initialize(mat2, maxRow, maxCol);

    // Número de hilos
    int num_threads = omp_get_max_threads();
    int rows_per_thread = maxRow / num_threads;

    while (true) {
        status1 = 1; // Reinicializar los estados de convergencia
        status2 = 1;

        #pragma omp parallel
        {

            int thread_id = omp_get_thread_num();
            int startRow = thread_id * rows_per_thread;
            int endRow = (thread_id == num_threads - 1) ? maxRow : startRow + rows_per_thread;
            // Asegurar que startRow y endRow estén dentro de los límites
            if (startRow < 1) {startRow = 1;}
            if (endRow > maxRow - 1) {endRow = maxRow - 1;}

            new_values(mat2, mat1, maxRow, maxCol, startRow, endRow);

            #pragma omp barrier


            int local_status1 = check_convergence(mat2, maxRow, maxCol, startRow, endRow);


            #pragma omp atomic
            status1 &= local_status1;


            #pragma omp barrier

            new_values(mat1, mat2, maxRow, maxCol, startRow, endRow);


            #pragma omp barrier


            int local_status2 = check_convergence(mat1, maxRow, maxCol, startRow, endRow);


            #pragma omp atomic
            status2 &= local_status2;

        }
        iter++;
        if (status1 == 1 || status2 == 1) {
            printf("a");
            break;
        }
    }


    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            if (mat2[i][j] > 50) {
                hot_cells++;
            }
        }
    }

    t_end = step();

    printf("Tiempo de ejecucion: %f\n", t_end - t_start);
    printf("Celdas calientes: %d\n", hot_cells);


    return 0;
}
