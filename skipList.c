#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LEVEL 5
typedef struct node{
    int data;             // contains the actual key value
    int level;            // contains the current level of the node
    struct node **next;   // array of pointers
}*Node;

typedef struct{
    Node head;       // head pointer
    int maxLevel;    // contains the maximum level for all nodes
}Skiplist;

/**
 * @brief Create a Node object
 * 
 * @param data actual key value
 * @param level_size size of the array of levels
 * @return Node return a pointer to a node
 */
Node createNode(int data, int level_size){
    /* create a new node */
    Node newNode = (Node)calloc(1, sizeof(struct node));

    /* pass the data and level, and create array of pointers */
    newNode->data = data;
    newNode->level = level_size;
    newNode->next = (Node*)calloc(newNode->level, sizeof(Node));

    return newNode;
}

void initializeList(Skiplist *list){
    /* create the first node if the list (negative infinity) */
    list->head = createNode(INT_MIN, list->maxLevel);

    /* create the last node of the list (positive infinity) */
    Node last = createNode(INT_MAX, list->maxLevel);
    /* array of pointers of the head should all point to the last node */
    int x;
    for(x = 0; x < list->head->level; x++){
        list->head->next[x] = last;
    }
}

void main(){
    Skiplist list = { NULL, MAX_LEVEL };

    initializeList(&list);
}