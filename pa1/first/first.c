#include <stdlib.h>
#include <stdio.h>

struct node{
    int value;
    struct node* next;
};

struct node* head = NULL;
int counter = 0;

void insert(int a){
    struct node *temp = (struct node *) malloc(sizeof(struct node));
    struct node *prev = head;
    struct node *curr = head;
    temp->value = a;
    temp->next = head;
    if(head == NULL){
        head = temp;
        counter++;
        return;
    }
    else if (temp->value <= head->value) {
        if(temp->value == head->value){
            return;
        }
        head = temp;
        counter++;
        return;
    }
    while(curr != NULL){
        if(temp->value == curr->value){
            return;
        }
        if(temp->value < curr->value){
            prev->next = temp;
            temp->next = curr;
            counter++;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    prev->next = temp;
    temp->next = NULL;

    counter++;

}

void delete(int a){
    struct node *temp = head;
    struct node *prev = temp;

    //temp->next = head;
    if(head == NULL){
        return;
    } 
    //else if(head->value == a){
    //    head = head->next;
    //    counter--;
    //}
    //else{
         if(head->value == a){
                head = head->next;
                counter--;
                temp = head;
                prev = temp;
        }
        while (temp != NULL) {
            if(temp->value != a){
                prev = temp;
                temp = temp->next;
            }else{
                //break;
                    prev->next = temp->next;
                    temp = temp->next;
                    counter--;
            }
        }
        //if(temp != NULL){
        //    prev->next = temp->next;
        //    counter--;
        //}
    //}
    free(temp);
}

void print(){
    struct node * temp =  head;
    while(temp != NULL){
        printf("%d\t", temp-> value);
        temp = temp->next;
    }
    printf("\n");
}

int main(int argc, char** argv){
    char* filename = NULL;
    FILE* fp =NULL;
    char operation;
    int num;
    
    filename = argv[1];
    //printf("filename entered is %s\n", filename);
    
    fp = fopen(filename, "r");
    
    if(fp == NULL){
        printf("error\n");
        //exit(0);
    }
     while(!feof(fp)){
        fscanf(fp, "%c %d\n", &operation, &num);
        //insert(num);
        
        if(operation == 'i'){
            insert(num);
            //counter++;
        }
        else if(operation == 'd'){
            delete(num);
            //counter--;
        }
        
        //printf("read values : %c\t%d\n", operation, num);
    }
    fclose(fp);
    printf("%d\n", counter);
    print();
    //printf("%d", 10);
    
    return 0;
}
