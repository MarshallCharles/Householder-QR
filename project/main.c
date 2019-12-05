#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <sys/random.h>

#define M (2)
#define N (3)
#define BLOCK (64)
#define MAX_NUM (9)

int main(int argc, char *argv[]){
  printf("M = %d\nN = %d\n",M, N);
  // int A[M][N] = {{0}};
  // int A_T[N][M] = {{0}};
  int A[M][N] = {{1,2,3}, {4,5,6}};
  int B[N][M] = {{0}};
  int C[N][N] = {{0}};

  printf("Matrix\n");
  printMatrix(M,N,A);
  printf("\n Now transposed \n");
  transposeMatrix(M,N,A,B);
  printMatrix(N,M,B);
  printf("\nProduct\n");
  mult_AtA(M,N,B,A,C);
  printMatrix(N,N,C);

}
