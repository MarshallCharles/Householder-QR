#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <x86intrin.h>
#include "utils.h"
#include <time.h>

#define MAX_VALUE 20.0

mat matrix_new(int m, int n)
{
	mat x = malloc(sizeof(mat_t));
	x->v = malloc(sizeof(double*) * m);
	x->v[0] = calloc(sizeof(double), m * n);
	for (int i = 0; i < m; i++)
		x->v[i] = x->v[0] + n * i;
	x->m = m;
	x->n = n;
	return x;
}

void matrix_delete(mat m)
{
	free(m->v[0]);
	free(m->v);
	free(m);
}

void matrix_transpose(mat m)
{
	for (int i = 0; i < m->m; i++) {
		for (int j = 0; j < i; j++) {
			double t = m->v[i][j];
			m->v[i][j] = m->v[j][i];
			m->v[j][i] = t;
		}
	}
}

mat matrix_copy(int n, double a[][n], int m)
{
	mat x = matrix_new(m, n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			x->v[i][j] = a[i][j];
	return x;
}

mat matrix_mul(mat x, mat y)
{
	if (x->n != y->m) return 0;
	mat r = matrix_new(x->m, y->n);
	for (int i = 0; i < x->m; i++)
		for (int j = 0; j < y->n; j++)
			for (int k = 0; k < x->n; k++)
				r->v[i][j] += x->v[i][k] * y->v[k][j];
	return r;
}

mat matrix_minor(mat x, int d)
{
	mat m = matrix_new(x->m, x->n);
	/* makes an x->m by x->n matrix called m,
	 * iterates up to d and gives the dth diagonal
	 * value 1 (when d=0 does nothing) */
	for (int i = 0; i < d; i++)
		m->v[i][i] = 1;
	/* Then iterates from d to x->m and x->n
	 and puts the value of the input x into m */
	for (int i = d; i < x->m; i++)
		for (int j = d; j < x->n; j++)
			m->v[i][j] = x->v[i][j];
	return m;
}

/* c = a + b * s */
double *vmadd(double a[], double b[], double s, double c[], int n)
{
	for (int i = 0; i < n; i++)
		c[i] = a[i] + s * b[i];
	return c;
}

/* m = I - v v^T */
mat vmul(double v[], int n)
{
	mat x = matrix_new(n, n);
	// #pragma omp parallel for default(none) shared(x,v) private(i,j)
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			x->v[i][j] = -2 *  v[i] * v[j];
	for (int i = 0; i < n; i++)
		x->v[i][i] += 1;

	return x;
}

/* ||x|| */
double vnorm(double x[], int n)
{
	double sum = 0;
	// #pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < n; i++){
		sum += x[i] * x[i];
	 }
	return sqrt(sum);
}

/* y = x / d */
double* vdiv(double x[], double d, double y[], int n)
{
	// #pragma omp parallel for default(none) shared(y) private(i)
	for (int i = 0; i < n; i++){
		y[i] = x[i] / d;
	 }
	return y;
}

/* take c-th column of m, put in v */
double* mcol(mat m, double *v, int c)
{
	for (int i = 0; i < m->m; i++)
		v[i] = m->v[i][c];
	return v;
}

void matrix_show(mat m)
{
	for(int i = 0; i < m->m; i++) {
		for (int j = 0; j < m->n; j++) {
			printf(" %8.3f", m->v[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void vector_show(double v[], int l)
{
	for(int i = 0; i< l; i++){
		printf("%f\n",v[i]);
	}
}

void printMatrix(int m, int n, int mat[m][n]) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }
}
void fillMatrix(int m, int n, int mat[m][n], int maximum) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++)
    {
      mat[i][j] = rand();
      mat[i][j] %= maximum;
    }
  }
}
void transposeMatrix(int m, int n, int mat1[m][n], int mat2[n][m]){
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      mat2[i][j] = mat1[j][i];
    }
  }
}
void mult_AtA(int m, int n, int mat1[n][m], int mat2[m][n], int mat3[n][n]){
  for(int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      for (int k = 0; k < m; k++){
        mat3[i][j] += mat1[i][k] * mat2[k][j];
      }
    }
  }
}

double drand ( double low, double high )
{
	return ( (double)rand() * ( high - low ) ) / (double)RAND_MAX + low;
}

mat generate_matrix(int m, int n)
{
	mat new = matrix_new(m,n);
	for(int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			new->v[i][j] = drand(1.0, MAX_VALUE);
		}
	}
	return new;
}

double* generate_vector(double v[], int n)
{
	for(int i = 0; i < n; i++)
	{
		v[i] = drand(1.0, MAX_VALUE);
	}
	return v;
}
