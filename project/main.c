#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <sys/random.h>

#define M_SIZE (3)
#define N_SIZE (4)

void transpose(int A[][N_SIZE], int B[][M_SIZE])
{
    int i, j;
    for (i = 0; i < N_SIZE; i++)
        for (j = 0; j < M_SIZE; j++)
            B[i][j] = A[j][i];

}

int main(int argc, char *argv[]){
  int A[M_SIZE][N_SIZE]
  int B[N_SIZE][M_SIZE], i, j;
  fillMatrix(A,M_SIZE,N_SIZE,10);
  printMatrix(A,M_SIZE,N_SIZE);
  transpose(A,B);
  printMatrix(B,M_SIZE,N_SIZE);
  }
