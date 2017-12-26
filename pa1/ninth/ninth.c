#include <stdio.h>
#include <stdlib.h>

struct node{
    int key;
    struct node* left;
    struct node* right;
};
int size = 0;
struct node* root = NULL;

int insert(int key){
    struct node* ptr = root;
    struct node* prev = NULL;
    int c = 0;

    while(ptr != NULL){
        prev = ptr;
        if(ptr->key == key){
            printf("duplicate");
            return -1;
        }
        else if(key < ptr->key){
            ptr = ptr->left;
            c = -1;
        } else{
            ptr = ptr->right;
            c = 1;
        }
    }

    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = key;
    temp->left = NULL;
    temp->right= NULL;

    if(prev == NULL){
        root = temp;
    }
    else if(c<0){
        prev->left = temp;
    } else{
        prev->right = temp;
    }
    size++;

    printf("inserted");
    return 1;
}

void inorderTraversal(struct node* root){
    if(root == NULL){
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->key);
    inorderTraversal(root->right);
}

int findHeight(struct node* tree, int height, int key){
    if(tree == NULL){
        return 0;
    }
    if(key == tree->key){
        return height;
    }
    if(findHeight(tree->left,height++, key) != 0){
        return findHeight(tree->left,height++, key);
    } else {
        return findHeight(tree->right, height++, key);
    }

}

int search(int key){
    struct node* ptr = root;
    //struct node* prev;
    //int c = 0;

    if(root == NULL){
        printf("absent\n");
        return -2;
    }
    else{
        while(ptr != NULL){
            if(ptr->key == key){
                break;
            }
            //prev = ptr;

            if(key< ptr->key){
                ptr = ptr->left;
            } else{
                ptr = ptr->right;
            }
        }

        if(ptr == NULL){
            printf("absent");
            return -1;
        } else{
            printf("present");
            return 1;
        }

    }
}
int delete(int key){
    struct node* ptr = root;
    struct node* prev = NULL;
    //int c = 0;

    if(root == NULL){
        printf("fail");
        return -2;
    }

    while(ptr != NULL){
        if(ptr->key == key){
            break;
        }
        prev = ptr;
        if(key< ptr->key){
            ptr = ptr->left;
        } else{
            ptr = ptr->right;
        }
    }

    if(ptr == NULL){
        printf("fail");
        return -1;
    }
    //two children
    struct node* temp = NULL;
    if(ptr->right!= NULL && ptr->left != NULL){
        temp = ptr->right;
        while(temp->left !=NULL){
            prev = temp;
            temp = temp->left;
        }
        
        ptr->key = temp->key;
        temp = temp->right;
        prev->left = NULL;
        prev->left=temp;
        printf("success");
        return 1;
    }

    if(ptr == root){
        if(ptr->left == NULL){
            root = ptr->right;
        }
        else if(ptr->right == NULL){
            root = ptr->left;
        }
        printf("success");
        return 1;
    }
    //if ptr have one or no children
    struct node* temp2 = NULL;
    if(ptr->right != NULL){
        temp2 = ptr->right;
    } else if(ptr->left !=NULL){
        temp2 = ptr->left;
    }

    if(ptr == prev->left){
        prev->left = temp2;
    } else{
        prev->right = temp2;
    }
    printf("success");
    return 1;

}

int main(int argc, char** argv) {
    /*
    insert(10);
    //inorderTraversal(root);
    insert(11);
    //inorderTraversal(root);
    insert(9);
    inorderTraversal(root);
    printf("\n");
    printf("%d",findHeight(root,1,10));
    */

    char* filename = NULL;
    FILE* fp =NULL;
    char operation;
    int num;
    int searchh;

    filename = argv[1];
    fp = fopen(filename, "r");

    if(fp == NULL){
        printf("error\n");
        //exit(0);
    }
    while(!feof(fp)){
        fscanf(fp, "%c %d\n", &operation, &num);
        //printf("%d ", num);

        if(operation == 'i'){
            searchh = insert(num);
            if(searchh == 1) {
                printf(" %d\n", findHeight(root, 1, num));
            }
            if (searchh == -1){
                printf("\n");
            }
        }
        else if(operation == 's'){
            searchh = search(num);
            if(searchh == 1){
                printf(" %d\n", findHeight(root,1, num));
            }
            if(searchh == -1){
                printf("\n");
            }
        }
        else if(operation == 'd'){
            searchh = delete(num);
                //printf(" %d\n", findHeight(root,1, num));
                printf("\n");
            //inorderTraversal(root);
        }

        //printf("read values : %c\t%d\n", operation, num);
    }
    //inorderTraversal(root);

    return 0;
}
