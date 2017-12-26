#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char** argv) {
    //printf("Hello, World!\n");
    //char* filename;
    //FILE* fp;
    int size;
    int x;
    char* sentence;
    
/*

    filename = argv[1];

    fp = fopen(filename,"r");

    if(fp ==  NULL){
        exit(0);
    }

    //fscanf(fp, "%s", sentence);
    fgets(sentence,100,fp);
    */
    sentence = argv[1];
    
    size = strlen(sentence);
    
    //printf("%s here\n",sentence);
    //printf("%d",argc);
    if(argc>2){
        printf("error\n");
        exit(0);
    }
    
    
    for(x = 0; x<strlen(sentence);x++){
        if(isdigit(sentence[x])){
            printf("error\n");
            exit(0);
        }
    }
    
    
    //printf("here after error\n");

    //starting the process
    //
    char letter[size];
    char temp=' ';
    int counter = 0;
    int letterCounter = 0;
    int letterNum[size];
    int letterNumCounter = 0;

    for(x = 0; x<size+1; x++){
        if(temp != sentence[x]){
            letter[counter] = sentence[x];
            temp = sentence[x];
            counter++;
            letterNum[letterNumCounter] =  letterCounter;
            letterNumCounter++;
            letterCounter = 1;
        } else{
            letterCounter++;
        }
    }
    //letterNum[letterNumCounter] =  letterCounter;

//    printf("\n%s", sentence);
//    printf("\n%s\n", letter);
//    for(x = 1; x<strlen(letter)+1;x++){
//        printf("%d ", letterNum[x]);
//    }

//    for(x = 0; x<strlen(sentence);x++){
//        if(isdigit(sentence[x])|| strchr(sentence,' ') !=NULL){
//            printf("error");
//            exit(0);
//        }
//    }
//
//    size = strlen(letter);
//    printf("\n%d\n",size);

    //int finalSize = strlen(letter)*2;

    //int templ;
    //int i,j;
    //int boolean = 0;
    //int change = 0;
/*
    for(i = 1; i<strlen(letter)+1;i++){
        templ = letterNum[i];
        for(j = 1; j<strlen(letter)+1; j++){
            if(templ == letterNum[j]){
                if(boolean == -1){
                    change = 1;
                }
                boolean = 1;
            }
            else if(templ != letterNum[i]){
                if( boolean == 1){
                    change = 1;
                }
                boolean = -1;
            }
        }
    }
*/
    //printf("%d\n",change);
    int change = 0;
    for(x = 0; x<strlen(letter);x++){
        if(change != 0){
            printf("%c%d", letter[x], letterNum[x + 1]);
        }
        else if(letterNum[x+1]>1) {
            printf("%c%d", letter[x], letterNum[x + 1]);
            change = 1;
        } else{
            printf("%c",letter[x]);
        }
    }
/*
    if(change == 1){
        for(x = 0; x<strlen(letter);x++){
            printf("%c%d", letter[x], letterNum[x + 1]);
        }
    } else{
        for(x = 0; x<strlen(letter);x++) {
            printf("%c", letter[x]);
        }
    }
    */
    //fclose(fp);
    //printf("end\n");

    return 0;
}
