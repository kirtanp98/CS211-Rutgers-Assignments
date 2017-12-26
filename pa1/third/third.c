#include<stdio.h>
#include<stdlib.h>

struct node* hashtable[10000] = {NULL};

struct node{
    int value;
    struct node* next;
};


int hash(int a, int size){
    int result;
    result = a % size;
    if(result < 0){
        result = abs(result);
    }
    return result;
}

char* insert(int a){
    struct node* temp = (struct node*) malloc(sizeof(struct node));
    temp->value = a;
    temp->next = NULL;
    int key = hash(a, 10000);
    char* tracker = "inserted";
   // int boolean = 0;
    
    if(hashtable[key]== NULL){
        hashtable[key] = temp;
        return "inserted";
    }
    else{
        struct node* ptr = hashtable[key];
        struct node* prev = ptr;
        
        while(ptr != NULL){
            prev = ptr;
            ptr = ptr->next;
            if(prev->value == a){
                tracker =  "duplicate";
            }
            //else if(prev->value != a && boolean != 1){
            //    tracker = "inserted";
            //    boolean  = 1;
            //}
        }
        prev->next = temp;
        
        return tracker;     
    }
    return "error in insert";
}

char* search(int a){
    int key = hash(a, 10000);
    if(hashtable[key] == NULL){
        return "absent";
    }
    else{
        struct node* ptr = hashtable[key];
        //struct node* prev = ptr;
        //&& ptr != NULL
        while(ptr->value != a){
            //prev = ptr;
            ptr = ptr->next;
            if(ptr == NULL){
                break;
            }
        }
        if(ptr==NULL){
            return "absent";
        }else if (ptr->value == a){
            return "present";
        }
    }
    return"error in search";
}


int main(int argc, char** argv){
    char* filename = NULL;
    FILE* fp = NULL;
    int number;
    char operation = 'o';
    
    filename = argv[1];
    
    fp = fopen(filename, "r");
    
    if(fp == NULL){
        exit(0);
    }
    
    while(!feof(fp)){
        fscanf(fp, "%c\t%d",&operation, &number);
        if(operation == 'i'){
            printf("%s\n",insert(number));
        }
        else if (operation =='s'){
            printf("%s\n",search(number));
        }
    }
    
    return 0;
}
