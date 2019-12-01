void printMatrix(int matrix, int m, int n) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%5d ", matrix[i * n + j]);
    }
    printf("\n");
  }
}

void fillMatrix(int matrix, int m, int n, int max_num) {
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
    {
      matrix[i * size + j] = rand();
      matrix[i * size + j] %= max_num;
    }
}
