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
void transposeMatrix(int m, int n, int mat[m][n], int mat2[n][m]){
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++){
      mat2[i][j] = mat[j][i];
    }
  }
}
