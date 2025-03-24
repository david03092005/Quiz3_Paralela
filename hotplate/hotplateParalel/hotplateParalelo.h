//hotplateParalelo.h
#ifndef _HOTPLATEPARALELO_H_
#define _HOTPLATEPARALELO_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <vector>
#include <omp.h>
//valores globales


//funciones
void initialize(std::vector<std::vector<float>>& arr, int maxRow, int maxCol);
void new_values(std::vector<std::vector<float>>& arr2, const std::vector<std::vector<float>>& arr1, int maxRow, int maxCol, int startRow, int endRow);

int check_convergence(const std::vector<std::vector<float>>& arr, int maxRow, int maxCol, int startRow, int endRow);
double step();

#endif //hotplateParalelo.h
