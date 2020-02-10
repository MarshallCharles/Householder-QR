#ifndef UTILS_H
#define UTILS_H

typedef struct {
	int m, n;
	double ** v;
} mat_t, *mat;

mat matrix_new(int m, int n);

void matrix_delete(mat m);

void matrix_transpose(mat m);

mat matrix_copy(int n, double a[][n], int m);

mat matrix_mul(mat x, mat y);

mat matrix_minor(mat x, int d);

double *vmadd(double a[], double b[], double s, double c[], int n);

mat vmul(double v[], int n);

double vnorm(double x[], int n);

double* vdiv(double x[], double d, double y[], int n);

double* mcol(mat m, double *v, int c);

void vector_show(double v[], int l);
void matrix_show(mat m);
void printMatrix(int m, int n, int mat[m][n]);
void fillMatrix(int m, int n, int mat[m][n], int maximum);
void transposeMatrix(int m, int n, int mat1[m][n], int mat2[n][m]);
void mult_AtA(int m, int n, int mat1[n][m], int mat2[m][n], int mat3[n][n]);
void householder(mat m, mat *R, mat *Q);
double drand ( double low, double high );
mat generate_matrix(int m, int n);
double* generate_vector(double v[], int n);
#endif
