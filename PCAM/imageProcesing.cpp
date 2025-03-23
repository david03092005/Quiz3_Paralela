#include <iostream>
#include <vector>
#include <omp.h>
#include <algorithm>

using namespace std;

const int INF = 1e9; // Valor alto para la inicialización

void algorithm(vector<vector<int>>& image){
        int rows = image.size(), cols = image[0].size();
        vector<vector<int>> labels(rows, vector<int>(cols, INF));

        // Se inicializa las etiquetas únicas, para cada píxel 1 recibe como etiqueta un ID = i * cols + j
        // cols es la cantidad de columnas que tiene la matriz.

        for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                        if (image[i][j] == 1) {
                                labels[i][j] = i * cols + j; // Etiqueta única.
                        }
                }
        }

        // En cada iteración, para cada pixel 1 tomara la etiqueta mínima tanto de la propia como la de sus vecinos (izquierda, arriba, derecha, abajo).
        // El proceso termina cuando las etiquetas de cada uno no cambia en dos iteraciones consecutivas.

        bool changed;
        do {
                changed = false;
                #pragma omp parallel for collapse(2) reduction(||:changed)
                for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
                                if (image[i][j] == 1){
                                        int minLabel = labels[i][j];

                                        // Revisar vecinos (izquierda, arriba, derecha, abajo).
                                        if (i > 0 && image[i - 1][j] == 1)
                                                minLabel = min(minLabel, labels[i - 1][j]);
                                        if (j > 0 && image[i][j - 1] == 1)
                                                minLabel = min(minLabel, labels[i][j - 1]);
                                        if (i < rows - 1 && image[i + 1][j] == 1)
                                                minLabel = min(minLabel, labels[i + 1][j]);
                                        if (j < cols - 1 && image[i][j + 1] == 1)
                                                minLabel = min(minLabel, labels[i][j + 1]);

                                        if (minLabel < labels[i][j]) {
                                                labels[i][j] = minLabel;
                                                changed = true;
                                        }
                                }
                        }
                }
        } while (changed);

        // Imprimir resultado.
        cout << "Etiquetas finales:" << endl;
        for (const auto& row : labels) {
                for (int val : row) {
                        if (val == INF) cout << "- ";
                        else cout << val % (rows * cols) << " ";
                }
                cout << endl;
        }
}

int main() {
        // Matriz de pixeles binarios.
        vector<vector<int>> image = {
                {0, 1, 1, 0, 0},
                {1, 1, 0, 0, 1},
                {0, 0, 1, 1, 1},
                {0, 1, 1, 0, 0},
        };

        algorithm(image);
        return 0;
}
