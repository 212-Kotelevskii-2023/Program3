#include <stdio.h>
#include <time.h>
#include "value.hpp"
#include "matrix.hpp"

//функция для подсчета перемен знака в последовательности миноров
int n_(int n, double* a, double lambda)
{
	int signChanges = 0;
	double l = a[0] - lambda;
    double u;

    if (l < 0.0)
        signChanges++;

    // double prevminor = 1;

    // LU-разложение для трёхдиагональной матрицы
    for (int i = 1; i < n; i++)
    {
        // Для L и U вычисляем по формулам для трёхдиагональной матрицы
        u = a[(i - 1) * n + i] / l;
        l = a[i * n + i] - lambda - u * a[i * n + i - 1];
		if(l < 0.0) signChanges++;
    }

    return signChanges;
}

//функция по нахождению собсвтенных значений
clock_t FindValues(int n, double* a, double* values, double eps, int* itsOut, double* x_)
{
	int its;
	int Count;
	double left, right, Left, Right, Mid;

	clock_t t1 = clock();
	Rot3(n, a, x_);
	t1 = clock() - t1;

	//по лемме
	right = norm(a, n) + 1e-10;
	left = -right;

	its = 0;

	int i = 0;
	Left = left;
	Right = right;

	//начинаем поиск
	while (i < n)
    {
		//printf("%d ", i);
		//с помощью бинарного поиска
		while (Right - Left > eps)
        {
			Mid = 0.5 * (Left + Right);

			if (n_(n, a, Mid) < i + 1)
            {
				Left = Mid;
			}
			else
            {
				Right = Mid;
			}
			++its;
		}

		Mid = 0.5 * (Left + Right);
		Count = n_(n, a, Right) - n_(n, a, Left);

		for (int j = 0; j < Count; ++j)
        {
			values[i + j] = Mid;
		}
		i += Count;

		Left = Mid;
		Right = right;
	}

	*itsOut = its;
	return t1;
}
