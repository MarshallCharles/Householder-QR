#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <sys/random.h>

#define M (2)
#define N (4)
#define BLOCK (64)
#define MAX_NUM (9)

int main(int argc, char *argv[]){
  printf("M = %d\nN = %d\n",M, N);
  // int A[M][N] = {{0}};
  // int A_T[N][M] = {{0}};
  int A[M][N] = { {7,1,4,2}, 
                  {1,9,2,3}};
  int B[N][M] = {{4,2},
                  {1,1},
                  {6,2},
                  {5,5}};
  int C[M][M] = {{0}};
  mult_mxn_nxm(M,N,A,B,C);
  printf("\nANSWER\n");
  printMatrix(M,M,C);
  // fillMatrix(M,N,A,MAX_NUM);
  // printMatrix(M,N,A);
  // printf("\n Now transposed \n");
  // transposeMatrix(M,N,A,A_T);
  // printMatrix(N,M,A_T);
}
