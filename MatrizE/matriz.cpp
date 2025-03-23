#include <stdio.h>

#define TAM 3

int main(){
        float result[4];
        float m[4][TAM] = {{1, 4, 0}, {4, 2, 0}, {1, 5, -2}, {-1, 4, -4}};

        float v[TAM] = {-3, 3, 4};

        for (int i = 0; i < 4; i++){
                result[i] = 0;
                for (int j = 0; j < TAM; j++){
                        result[i] += (m[i][j] * v[j]);
                }
                printf("Resultado: %f\n", result[i]);
        }


        return 0;
}
