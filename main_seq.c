
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <omp.h>
#include <x86intrin.h>

#define MAX_THREADS omp_get_max_threads()

/* wierd matlab function used in the algorithm*/
mat vec_vec_mult_matlab(double v1[], double v2[], int m1, int m2)
{
    mat v3 = matrix_new(m1, m2);
    for(int i =0; i<m1; i++)
    {
        for(int j=0; j<m2; j++)
        {
            v3->v[i][j] = v1[i]*v2[j];
        }
    }
    return v3;
}


mat mat_minus_mat(mat A, mat B)
{
    if(A->m != B->m || A->n != B->n)
    {
        printf("Dimension error in matrix soustraction\n");
        exit(1);
    }
    mat C = matrix_new(A->m, A->n);
    for(int i =0; i<A->m; i++)
    {
        for(int j=0; j<A->n; j++)
        {
            C->v[i][j] = A->v[i][j] - B->v[i][j];
        }
    }
    return C;
}


double* scalar_mat_vect_mult(mat x, double y[], double scalar, int m, double res[])
{
    if (x->n == m)
    {
        for(int i =0; i<x->m; i++)
        {
            double tmp = 0.0;
            for(int j=0; j<x->n; j++)
            {
                tmp += x->v[i][j] * y[j];
            }
            res[i] = scalar * tmp;
        }
        return res;
    }
    else
    {
        printf("Dimension error in scalar vector matrix multiplication\n");
        printf("%d, %d\n", x->m, m);
        exit(1);
    }
}


double* scalar_vect_mat_mult(mat x, double y[], double scalar, int m, double res[])
{
    if(x->m == m)
    {
        for(int i =0; i<x->n; i++)
        {
            double tmp = 0.0;
            for(int j=0; j<m; j++)
            {
                tmp += y[j]*x->v[j][i];
            }
            res[i] = scalar * tmp;
        }
        return res;
    }
    else
    {
        printf("Dimension error in scalar vector matrix multiplication\n");
        printf("%d, %d\n", x->m, m);
        exit(1);
    }
}


/* take c-th row of m, put in v */
double* mrow(mat m, double *v, int c)
{
	for (int i = 0; i < m->n; i++)
		v[i] = m->v[c][i];
	return v;
}


mat mult_mat_t_mat(mat A)
{
    int m = A->m;
    int n = A->n;
    mat T = matrix_new(m, n);
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
				T->v[i][j] += A->v[k][i] * A->v[k][j];
            }
        }
    }
    return T;
}


mat tril(mat R)
{
    mat U = matrix_new(R->m, R->n);
    for(int i = 0; i < R->m; i++)
    {
        for(int j = 0; j <= i+1 && j<R->n; j++)
        {
            U->v[i][j] = R->v[i][j];
        }
    }
    return U;
}


void svd(mat A, mat *S)
{
    int m = A->m;
    int n = A->n;
    int min = (m < n)? m : n;

    for(int k = 0; k < min; k++)
    {
        double u[m];
        mcol(A, u, k);

        for(int i=0; i<=k-1;i++)
        {
            u[i] = 0.0;
        }

        double sigma = vnorm(u, m);

        if(sigma != 0.0)
        {
            if(u[k] != 0.0)
            {
                sigma = (u[k] < 0.0) ? -1*sigma : sigma;
            }
            u[k] = u[k] + sigma;
            double rho = 1/(sigma*u[k]);
            double v[A->n];
            scalar_vect_mat_mult(A,u,rho,m,v);
            mat uv = vec_vec_mult_matlab(u, v, m, n);
            mat Ai = mat_minus_mat(A, uv);
            *A = *Ai;
            free(Ai);
            free(uv);
            for(int i=k+1; i<m; i++){
                A->v[i][k] = 0.0;
            }
        }


        double u1[n];
        mrow(A, u1, k);

        for(int i=0; i<=k;i++)
        {
            u1[i] = 0.0;
        }
        double sigma1 = vnorm(u1, n);
        if(sigma1 != 0.0)
        {
            if(u1[k+1] != 0.0)
            {
                sigma1 = (u1[k+1] < 0.0) ? -1*sigma1 : sigma1;
            }
            u1[k+1] = u1[k+1] + sigma1;
            double rho = 1/(sigma1*u1[k+1]);
            double v1[A->m];
            scalar_mat_vect_mult(A,u1,rho,n,v1);
            mat vu = vec_vec_mult_matlab(v1, u1, m, n);
            mat Ai = mat_minus_mat(A, vu);
            *A = *Ai;
            free(Ai);
            free(vu);
            for(int i=k+2; i<n; i++){
                A->v[k][i] = 0.0;
            }
        }
    }
    int k = min;
    mat sub_A;
    while(k > 1)
    {
        sub_A = matrix_new(k,k);
        for(int i = 0; i < k; i++)
        {
            for(int j = 0; j < k; j++)
            {
                sub_A->v[i][j] = A->v[i][j];
            }
        }
        if(fabs(sub_A->v[k-2][k-1]) <= 2*2.2204e-6*(fabs(sub_A->v[k-2][k-2]) + fabs(sub_A->v[k-1][k-1])))
        {
            sub_A->v[k-2][k-1] = 0.0;
            k -=1;
        }
        else
        {
            mat T = mult_mat_t_mat(sub_A);

            double r = (T->v[k-1][k-1] - T->v[k-1][k-1])/(2*T->v[k-1][k-2]);
            double s = sqrt(r*r + T->v[k-2][k-1]/T->v[k-1][k-2]);

            s = (r < 0.0) ? -1*s : s;
            s = (r+s != 0.0) ? T->v[k-1][k-1] + T->v[k-2][k-1]/(r+s) : s;
            mat R, Q;
            mat X = matrix_new(k,k);
            for(int i = 0; i < k; i++)
            {
                for(int j = 0; j < k; j++)
                {
                    if(i == j)
                    {
                        X->v[i][j] = T->v[i][j] - s;
                    }
                    else
                    {
                        X->v[i][j] = T->v[i][j];
                    }
                }
            }

            householder(X, &R, &Q);

            mat A_tmp = matrix_mul(sub_A, Q);
            
            mat R1, Q1;
            householder(A_tmp, &R1, &Q1);

            

            mat tmp = tril(R1);

            for(int i = 0; i < k; i++)
            {
                for(int j = 0; j < k; j++)
                {
                    A->v[i][j] = tmp->v[i][j];
                }
            }
            matrix_delete(tmp);
            matrix_delete(Q);
            matrix_delete(R);
            matrix_delete(Q1);
            matrix_delete(R1);
            matrix_delete(A_tmp);
        }
    }
}

int main()
{
    srand ( (unsigned)time ( NULL ) );
  // double v[1000000];
  // generate_vector(v,1000000);
  // double a;
  // a = vnorm(v,1000000);
  // printf("NORM IS %f\n",a);
  //
  // vdiv(v,a, v,1000000);

  // mat Q, R;
  // mat A = generate_matrix(10,10);
  // householder(A,&R,&Q);

    // mat A = matrix_copy(3, x, 5);
    // mat res;
    // svd(A, &res);

    // printf("AMOUNT OF THREADS IS %d", MAX_THREADS);
    mat matrix = generate_matrix(130,130);
    mat res;
    double start = omp_get_wtime();
    svd(matrix, &res);
    double end = omp_get_wtime();
    printf("Time elapsed : %f\n", end-start);


}
