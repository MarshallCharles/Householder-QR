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
