#include <stdio.h>
#include <stdlib.h>

#define KEY 3
#define ORDER KEY + 1

typedef struct node{
    int keys[KEY];
    struct node *children[ORDER];
    int keyCount;
}*PAGE;

void initializeNode(PAGE *A){
    *A = NULL; 
}

void createNode(PAGE *A){
    *A = (PAGE)calloc(1, sizeof(struct node));
}

void shiftAndInsert(int *A, int max, int key){
    int x;
    for(x = max - 1; x >= 0 && A[x] > key; x--){
        A[x + 1] = A[x];
    }
    A[x + 1] = key;
}

void insertKey(PAGE *root, int key){
    if(*root == NULL){
        createNode(root);
    }
    // }else{
    //     int child;
    //     for(child = 0; child < KEY && key > (*root)->keys[child]; child++){}
    //     insertKey(&(*root)->children[child], key);
    // }

    
}

void main(){
    PAGE root; 
    initializeNode(&root);
    insertKey(&root, 5);
}