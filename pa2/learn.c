#include <stdio.h>
#include <stdlib.h>
#include "learn.h"

void print(double** matrix, int row, int column){
    int i,j;
    for(i = 0; i<row; i++){
        for(j = 0; j<column;j++){
            printf("%lf ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

double** transpose(double** matrix, int row, int column){
    double** transpose;
    int i,j;

    transpose = (double**)malloc(column* sizeof(double*));

    for(i = 0; i<column;i++){
        transpose[i] = (double*)malloc(row*sizeof(double));
    }

    for(i = 0; i<row; i++){
        for(j=0;j<column;j++){
            transpose[j][i] = matrix[i][j];
        }
    }
    return transpose;
}
double** multiply(double** matrix1, int row1, int col1, double** matrix2, int row2, int col2){
    if(col1 != row2){
        //printf("Can not multiply, matrix do not have equal col and row");
        return NULL;
    }else{
        //declare matrix
        //printf("arrive\n");
        double** product = (double**)malloc(row1* sizeof(double*));
        int i,j,k;

        for(i = 0; i< row1;i++){
            product[i] = (double*)malloc(col2* sizeof(double));
        }
        //printf("memory\n");
        //end of declaration
        //make all the values of teh matrix 0 so you can add for multiplication
        for(i = 0; i<row1;i++){
            for ( j = 0; j <col2 ; j++) {
                product[i][j] = 0;
            }
        }
        //printf("zero\n");
        for(i = 0; i< row1;i++){
            for(j = 0;j<col2;j++){
                for(k = 0; k< col1;k++){
                    product[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        //printf("return\n");
        return product;
    }

}

double** inverse(double** matrix, int size){
    double** identity;
    int i,j,k;
    double constant;
    double pivot;
    //create id matrix
    identity = (double**)malloc(size* sizeof(double*));

    for(i = 0; i<size;i++){
        identity[i] = (double*)malloc(size*sizeof(double));
    }

    for(i = 0; i<size; i++){
        identity[i][i] = 1;
        for(j = 0; j<size; j++){
            if(j == i){
                continue;
            }
            identity[i][j] = 0;
        }
    }
    //starting algorithm for inverse
    //bottom triangle
    for(i = 0; i<size; i++){
        for(j = i; j<size; j++){
            if(matrix[j][i] != 1 && j==i){
                //checking first colum
                if(matrix[j][i] != 0) {
                    constant = matrix[j][i];
                    for (k = 0; k < size; k++) {
                        matrix[j][k] = matrix[j][k] / constant;
                        identity[j][k] = identity[j][k] / constant;
                    }
                } else{
                    printf("\n something went wrong, there is a 0 in a pivot");
                }
            }
                //now for the zeros below the pivot
            else if(matrix[j][i] != 0 && j!=i){
                pivot = matrix[j][i];
                for(k = 0; k<size; k++){
                    matrix[j][k] = matrix[j][k] - (pivot*matrix[i][k]);
                    identity[j][k] = identity[j][k] - (pivot*identity[i][k]);
                }

            }
        }
    }

    //Top half of the triangle
    for(i=size - 1; i>-1;i--){
        for(j=i;j>-1;j--) {
            if (matrix[j][i] != 1 && i==j) {
                constant = matrix[j][i];
                //for (k = 0; k < size; k++) {
                    matrix[j][i] = matrix[j][i] / constant;
                    identity[j][i] = identity[j][i] / constant;
                //}
            }
            else if(matrix[j][i] != 0 && i!=j){
                constant = matrix[j][i];
                //matrix[j][i] = matrix[j][i] - (constant*matrix[i][i]);
                //identity[j][i] = identity[j][i] - (constant*identity[i][i]);

                //    //subtracting a row multiply with a constant
                for(k = 0; k<size; k++){
                    matrix[j][k] = matrix[j][k] - (matrix[i][k])*constant;
                    identity[j][k] = identity[j][k] - (identity[i][k])*constant;

                }
            }
        }
    }


    return identity;
}

int main(int argc, char** argv){
    double** matrix;
    double** matrix2;
    char* filename;
    FILE* fp;
    FILE* fp2;
    int row,row2;
    int column;
    int i,j;
    
    filename = argv[1];

    fp = fopen(filename,"r");

    if(fp ==  NULL){
        exit(0);
    }
    
    fscanf(fp, "%d \n", &column);
    fscanf(fp, "%d \n", &row);
    column++;
    
    matrix = (double**)malloc(row* sizeof(double*));

    for(i = 0; i<row;i++){
        matrix[i] = (double*)malloc(column*sizeof(double));
    }
    
    for(i = 0; i<row; i++){
        for(j = 0; j<column; j++){
            fscanf(fp,"%lf,", &matrix[i][j]);
        }
        fscanf(fp,"\n");
    }
    fclose(fp);
    //-----------
    filename = argv[2];

    fp2 = fopen(filename,"r");

    if(fp2 ==  NULL){
        exit(0);
    }

    fscanf(fp2, "%d \n", &row2);

    matrix2 = (double**)malloc(row2* sizeof(double*));

    for(i = 0; i<row2;i++){
        matrix2[i] = (double*)malloc((column-1)*sizeof(double));
    }

    for(i = 0; i<row2; i++){
        for(j = 0; j<(column-1); j++){
            fscanf(fp2,"%lf,", &matrix2[i][j]);
        }
        fscanf(fp2,"\n");
    }
    fclose(fp2);
    
    
    
    double** X;
    
    X = (double**)malloc(row* sizeof(double*));

    for(i = 0; i<row;i++){
        X[i] = (double*)malloc(column*sizeof(double));
    }

    for(i = 0; i<row;i++){
        X[i][0] = 1;
        for(j = 1; j<column;j++){
            X[i][j] = matrix[i][j-1];
        }
    }
    
    //print(X,row,column);
    //PRICE OF HOUSE OR Y
    double** Y;
    Y = (double**)malloc(row* sizeof(double*));

    for(i = 0; i<row;i++){
        Y[i] = (double*)malloc(sizeof(double));
    }

    for(i = 0; i<row;i++){
        Y[i][0] = matrix[i][column-1];
    }
    //print(Y,row,1);
    //PLACE HOULDER FOR W
    double** W;
    W = (double**)malloc((column-1)* sizeof(double*));

    for(i = 0; i<(column-1);i++){
        W[i] = (double*)malloc(sizeof(double));
    }

    free(matrix);
    
    double** transposeX = transpose(X,row,column);

    double** Xmulti = multiply(transposeX,column,row,X,row,column);

    double** inverseX = inverse(Xmulti,column);

    double** finalX = multiply(inverseX,column,column,transposeX,column,row);

    double** weights = multiply(finalX,column,row,Y,row,1);

    int temp;
    double total = 0;
    for(i = 0; i<row2;i++){
        for(j=-1;j<(column-1);j++){
            if(j <0){
                total += weights[0][0];
            }
            else{
                total += weights[j+1][0]*matrix2[i][j];
            }
        }
        total+=.5;
        temp = total;
        //printf("%lf, %d \n",total,temp);
        printf("%d\n",temp);
        total = 0;
    }
    
    
    //freeing memory
    free(X);
    free(Y);
    free(W);
    free(transposeX);
    free(Xmulti);
    free(inverseX);
    free(finalX);
    free(weights);
    free(matrix2);
    
    return 0;
}
