//main.cpp

#include "hotplate.h"

int main(int argc, char* argv[]){
        if (argc < 3) {
                printf("Uso: %s <maxRow> <maxCol>\n", argv[0]);
                return 1;
        }

        int iter = 0;
        int status1 = 1;
        int status2 = 1;
        int hot_cells = 0;
        double t_start = 0;
        double t_end = 0;
        int maxRow = atoi(argv[1]);
        int maxCol = atoi(argv[2]);

        std::vector<std::vector<float>> mat1(maxRow, std::vector<float>(maxCol));
        std::vector<std::vector<float>> mat2(maxRow, std::vector<float>(maxCol));

        t_start = step();

        initialize(mat1, maxRow, maxCol);
        initialize(mat2, maxRow, maxCol);


        while (true){
                new_values(mat2, mat1, maxRow, maxCol);
                status1 = check_convergence(mat2, maxRow, maxCol);
                iter++;
                if (status1 == 1){
                        break;
                }
                new_values(mat1, mat2, maxRow, maxCol);
                status2 = check_convergence(mat1, maxRow, maxCol);
                iter++;
                if (status2 == 1){
                        break;
                }
        }

        for (int i = 0; i < maxRow; i++){
                for (int j = 0; j < maxCol; j++){
                        if (mat2[i][j] > 50){
                                hot_cells++;
                        }
                }
        }


        t_end = step();

        printf("tiempo de ejecucion: %f\n", t_end - t_start);
}
