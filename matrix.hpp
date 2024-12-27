#ifndef matrix_h
#define matrix_h

#include <stdio.h>

double f(int k, int n, int i, int j);
int enter_matrix(double* a, int n, int k, FILE* fin);
void print_matrix(double* a, int l, int n, int m);
void residual(double* a, double* x, double *norm1, double *norm2, int n);
double norm(double *a, int n);
void Rot3(int n, double* a, double* x_);

#endif
