#include <stdio.h>
#include <stdlib.h>

void magic(int** matrix, int size, int* array){
    //int arraySize = (2*size)+2;
    //int* array = (int*)malloc(size * sizeof(int));
    int x,y;
    int total=0;
    int counter = 0;

    for(x = 0;x<size; x++){
        for(y = 0; y<size;y++){
            total+= matrix[x][y];
        }
        array[counter] = total;
        counter++;
        total = 0;
    }

    for(x = 0;x<size; x++){
        for(y = 0; y<size;y++){
            total+= matrix[y][x];
        }
        array[counter] = total;
        counter++;
        total = 0;
    }

    for(x = 0;x<size; x++){
        total+= matrix[x][x];
    }

    array[counter] = total;
    counter++;
    total = 0;

    for(x = size-1; x > -1;x--){
        total+=matrix[x][x];
    }

    array[counter] = total;
    counter++;
    total = 0;

    //return array;
}

int isMagic(int* array, int size){
    int temp;
    int i,j;
    int boolean = 0;
    int change = 0;

    for(i = 0; i<size;i++){
        temp = array[i];
        for(j = 0; j<size; j++){
        /*
            if(temp == array[j]){
                if(boolean == 0 || boolean == -1){
                    change = 1;
                }
                boolean = 1;
            }
            */
            if(temp !=array[j]){
                if(boolean == 0 || boolean == 1){
                    change = 1;
                }
                boolean = -1;
            }
        }
    }
    return change;
}


void print(int** matrix, int size){
    int i,j;
    for(i = 0; i<size; i++){
        for(j = 0; j<size;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

int main(int argc, char** argv) {
    int** matrix;
    char* filename;
    FILE* fp;
    int size;
    int i,j;
    int* array;


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

    int arraySize = (size*2)+2;;
    array = (int*)malloc(arraySize*sizeof(int));
    magic(matrix, size,array);

    //printing
    //printf("%d\n", size);

    //print(matrix,size);


    magic(matrix,size,array);

//    for(i = 0; i<(size*2) +2;i++){
//        //array[i] = i;
//        printf("%d ", array[i]);
//    }

    if(isMagic(array,size) == 1){
        printf("not-magic\n");
    } else if(isMagic(array,size) == 0 ){
        printf("magic\n");
    }

    fclose(fp);

    return 0;
}
