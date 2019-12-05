#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <sys/random.h>

#define M (10)
#define N (12)
#define BLOCK (64)
#define MAX_NUM (9)

int main(int argc, char *argv[]){
  printf("M = %d\nN = %d\n",M, N);
  int A[M][N] = {{0}};
  int A_T[N][M] = {{0}};

  fillMatrix(M,N,A,MAX_NUM);
  printMatrix(M,N,A);
  printf("\n Now transposed \n");
  transposeMatrix(M,N,A,A_T);
  printMatrix(N,M,A_T);
}
