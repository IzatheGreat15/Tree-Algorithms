#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_LEVEL 5

typedef struct node{
    int data, level;
    struct node **next;
}*Node;

typedef struct{
    Node head;
    int max_level;
}Skiplist;

Node createNewNode(int data, int level_size){
    Node newNode = (Node)calloc(1, sizeof(struct node));

    newNode->data = data;
    newNode->level = level_size;
    newNode->next = NULL;
    if(level_size > 0)
        newNode->next = (Node*)calloc(level_size, sizeof(Node));

    return newNode;
}

void initList(Skiplist *L){
    /* create the first node of the list (-INF) */
    L->head = createNewNode(INT_MIN, L->max_level);

    /* create the last node of the list (+INF) */
    Node temp =  createNewNode(INT_MAX, 0);

    /* point all pointers of the first node to the last node */
    for(int x = 0; x < L->head->level; x++){
        L->head->next[x] = temp;
    }
}

int coinFlip(){
    return rand() % 2;
}

// top-down approach - pointer to node
void insertNode(Node L, int data){
    /* get the level using coin flip */
    int level_size;
    for(level_size = 1; coinFlip() != 0 && level_size <= MAX_LEVEL; level_size++){}

    Node temp = createNewNode(data, level_size);
    Node trav = NULL;
    int x;

    /* traverse by level */
    for(x = temp->level - 1, trav = L; x >= 0; x--){
        /* traverse by node */
        /* skip nodes as necessary */
        for(; temp->data > trav->next[x]->data; trav = trav->next[x]){}

        /* adjust pointers */
        temp->next[x] = trav->next[x];
        trav->next[x] = temp;
    }
}

// top-down approach - pointer to pointer
void insertNodev1(Node L, int data){
    /* get the level using coin flip */
    int level_size;
    for(level_size = 1; coinFlip() != 0 && level_size <= MAX_LEVEL; level_size++){}
    
    Node temp = createNewNode(data, level_size);
    Node *trav = NULL;
    int x;

    /* traverse by level */
    for(x = temp->level - 1, trav = &(L->next[x]); x >= 0; x--, trav--){
        /* traverse by node */
        /* skip nodes as necessary */
        for(; temp->data > (*trav)->data; trav = &(*trav)->next[x]){}

        temp->next[x] = (*trav);
        (*trav) = temp;
    }
}

/**
 * @brief search for a node in the skip list
 * 
 * @param L head pointer
 * @param data key to find
 * @return int level of the node, otherwise -1
 */
int searchNode(Node L, int data){
    Node trav;
    int x;
    /* traverse by level */
    for(x = L->level - 1, trav = L; x >= 0 && data != trav->next[x]->data; x--){
        /* traverse by node */
        /* skip nodes as necessary */
        for(; data > trav->next[x]->data; trav = trav->next[x]){}
    }
    return x;
}

void deleteNode(Node L, int data){
    /* find the correct position of the node */
    int level = searchNode(L, data);

    if(level == -1){
        printf("Node is not in the skiplist\n");
        return;
    }

    Node trav, temp;
    int x;
    for(x = level, trav = L; x >= 0; x--){
        for(; data > trav->next[x]->data; trav = trav->next[x]){}

        temp = trav->next[x];
        trav->next[x] = temp->next[x];
    }
}

void displayList(Skiplist l){
	printf("\n===============================================================================");
	printf("\nList:");
	
	Node trav;
	int x;
	for(trav = l.head->next[0]; trav->next != NULL; trav = trav->next[0]){
		printf("\nTrav: %x Data: %d Level: %d ", trav, trav->data, trav->level);
		if(trav->next != NULL){
			for(x = 0; x <= trav->level; x++){
				printf("\n\tnext[%d]: %x ", x, trav->next[x]);
			}
			printf("\n");
		}else{
			printf("%x ", trav->next);
		}
	}
	printf("===============================================================================");
}

void populateList(Node L){
    int num_of_nodes = rand() % 10 + 1;

    for(int x = 0; x < num_of_nodes; x++){
        insertNodev1(L, rand());
    }
}

void main(){
    Skiplist list = {NULL, MAX_LEVEL};
    srand(time(NULL));

    initList(&list);
    populateList(list.head);
    displayList(list);
}