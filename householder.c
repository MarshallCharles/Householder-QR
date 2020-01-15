#include "utils.h"

void householder(mat m, mat *R, mat *Q)
{
	mat q[m->m];
	mat z = m, z1;
	for (int k = 0; k < m->n && k < m->m - 1; k++) {
		double e[m->m], x[m->m], a;
		z1 = matrix_minor(z, k);
		if (z != m) matrix_delete(z);
		z = z1;

		mcol(z, x, k);
		a = vnorm(x, m->m);
		if (m->v[k][k] > 0) a = -a;

		for (int i = 0; i < m->m; i++)
			e[i] = (i == k) ? 1 : 0;

		vmadd(x, e, a, e, m->m);
		vdiv(e, vnorm(e, m->m), e, m->m);
		q[k] = vmul(e, m->m);
		z1 = matrix_mul(q[k], z);
		if (z != m) matrix_delete(z);
		z = z1;
	}
	matrix_delete(z);
	*Q = q[0];
	*R = matrix_mul(q[0], m);
	for (int i = 1; i < m->n && i < m->m - 1; i++) {
		z1 = matrix_mul(q[i], *Q);
		if (i > 1) matrix_delete(*Q);
		*Q = z1;
		matrix_delete(q[i]);
	}
	matrix_delete(q[0]);
	z = matrix_mul(*Q, m);
	matrix_delete(*R);
	*R = z;
	matrix_transpose(*Q);
}

double in[][3] = {
	{ 12, -51,   4},
	{  6, 167, -68},
	{ -4,  24, -41},
	{ -1, 1, 0},
	{ 2, 0, 3},
};

int main()
{
	mat R, Q;
	mat x = matrix_copy(3, in, 5);
	householder(x, &R, &Q);

	puts("Q"); matrix_show(Q);
	puts("R"); matrix_show(R);

	// to show their product is the input matrix
	mat m = matrix_mul(Q, R);
	puts("Q * R"); matrix_show(m);

	matrix_delete(x);
	matrix_delete(R);
	matrix_delete(Q);
	matrix_delete(m);
	return 0;
}
