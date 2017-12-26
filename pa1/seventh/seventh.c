#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv){
    //char* sentence;
    int x;
    int size;
    //int counter = 0;
    char result[argc];
    result[argc-1] = '\0';
    
    //printf("%d\n", counter);
    //char result[counter+1];
    
    for(x = 1; x<argc;x++){
        //printf("%s ",argv[x]);
        char* sentence = argv[x];
        size = strlen(sentence);
        result[x-1] = sentence[size-1];
        //printf("%c", sentence[size-1]);  
    }
    //result[counter+1] = '\0';
    
    printf("%s\n", result);
    //printf("\n");
    
    return 0;
}
