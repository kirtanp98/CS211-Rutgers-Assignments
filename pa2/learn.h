#ifndef learn_h
#define learn_h

void print(double** matrix, int row, int column);

double** transpose(double** matrix, int row, int column);

double** multiply(double** matrix1, int row1, int col1, double** matrix2, int row2, int col2);

double** inverse(double** matrix, int size);

#endif
