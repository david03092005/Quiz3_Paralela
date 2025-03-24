//hotplateParalelo.cpp
#include "hotplateParalelo.h"


/*
 *initialize
 *
 * @param arr 2D-Matrix
 */
void initialize(std::vector<std::vector<float>>& arr, int maxRow, int maxCol){
        for (int i = 0; i < maxRow; i++){
                for (int j = 0; j < maxCol; j++){
                        if (i == 0 || j == 0 || j == (maxCol - 1)){
                                arr[i][j] = 0;
                        }
                        else if (i == (maxRow - 1)){
                                arr[i][j] = 100;
                        }
                        else if (i == 400 && j < 500){
                                arr[i][j] = 100;
                        }
                        else if (i == 512 && j == 512){
                                arr[i][j] = 100;
                        }
                        else{
                                arr[i][j] = 0;
                        }
                }
        }
}


/*
 *
 */
void new_values(std::vector<std::vector<float>>& arr2, const std::vector<std::vector<float>>& arr1, int maxRow, int maxCol, int startRow, int endRow) {
    for (int i = startRow; i < endRow; i++) {  // Procesar filas asignadas
        for (int j = 1; j < maxCol - 1; j++) {  // Evitamos bordes de j
            if (!(i == 400 && j < 500) && !(i == 512 && j == 512)) {  // Evitar puntos fijos
                arr2[i][j] = (arr1[i][j+1] + arr1[i][j-1] + arr1[i-1][j] + arr1[i+1][j] + (4 * arr1[i][j])) / 8;
            }
        }
    }
}

int check_convergence(const std::vector<std::vector<float>>& arr, int maxRow, int maxCol, int startRow, int endRow) {
        float convergence;
        int converged = 1;
        for (int i = startRow; i < endRow; i++) {
                for (int j = 1; j < maxCol - 1; j++) {
                        if (!(i == 400 && j < 500) && !(i == 512 && j == 512)) {
                                convergence = arr[i][j] - ((arr[i][j-1] + arr[i][j+1] + arr[i+1][j] + arr[i-1][j]) / 4.0f);
                                if (fabs(convergence) >= 0.1) {
                                        converged = 0;
                                }
                        }
                }
        }
        return converged;
}


double step(){
        struct timeval tp;
        gettimeofday(&tp, NULL);
        return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}
