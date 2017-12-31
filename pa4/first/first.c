#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int memoryRead = 0;
int memoryWrite = 0;
int cacheHits = 0;
int cacheMiss = 0;
int cacheHitsPre = 0;
int cacheMissPre = 0;

struct node{
    char bit[49];
    struct node* next;
};

struct node* rear = NULL;
struct node* rearPre =NULL;
int size = 0;
int sizePre = 0;
//struct node* last;

int binaryToDecimal(char* binary){
    int length = strlen(binary);
    int value = 0;
    int power = 0;
    int i;
    for(i =length-1; i>-1;i--){
        value += pow(2,power)* (binary[i]-'0');
        power++;
    }
    return value;
}

char* decimalToBinary (int decimal, int length){
    //char binary[5];
    char* binary = malloc(sizeof(char)*length);
    int r = 0;
    int result = 0;
    int counter = length-2;
    while(decimal !=0){
        result = decimal /2;
        r = decimal - (result*2);
        binary[counter] = r + '0';
        decimal = result;
        counter--;
    }

    while(counter >=0){
        binary[counter] = '0';
        counter--;
    }

    binary[length-1] ='\0';
    //printf("%s\n", binary);
    char * ret = binary;
    //free(binary);
    return ret;
}


char* hexToBinary(char * hex){
    char* binary = malloc(sizeof(char)*48);
    int integer = 0;
    int i;
    
    for(i = 0; i<strlen(hex);i++){
        if(isdigit(hex[i])){
            integer = hex[i] - '0';
        }
        else{
            switch(hex[i]){
                case 'a':
                    integer = 10;
                    break;
                case'b':
                    integer = 11;
                    break;
                case'c':
                    integer = 12;
                    break;
                case'd':
                    integer = 13;
                    break;
                case'e':
                    integer = 14;
                    break;
                case'f':
                    integer = 15;
                    break;
                default:
                    integer = -1;
            }
        }
        //snprintf(binary, sizeof(binary),"%s",decimalToBinary(integer));
        strcat(binary, decimalToBinary(integer, 5));
    }

    //binary[47] ='\0';
    return binary;
}

void enqueue(char* bit){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    //temp->bit = bit;
    strcpy(temp->bit, bit);
    //printf("%s\n",temp->bit);

    if(rear == NULL){
        temp->next = temp;
    }
    else{
        temp->next = rear->next;
        rear->next = temp;
    }
    size++;
    rear = temp;
}

void enqueuePre(char* bit){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    //temp->bit = bit;
    strcpy(temp->bit, bit);

    if(rearPre == NULL){
        temp->next = temp;
    }
    else{
        temp->next = rearPre->next;
        rearPre->next = temp;
    }
    sizePre++;
    rearPre = temp;
}

void dequeue(){
    if(rear == NULL){
        //should happened ever
    }
    //char* data = rear->next->bit;
    if(rear == rear->next){
        rear = NULL;
    }
    else{
        rear->next = rear->next->next;
    }

    size--;
}

void dequeuePre(){
    if(rearPre == NULL){
        //should happened ever
    }
    //char* data = rear->next->bit;
    if(rearPre == rearPre->next){
        rearPre = NULL;
    }
    else{
        rearPre->next = rearPre->next->next;
    }

    sizePre--;
}

int search(char* bit){
    if(rear == NULL){
        return -1;
    }
    else if(rear->next == NULL){
        if(strcmp(bit, rear->bit) == 0){
            return 1;
        } else{
            return -1;
        }
    }
    else{
        struct node* ptr = rear->next;
        while(strcmp(bit,ptr->bit) != 0){
            ptr = ptr->next;
            if(ptr == rear){
                break;
            }
        }
        if(ptr == rear && strcmp(bit,rear->bit) == 0){
            return 1;
        }
        if(ptr == rear){
            return -1;
        }
        else if(strcmp(bit,ptr->bit) == 0){
            return 1;
        }
    }
    return -1;
}

int searchPre(char* bit){
    if(rearPre == NULL){
        return -1;
    }
    else if(rearPre->next == NULL){
        if(strcmp(bit, rearPre->bit) == 0){
            return 1;
        } else{
            return -1;
        }
    }
    else{
        struct node* ptr = rearPre->next;
        while(ptr != rearPre && strcmp(bit,ptr->bit) !=0){
            ptr = ptr->next;
        }
        if(ptr == rearPre){
            return -1;
        }
        else if(strcmp(bit,ptr->bit) ==0){
            return 1;
        }
    }
    return -1;
}

int main(int argc, char** argv) {
    char *filename;
    FILE *fp;
    char counter[20];
    char operation[2];
    char address[20];
    //char stop[10];

    filename = argv[5];

    fp = fopen(filename, "r");

    if (fp == NULL) {
        exit(0);
    }

    //Now starting cache if memory hit for direct
    //any Size are in bytes

    int cacheSize= atoi(argv[1]);
    //int cacheSize= 32;
    char* policy = argv[3];
    //char* policy = "assoc:2";
    int blockSize = atoi(argv[4]);
    //int blockSize = 4;
    int numberOfLines= 1;
    int setSize = cacheSize/(blockSize*numberOfLines);

    //in bits
    int blockBits = (int)(log(blockSize)/log(2));
    int setBits = (int)(log(setSize)/log(2));
    int tagBits = 48-(setBits+blockBits);

    //set up array list for direct
    char* cache[setSize];
    int i;
    for(i = 0; i< setSize;i++){
        cache[i] = malloc(48 *sizeof(char));
    }

    char* cachePre[setSize];

    for(i = 0; i< setSize;i++){
        cachePre[i] = malloc(48 *sizeof(char));
    }
//    for(int i =0; i <setSize;i++){
//        cache[i] = "0";
//        cachePre[i] = "0";
//    }
    //set up for set assoitve

    //int index = strchr(policy,':')-policy;
    int digits;
    if(strcmp(policy,"assoc")!=0) {
        digits = strlen(policy) - 6;
    }

    char digitString[digits+1];
    memcpy(digitString, &policy[6],digits);
    digitString[digits] = '\0';
    //printf("%s %d yeet\n", digitString, digits);


    int set = atoi(digitString);
    //printf("%d", set);
    numberOfLines = set;
    if(strcmp(policy,"direct") != 0 && strcmp(policy,"assoc") != 0) {
        setSize = cacheSize / (blockSize * numberOfLines);
    }
    char* setCache[setSize][numberOfLines];
    char* setCachePre[setSize][numberOfLines];
    int j;
    for(i = 0; i<setSize;i++){
        for(j = 0; j<numberOfLines;j++){
            setCache[i][j] = malloc(48 *sizeof(char));;
            setCachePre[i][j] = malloc(48 *sizeof(char));;
        }
    }

    //set assoitive
    int booleanSearch = -1;
    int booleanSearchPre = -1;
    int order[setSize];
    int orderPre[setSize];
    char indexString[5];
    char indexStringPre[5];
//    memcpy( indexString, &zeros[tagBits], setBits );
//    memcpy( indexStringPre, &zerosPre[tagBits], setBits );
//    indexString[setBits] = '\0';
//    indexStringPre[setBits] = '\0';

    for(i = 0; i< setSize;i++){
        order[i]= 0;
        orderPre[i]=0;
    }

    //
    while(!feof(fp)) {
        fscanf(fp, "%s", counter);
        fscanf(fp, "%s", operation);
        fscanf(fp, "%s\n", address);
        if (strcmp(counter, "#eof") == 0 || strcmp(operation, "#eof") == 0 || strcmp(address, "#eof") == 0) {
            break;
        }
        //counter[11]='\0';
        operation[1] = '\0';
        //printf("%d\n",strlen(address));

        if (strcmp(operation, "W") == 0) {
            memoryWrite++;
        } else if (strcmp(operation, "R") == 0) {
            memoryRead++;
        }

        //seperate strings
        char hex[13];
        //char prehex[10];
        //strncpy(hex, address + 2, (strlen(address)-1));
        memcpy(hex, &address[2], strlen(address)-2);
        hex[strlen(hex)] = '\0';
        //printf("%s\n", hex);
        //printf("%d\n", strlen(hex));

        //converts hex to binary
        char *binary;
        binary = hexToBinary(hex);
        binary[4 * strlen(hex)] = '\0';
        //printf("%d\n", strlen(binary));

        //finds how many zeros we need to lead them
        //printf("%s \n", binary);
        int numberOfZeros = 48 - strlen(binary);

        char zeros[49];
        //printf("%d\n",numberOfZeros);
        int i;
        
        for (i = 0; i < numberOfZeros; i++) {
            zeros[i] = '0';
            //printf("%s","1");
        }
        zeros[numberOfZeros] = '\0';

        //printf("%s %d\n", zeros,strlen(zeros));

        //char *result = malloc(strlen(zeros) + strlen(binary) + 1);
        //strcpy(result, zeros);
        strcat(zeros, binary);
        zeros[48] = '\0';

        //printf("%s %d\n", zeros, strlen(zeros));

        char* zerosPre = zeros;
        int valuePre = binaryToDecimal(zeros);
        //printf("%d\n", valuePre);

        valuePre = valuePre+blockSize;
        //printf("%d\n",strlen(zerosPre));
        zerosPre = decimalToBinary(valuePre, strlen(zerosPre)+1);
        //printf("%s\n", zerosPre);


        if(strcmp(policy,"direct") == 0){
            //char counterString[10];
            int booleanSearch = -1;
            int booleanSearchPre = -1;
            int index;
            char indexString[5];
            memcpy( indexString, &zeros[tagBits-1], setBits );
            indexString[setBits] = '\0';

            //printf("%s\n",zeros);
            
            for(i = 0; i<setSize;i++){
                if(strcmp(cache[i],zeros) == 0){
                    //printf(cache[3]);
                    cacheHits++;
                    booleanSearch = 1;
                }

                if(strcmp(cachePre[i],zeros) == 0){
                    cacheHitsPre++;
                    booleanSearchPre = 1;
                }
            }


            if(booleanSearch == -1) {
                cacheMiss++;
                
                index=binaryToDecimal(indexString);
                //index = atoi(indexString);
                //index
                //if (counterNumber < setSize) {
                //cache[index] = zeros;
                strcpy(cache[index], zeros);
                //cachePre[index] = zeros;
                //sprintf(counterString, "%d", counterNumber);
                //cache[index][1] = counterString;
                // counterNumber++;

            }

            if(booleanSearchPre == -1){
                cacheMissPre++;
                memcpy( indexString, &zeros[tagBits-1], setBits );
                indexString[setBits] = '\0';
                
                index=binaryToDecimal(indexString);
                strcpy(cachePre[index], zeros);

                for(i = 0; i<setSize;i++){
                    if(strcmp(cachePre[i],zerosPre) == 0){
                        booleanSearchPre = 1;
                    }
                }
                if(booleanSearch == -1){
                    memcpy( indexString, &zerosPre[tagBits], setBits );
                    indexString[setBits] = '\0';
                    index = binaryToDecimal(indexString);
                    //cachePre[index] = zerosPre;
                    strcpy(cache[index], zerosPre);
                }


            }

        }
        //printf("%d\n", strlen(policy));

        if(strlen(policy) <= 5 && strcmp(policy, "direct") !=0) {
            //checking for hits and miss for assotivity
            if (strcmp(policy, "assoc") == 0) {
                if (size <= setSize) {
                    int check = search(zeros);
                    if (check == -1) {
                        cacheMiss++;
                        enqueue(zeros);
                    } else if (check == 1) {
                        cacheHits++;

                    }


                } else {
                    int check = search(zeros);
                    if (check == -1) {
                        cacheMiss++;
                        dequeue();
                        enqueue(zeros);
                    } else if (check == 1) {
                        cacheHits++;
                    }
                }
                //prefetching
                if(sizePre<=setSize){
                    int checkPre = searchPre(zeros);
                    if(checkPre == -1){
                        cacheMissPre++;
                        enqueuePre(zeros);
                        checkPre = searchPre(zerosPre);
                        if(checkPre == -1){
                            if(sizePre<=setSize) {
                                enqueuePre(zerosPre);
                            }
                            else{
                                dequeuePre();
                                enqueuePre(zerosPre);
                            }
                        }

                    } else if(checkPre == 1){
                        cacheHitsPre++;
                    }

                }
                else{
                    int checkPre = searchPre(zeros);
                    if(checkPre == -1){
                        cacheMissPre++;
                        dequeuePre();
                        enqueuePre(zeros);

                        checkPre = searchPre(zerosPre);
                        if(checkPre == -1){
                            if(sizePre<=setSize) {
                                enqueuePre(zerosPre);
                            }
                            else{
                                dequeuePre();
                                enqueuePre(zerosPre);
                            }
                        }
                    }
                    else if(checkPre == 1){
                        cacheHitsPre++;
                    }
                }
            }
        }

        if(strlen(policy) > 5 && strcmp(policy, "direct") !=0) {
            //printf("%d\n", numberOfLines);
//            int index = strchr(policy,':')-policy;
//            int digits = strlen(policy) - 6;
//
//            char digitString[digits];
//            memcpy(digitString, &policy[6],digits);
//            digitString[digits-1] = '\0';
//
//            int set = atoi(digitString)
//            int booleanSearch = -1;
//            int booleanSearchPre = -1;
//            int order[setSize];
//            int orderPre[setSize];
//            char indexString[5];
//            char indexStringPre[5];
            memcpy( indexString, &zeros[tagBits], setBits );
            memcpy( indexStringPre, &zerosPre[tagBits], setBits );
            indexString[setBits] = '\0';
            indexStringPre[setBits] = '\0';


            for (i = 0; i <setSize ; i++) {
                for (j = 0; j < numberOfLines; j++) {
                    if(booleanSearch == 1){
                        break;
                    }
                    if(strcmp(setCache[i][j],zeros)==0){
                        cacheHits++;
                        booleanSearch = 1;
                        break;
                    }
                }
                if(booleanSearch == 1){
                    break;
                }
            }

            for (i = 0; i <setSize ; i++) {
                for (j = 0; j < numberOfLines; j++) {
                    if(booleanSearchPre == 1){
                        break;
                    }
                    if(strcmp(setCachePre[i][j],zeros)==0){
                        cacheHitsPre++;
                        booleanSearchPre = 1;
                        break;
                    }
                }
                if(booleanSearchPre == 1){
                    break;
                }
            }

//            for(int i = 0; i< setSize;i++){
//                order[i]= 0;
//                orderPre[i]=0;
//            }

            if(booleanSearch == -1){
                //check the order
                //with prefetch
                cacheMiss++;
                cacheMissPre++;
                int index = binaryToDecimal(indexString);
                int indexPre = binaryToDecimal(indexString);
                if(order[index]>numberOfLines){
                    order[index] = 0;
                }
                if(orderPre[indexPre]> numberOfLines){
                    orderPre[indexPre] = 0;
                }
                setCache[index][order[index]] = zeros;
                setCachePre[indexPre][orderPre[indexPre]] = zeros;
                order[index]++;
                orderPre[indexPre]++;
                if(booleanSearchPre == -1){
                    indexPre = binaryToDecimal(indexStringPre);
                    if(orderPre[indexPre]> numberOfLines){
                        orderPre[indexPre] = 0;
                    }
                    setCachePre[indexPre][orderPre[indexPre]] = zerosPre;
                    orderPre[indexPre]++;
                }
            }
            
            //prefetched

//            if (strcmp(policy, "assoc:") == 0) {
//
//            }
        }

    }

    printf("no-prefetch\n");
    printf("memory reads: %d\n", memoryRead);
    printf("memory writes: %d\n", memoryWrite);
    printf("cache-hits: %d\n",cacheHits);
    printf("cache-miss: %d\n",cacheMiss);
    printf("with-prefetch\n");
    printf("memory reads: %d\n", memoryRead);
    printf("memory writes: %d\n", memoryWrite);
    printf("cache-hits: %d\n",cacheHitsPre);
    printf("cache-miss: %d\n",cacheMissPre);

    return 0;
}
