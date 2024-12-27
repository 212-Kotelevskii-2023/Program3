#ifndef value_h
#define value_h

#include <stdio.h>
#include <time.h>

int n_(int n, double* a, double lambda);
clock_t FindValues(int n, double* a, double* values, double eps, int* itsOut, double* x_);

#endif
