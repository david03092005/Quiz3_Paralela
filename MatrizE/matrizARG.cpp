#include <stdio.h>
#include <random>
#include <iostream>

#define TAM 3

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist(-100, 100);

int number = dist(gen);

int main(int argc, char *argv[]){
        if (argc != 3){
		printf("No se ingreso la cantidad correcta de argumentos (2)");
	}
	else{
		int x = atoi(argv[1]);
		int y = atoi(argv[2]);
		float result[x];
	        float m[x][y];
	
	        float v[y];

		printf("MATRIZ M\n");
		for (int i = 0; i < x; i++){
			for (int j = 0; j < y; j++){
				m[i][j] = dist(gen);
				printf("%f\t", m[i][j]);
			}
			printf("\n");
		}

		printf("Vector v\n");
		for (int b = 0; b < y; b++){
			v[b] = dist(gen);
			printf("%f\t", v[b]);
		}

		printf("\nResultado\n");
        	for (int i = 0; i < x; i++){
                	result[i] = 0;
             	   	for (int j = 0; j < y; j++){
                        	result[i] += (m[i][j] * v[j]);
                	}
                	printf("%f\t", result[i]);
        	}
		printf("\n");
	}

        return 0;
}
