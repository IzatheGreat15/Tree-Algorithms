#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX_LEVEL 5
typedef struct node{
    int data;             // contains the actual key value
    int level;            // contains the current level of the node
    struct node **prev;   // array of pointers to previous nodes
    struct node **next;   // array of pointers to next nodes
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
    // newNode->prev = (Node*)calloc(newNode->level, sizeof(Node));
    newNode->next = (Node*)calloc(newNode->level, sizeof(Node));

    return newNode;
}

/**
 * @brief initialize an empty skiplist
 * 
 * @param list 
 */
void initializeList(Skiplist *list){
    /* create the first node if the list (negative infinity) */
    list->head = createNode(INT_MIN, list->maxLevel);

    /* create the last node of the list (positive infinity) */
    Node last = createNode(INT_MAX, list->maxLevel);
    /**
     * next pointers of head => last node
     * prev pointers of last => head
     */
    int x;
    for(x = 0; x < list->head->level; x++){
        list->head->next[x] = last;
        // last->prev[x] = list->head;
    }
}

/**
 * @brief flip a coin
 * 
 * @return int 1 => head; 0 => tail
 */
int coinFlip(){
    return rand() % 2;
}

/**
 * @brief inserting a new node to the skiplist
 * 
 * @param head Head node
 * @param key actual key value to insert
 * @param level optional
 */
void insertNode(Node head, int key, int level){
    Node trav = head;

    // if(level < 0)
    //     return;

    /* traverse to the right level */
    for(level = trav->level - 1; key < trav->next[level]->data && level > 0; level--){
        /* no duplicates */
        if(key == trav->next[level]->data)
            return;

        /* move trav to next checkpoint */
        if(key > trav->next[level - 1]->data)
            trav = trav->next[level - 1];
    }
    // if(key < trav->next[level]->data){
    //     insertNode(trav, key, level - 1);
    // }else if(key > trav->next[level]->data){
    //     insertNode(trav->next[level], key, level);
    // }
    
    /* determine level size of new node using coin flip */
    int level_size = 1, coin;
    do{
        coin = coinFlip();
        level_size += coin;
    }while(coin && level_size < MAX_LEVEL);

    Node newNode = createNode(key, level_size);
    /* insert node */
    int x;
    for(x = 0; x < level_size; x++){
        if(x == trav->level)
            trav = trav->prev[x - 1];

        newNode->next[x] = trav->next[x];
        newNode->prev[x] = newNode->next[x]->prev[x];
        newNode->next[x]->prev[x] = newNode;
        trav->next[x] = newNode;
    }
}

Node searchNode(Node head, int key){
    Node foundNode = NULL;
    

    return foundNode;
}

void main(){
    Skiplist list = { NULL, MAX_LEVEL };

    srand(time(NULL));

    initializeList(&list);
    insertNode(list.head, 56, list.maxLevel - 1);
    insertNode(list.head, 60, list.maxLevel - 1);
}