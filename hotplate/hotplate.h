#ifndef __HOTPLATE_H__
#define __HOTPLATE_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>


// constantes
#define MAXROW 256
#define MAXCOL 256


//funciones
void initialize(float arr[MAXROW][MAXCOL]);
void new_values(float arr2[MAXROW][MAXCOL], float arr1[MAXROW][MAXCOL]);
int check_convergence(float arr[MAXROW][MAXCOL]);
double step();


#endif 
