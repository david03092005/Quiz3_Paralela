#include "hotplate.h"

int main(int argc, char* argv[]){
	int iter = 0;
	int status1 = 1;
	int status2 = 1;
	int hot_cells = 0;
	double t_start = 0;
	double t_end = 0;
	float mat1[MAXROW][MAXCOL];
	float mat2[MAXROW][MAXCOL];

	t_start = step();

	initialize(mat1);
	initialize(mat2);

	while (true){
		new_values(mat2, mat1);
		status1 = check_convergence(mat2);
		iter++;
		if (status1 == 1){
			break;
		}
		new_values(mat1, mat2);
		status2 = check_convergence(mat1);
		iter++;
		if (status2 == 1){
			break;
		}
	}

	for (int i = 0; i < MAXROW; i++){
		for (int j = 0; j < MAXCOL; j++){
			if (mat2[i][j] > 50){
				hot_cells++;	
			}
		}
	}


	t_end = step();

	printf("tiempo de ejecucion: %f\n", t_end - t_start);
}
