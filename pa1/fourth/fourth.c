#include <stdio.h>
#include <stdlib.h>

int** process(int** a, int**b, int s, int e) {
    int **matrixr = (int **) malloc(s * sizeof(int *));
    int i, j;
    i = e;
    for (i = 0; i < s; i++) {
        matrixr[i] = (int *) malloc(s * sizeof(int));
    }

    if (e == 1) {
        return a;
    }
    else {

        for (i = 0; i < s; i++) {
            for (j = 0; j < s; j++) {
                matrixr[i][j] = 0;
            }
        }

        int x, y, z;
        for (x = 0; x < s; x++) {
            for (y = 0; y < s; y++) {
                for (z = 0; z < s; z++) {
                    matrixr[x][y] += a[x][z] * b[z][y];
                }
            }
        }

    }

    return process(matrixr, b, s, e-1);
    //return matrixr;
}

void print(int** matrix, int size){
    int i,j;
    for(i = 0; i<size; i++){
        for(j = 0; j<size;j++){
            printf("%d\t",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

int main(int argc, char** argv) {
    //printf("Hello, World!\n");
    int** matrix;
    char* filename;
    FILE* fp;
    int size;
    int i,j;
    int exponent;

    filename = argv[1];

    fp = fopen(filename,"r");

    if(fp ==  NULL){
        exit(0);
    }

    fscanf(fp, "%d \n", &size);

//    while(!feof(fp)){
//        fscanf(fp, "%d %d %d\n", );
//    }
    matrix = (int**)malloc(size* sizeof(int*));

    for(i = 0; i<size;i++){
        matrix[i] = (int*)malloc(size*sizeof(int));
    }


    for(i = 0; i<size; i++){
        for(j = 0; j<size; j++){
            fscanf(fp,"%d", &matrix[i][j]);
        }
        fscanf(fp,"\n");
    }

    fscanf(fp,"%d",&exponent);

    //printf("asda");

    //printing
    //printf("%d\n", size);
/*
    for(i = 0; i<size; i++){
        for(j = 0; j<size;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
*/
    //printf("%d\n\n", exponent);
    //printing done

    //print(matrix,size);

    //exponent = 10;
    matrix = process(matrix,matrix, size, exponent);

    print(matrix,size);

    fclose(fp);

    return 0;
}
