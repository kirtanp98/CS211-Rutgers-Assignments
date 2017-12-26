#include <stdio.h>
#include <stdlib.h>

void sort(int* a, int s){
    int b;
    for(b = 1; b<s;b++){
        int insert = a[b];
        int location = b-1;
        
        while(location >= 0){
            if(a[location] > insert){
            (a[location + 1] = a[location]);
            location--;
            }else{
                break;
            }
        }
        a[location + 1] = insert;
    }
}

int main(int argc, char** argv){
    char* filename = NULL;
    FILE* fp = NULL;
    int size = 0;
    int counter = 0;
    int i;
    
    filename = argv[1];
    
    fp = fopen(filename, "r");
    
    if(fp == NULL){
        exit(0);
    }
    
    fscanf(fp, "%d\n", &size);
    //printf("read size : %d\n", size);
    int array[size];
    
    while(!feof(fp) && counter<size){
        fscanf(fp, "%d", &array[counter]);
        //printf("read value: %d \n", array[counter]);
        counter++;
    }
    
    sort(array, size);
    
    for(i = 0; i<size; i++){
        //if(i< size -1){
            printf("%d\t", array[i]);
        //}
        //else{
        //    printf("%d", array[i]);
        //}
    }
    //printf("\n");
    return 0;
}

