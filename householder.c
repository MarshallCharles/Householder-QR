#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void householder(mat m, mat *R, mat *Q)
{
	/* We have input matrix x (defined below),
	 * as well as empty Q and R which we want to store
	 * decomposition in */
	 /* q is empty of dimensions of m->m, z is input matrix */
	mat q[m->m];
	mat z = m, z1;

	/* Iterate k = 0 to n or m (whichever is smaller) */
	for (int k = 0; k < m->n && k < m->m - 1; k++) {
		//Not sure on these vars yet
		double e[m->m], x[m->m], a;
		printf("==========ITERATION %d==========\n",k);

		/* Matrix minor will make the first k diagonals 1, and
	   Then copy the remaining (m-k)(n-k) values of z to z1
		 (all else is 0) */
		puts("Z"); matrix_show(z);
		z1 = matrix_minor(z, k);
		puts("Z1"); matrix_show(z1);

		//Is this useless?? cause we just redefine z right after
		if (z != m) matrix_delete(z);
		z = z1;

		//Take kth column of z, put in vector x
		mcol(z, x, k);
		//Print X = kth column of Z for iteration k
		puts("Vector X"); vector_show(x, m->m);
		//Get vector norm of x (of dimension m->m)
		a = vnorm(x, m->m);

		/* If the kth diagonal of the input matrix m
		 is positive, then flip sign of a */
		if (m->v[k][k] > 0) a = -a;

		//e just has a 1 in the kth position and resets at each iter
		for (int i = 0; i < m->m; i++)
			e[i] = (i == k) ? 1 : 0;
		//puts("Vector e"); vector_show(e, m->m);


		// Does e = x + e * a (for vecs of size m)
		vmadd(x, e, a, e, m->m);
		// Does e = e/||e||
		vdiv(e, vnorm(e, m->m), e, m->m);
		// Deos q[k] = I - ee^T
		q[k] = vmul(e, m->m);
		//q[k] has the dimensions of our resulting Q
		//And is has the property of Z1 where kth diagonals
		//have 1, and rows 0 to k have all 0
		puts("small q"); matrix_show(q[k]);

		//below are prints to verify the standing of Z and Z1
		// printf("\n\nNOWWWWW\n\n");
		// puts("THIS Z"); matrix_show(z);
		// puts("Z1"); matrix_show(z1);

		//Here Z = Z1, and we multiply q[k] and z
		//We are multiplying a (m*m) by (m*n) => result is m*n
		z1 = matrix_mul(q[k], z);
		if (z != m) matrix_delete(z);
		z = z1;
		puts("FINAL q[k]*Z (carries over to next iteration)"); matrix_show(z);
	}
	printf("\n~~~Done With for Loop~~~\n\n");

	matrix_delete(z);

	*Q = q[0];
	*R = matrix_mul(q[0], m);
	for (int i = 1; i < m->n && i < m->m - 1; i++) {
		//compounding the q[i]'s <=> q[1]*q[2]*...q[min(m,n)]
		z1 = matrix_mul(q[i], *Q);
		//Do we even need this next line...
		if (i > 1) matrix_delete(*Q);
		// Puts z1 result into *Q to keep compounding
		*Q = z1;
		//Throw away old q[i]'s'
		matrix_delete(q[i]);
	}
	matrix_delete(q[0]);
	//Now we have the unitary matrix transposed in *Q
	//This gives us the upper triangular R
	z = matrix_mul(*Q, m);
	matrix_delete(*R);
	*R = z;
	//Transposing just to show result, not actually needed.
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
	/* Define  matrices Q, R, and put the above input matrix
	 * into 'mat x'	*/
	mat R, Q;
	mat x = matrix_copy(3, in, 5);

	/* Householder does all the work now. Give input matrix,
	 * R, and Q empty mats 	*/
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
