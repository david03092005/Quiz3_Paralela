#include <stdio.h>
#include <random>
#include <iostream>
#include <pthread.h>
#include <cstring>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(-100, 100);

int number = dist(gen);

struct MULT {
	float cols[100][100];
	float vect[100];
	int c;
	int r;
};

void *mult(void* argv){
	MULT* data = (MULT*) argv;	
	int x = data->r;
	int y = data->c;
	float result[x];
        for (int i = 0; i < x; i++){
        	result[i] = 0;
                for (int j = 0; j < y; j++){
                	result[i] += (data->cols[i][j] * data->vect[j]);
                }
        printf("%f\t", result[i]);
        }
        printf("\n");
	delete data;
	pthread_exit(NULL);
}


int main(int argc, char *argv[]){
        if (argc != 3){
		printf("No se ingreso la cantidad correcta de argumentos (2)");
	}
	else{
		int x = atoi(argv[1]);
		int y = atoi(argv[2]);
		float result[x];
	        float m[100][100];
	
	        float v[100];

		printf("MATRIZ M\n");
		for (int i = 0; i < x; i++){
			for (int j = 0; j < y; j++){
				m[i][j] = dist(gen);
				printf("%f\t", m[i][j]);
			}
			printf("\n");
		}

		printf("Vector v\n");
		for (int i = 0; i < y; i++){
			v[i] = dist(gen);
			printf("%f\t", v[i]);
		}

		printf("\nResultado\n");
		pthread_t threads[y];

		for (int k = 0; k < x; k++){
			MULT *par = new MULT;
    			par->c = y;
    			par->r = 1;
    			memcpy(par->vect, v, sizeof(float) * y);
    			memcpy(par->cols[0], m[k], sizeof(float) * y);
			pthread_create(&threads[k], NULL, mult, par);
		}

		for (int k = 0; k < x; k++){
			pthread_join(threads[k], NULL);
		}

	}

        return 0;
}
