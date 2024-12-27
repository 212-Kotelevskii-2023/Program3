#include <iostream>
#include <time.h>
#include <math.h>
#include "matrix.hpp"
#include "value.hpp"

int main(int argc, char **argv)
{
    int n, m, k, its;
    double *a;
    double *x;
    double *x_;
    FILE* fin = NULL;
    clock_t t1, t2;
    int flag;
    double eps;
    double norm1, norm2;

    if (argc < 5)
    {
        printf("Некорректный запуск программы. Правильный формат:\n./a.out n m eps k *filename (если k != 0)");
        return -1;
    }

    if (sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &m) != 1
        || sscanf(argv[3], "%lf", &eps) != 1 || sscanf(argv[4], "%d", &k) != 1)
    {
        printf("Данные запуска некорректны.\n");
        return -1;
    }

    if ((k == 0 && argc != 6) || (k != 0 && argc != 5))
    {
        printf("Данные запуска некорректны.\n");
        return -1;
    }

    if (n < 0 || m < 0 || m > n || k < 0 || k > 4 || eps < 1e-16)
    {
        printf("Данные некорректны.\n");
        return -1;
    }

    if (k == 0)
    {
        fin = fopen(argv[5], "r");

        if (!fin)
        {
            printf("Файла не существует.\n");
            fclose(fin);
            return -2;
        }
    }

    a = new double [n*n];
    x = new double [n];
    x_ = new double[n];

    if (!(a && x))
    {
        printf("Недостаточно памяти.\n");

        if (k == 0)
            fclose(fin);

        delete []a;
        delete []x;
        delete []x_;

        return -2;
    }

    flag = enter_matrix(a, n, k, fin);

    if (flag < 0)
    {
        printf("Матрица некорректна.\n");

        if (k == 0)
            fclose(fin);

        delete []a;
        delete []x;
        delete []x_;

        return -2;
    }

    printf("Изначальная матрица:\n");
    print_matrix(a, n, n, m);


    t2 = clock();
    t1 = FindValues(n, a, x, eps, &its, x_);
    t2 = clock() - t2;
    t2 = t2 - t1;

    printf("Собственные значения:\n");
    print_matrix(x, 1, n, m);

    if (k == 0)
        fseek(fin, 0, SEEK_SET);

    flag = enter_matrix(a, n, k, fin);

    residual(a, x, &norm1, &norm2, n);

    printf ("%s : Residual1 = %e Residual2 = %e Iterations = %d \
Iterations1 = %d Elapsed1 = %.2f Elapsed2 = %.2f\n",
            argv[0], norm1, norm2, its, its / n, 1.0*t1/CLOCKS_PER_SEC, 1.0*t2/CLOCKS_PER_SEC);

    if (k == 0)
        fclose(fin);

    delete []a;
    delete []x;
    delete []x_;

    return 0;
}
