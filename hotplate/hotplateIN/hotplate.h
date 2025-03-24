//hotplate.h
#ifndef _HOTPLATE_H_
#define _HOTPLATE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <vector>
//valores globales


//funciones
void initialize(std::vector<std::vector<float>>& arr, int maxRow, int maxCol);
void new_values(std::vector<std::vector<float>>& arr2, const std::vector<std::vector<float>>& arr1, int maxRow, int maxCol);

int check_convergence(const std::vector<std::vector<float>>& arr, int maxRow, int maxCol);
double step();

#endif //hotplate.h
