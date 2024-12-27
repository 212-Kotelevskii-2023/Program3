#include <math.h>
#include <stdio.h>
#include "matrix.hpp"

using namespace std;

double f(int k, int n, int i, int j)
{
    switch (k)
    {
        case 1:
            return n-fmax(i, j)+1;

        case 2:
            if (i == j)
                return 2;
            if (fabs(fabs(i-j) - 1) < 1e-16)
                return -1;
            return 0;

        case 3:
            if (i == j && i < n-1)
                return 1;
            if (j == n-1)
                return i;
            if (i == n-1)
                return j;
            return 0;

        case 4:
            return 1.0/(i+j+1);

        default:
            return -1;
    }
}

int enter_matrix(double* a, int n, int k, FILE* fin)
{
    int i, j;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if (k == 0)
            {
                if (fscanf(fin, "%lf", &a[i*n+j]) != 1)
                    return -1;
            }
            else
            {
                a[i*n+j] = f(k, n, i, j);
            }
        }
    }

    return 0;
}

void print_matrix(double* a, int l, int n, int m)
{
    int i, j;

    for (i = 0; i < fmin(l, m); ++i)
    {
        for (j = 0; j < m; ++j)
        {
            printf("%10.3e ", a[i*n+j]);
        }
        printf("\n");
    }
}


double norm(double *a, int n)
{
    int i, j;
    double sum;
    double res;

    res = 0.0;
    for (i = 0; i < n; ++i)
    {
        sum = 0.0;
        for (j = 0; j < n; ++j)
            sum += fabs(a[i*n+j]);

        if (res < sum)
            res = sum;
    }

    return res;
}

void residual(double* a, double* x, double *norm1, double *norm2, int n)
{
    int i, j;
    double temp = 0;

    *norm1 = 0.0;
    *norm2 = 0.0;

    for (i = 0; i < n; ++i)
    {
        *norm1 += a[i*n+i] - x[i];
        *norm2 += x[i] * x[i];

        for (j = 0; j < n; ++j)
            temp += a[i*n+j] * a[j*n+i];
    }

    *norm1 = fabs(*norm1) / norm(a, n);
    *norm2 = fabs(sqrt(temp) - sqrt(*norm2)) / norm(a, n);
}

//функция для приведения к трехдиагональному виду
void Rot3(int n, double* a, double* x_) {
    int i, j, k;

    for (i = 0; i < n-2; ++i)
    {
        double s = 0.0;
        for (j = i+2; j < n; ++j)
            s += a[j*n+i] * a[j*n+i];//(12)

        double norm_a1 = sqrt(a[(i+1)*n+i]*a[(i+1)*n+i] + s);//(13)

        if (norm_a1 < 1e-16)
            continue;

        if (s < 1e-16)
            continue;

        x_[i+1] = a[(i+1)*n+i] - norm_a1;

        for (j = i+2; j < n; ++j)
            x_[j] = a[j*n+i]; //(14)

        double norm_x = sqrt(x_[i+1]*x_[i+1] + s);//(15)

        if (norm_x < 1e-16)
            continue;

        for (j = i+1; j < n; ++j)
            x_[j] /= norm_x; //(16)

        for (k = i; k < n; ++k) //лемма 10-11
        {
            double sum = 0.0;
            for (j = i+1; j < n; ++j)
                sum += x_[j] * a[j*n+k];

            sum *= 2.0;
            for (j = i+1; j < n; ++j)
                a[j*n+k] -= sum * x_[j];
        }

        for (k = 0; k < n; ++k) //лемма 10-11
        {
            double sum = 0.0;
            for (j = i+1; j < n; ++j)
                sum += a[k*n+j] * x_[j];

            sum *= 2.0;
            for (j = i+1; j < n; ++j)
                a[k*n+j] -= sum * x_[j];
        }
    } 
}
