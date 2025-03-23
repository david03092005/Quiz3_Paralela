#include "hotplate.h"


/*
 *initialize
 *
 * @param arr 2D-Matrix
 */
void initialize(float arr[MAXROW][MAXCOL]){
	for (int i = 0; i < MAXROW; i++){
		for (int j = 0; j < MAXCOL; j++){
			if (i == 0 || j == 0 || j == (MAXCOL - 1)){
				arr[i][j] = 0;
			}
			else if (i == (MAXROW - 1)){
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
void new_values(float arr2[MAXROW][MAXCOL], float arr1[MAXROW][MAXCOL]) {
    for (int i = 1; i < MAXROW - 1; i++) {  // Evitamos bordes de i
        for (int j = 1; j < MAXCOL - 1; j++) {  // Evitamos bordes de j
            if (!(i == 400 && j < 500) && !(i == 512 && j == 512)) {  // Evitar puntos fijos
                arr2[i][j] = (arr1[i][j+1] + arr1[i][j-1] + arr1[i-1][j] + arr1[i+1][j] + (4 * arr1[i][j])) / 8;
            }
        }
    }
}

int check_convergence(float arr[MAXROW][MAXCOL]) {
	float convergence;
	int converged = 1;
	for (int i = 1; i < MAXROW - 1; i++) {
		for (int j = 1; j < MAXCOL - 1; j++) {
	       		if (!(i == 400 && j < 500) && !(i == 512 && j == 512)) {
        	    		float convergence = arr[i][j] - ((arr[i][j-1] + arr[i][j+1] + arr[i+1][j] + arr[i-1][j]) / 4);
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
