#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MIN -2147483647
#define MAX 2147483647

#define SIZE 10

typedef struct node {
    int data;
    struct node *next;
    struct node *below;
}*Node;

typedef struct {
    Node head;
    int level;
    int maxLevel;
}SkipList;

void initSkipList(SkipList *list);
void insertData(Node *head, int data, int level, SkipList *list);
void createNewNode(Node *head, int data, Node new);
int coinFlip();
void deleteData(Node *head, int data);
void removeNode(Node *head);
void populateList(SkipList *list, int arr[]);
Node searchList(Node head, int data);
void displayList(SkipList list);

int main()
{
    srand(time(NULL));
    int arr[] = {3,2,1,4,5,7,6,8,9,0};
    SkipList list = {NULL, 0, 5};

    initSkipList(&list); // initialization
    // displayList(list);
    printf("Skiplist");
    // printf("\n");

    populateList(&list, arr); // insertion
    // displayList(list);

    // printf("\n\n");
    Node get = searchList(list.head, 5); // search
    // printf("\ntest: %d\n", get != NULL ? get->data: -1);

    deleteData(&(list.head), 5); // deletion
    displayList(list);
    return 0;
}

void initSkipList(SkipList *list) // initialize a -2147483647 -> 2147483647 linked list
{
    int i;
    Node trav = list->head, prev;
    list->head = (struct node*)malloc(sizeof(struct node));
    list->head->data = MIN;
    list->head->next = (struct node*)malloc(sizeof(struct node));
    list->head->next->data = MAX;
    list->head->next->next = NULL;
    list->head->below = trav;
    for(prev = trav;trav != NULL; prev = trav, trav = trav->next) {} // gets last node of below the head
    list->head->next->below = prev;
    list->level++;
}

void insertData(Node *head, int data, int level, SkipList *list)
{
    static int coin;
    static int currentLevel;
    static Node new;
    new = NULL;
    coin = 0;

    if(*head == NULL) {
        return;
    }

    if(data < (*head)->next->data && (*head)->below != NULL) { 
        insertData(&(*head)->below, data, level-1, list);
    } else if(data > (*head)->next->data) {
        insertData(&(*head)->next, data, level, list);
    } else {
        createNewNode(head, data, new);
        currentLevel = level+1;
        new = (*head)->next;
        coin = coinFlip();
    }

    
    if(level == currentLevel && coin) { // if "heads" and a level above the created node
        createNewNode(head, data, new);
        new = (*head)->next;
        coin = coinFlip();
        currentLevel++;
    } else if(level == list->level) { // if at the top level
        while(coin && currentLevel <= list->maxLevel) { // iterates until "tails" or it is greater than max level
            initSkipList(list);
            createNewNode(&(list->head), data, new);
            new = list->head->next;
            coin = coinFlip();
            currentLevel++;
        }
        
    }

}

void createNewNode(Node *head, int data, Node new)
{
    Node newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = (*head)->next;
    newNode->below = new;
    (*head)->next = newNode;
}

int coinFlip()
{
    int ret = rand() % 2;
    return ret;
}

void populateList(SkipList *list, int arr[])
{
    int i;
    for(i = 0; i < SIZE; i++) {
        insertData(&(list->head), arr[i], list->level, list);
    }
}

void deleteData(Node *head, int data)
{
    if(*head == NULL) {
        return;
    }

    if((*head)->next != NULL && data >= (*head)->next->data) {
        deleteData(&(*head)->next, data);
    }
    if(data == (*head)->data) {
        removeNode(head);
    }
    if((*head)->next != NULL && data < (*head)->next->data) {   
        deleteData(&(*head)->below, data);
    }
}

void removeNode(Node *head)
{
    Node temp = *head;
    *head = temp->next;
    free(temp);
}

Node searchList(Node head, int data)
{
    if(head == NULL) {
        return NULL;
    }

    if(data < head->next->data) {  
        // printf("iterate "); 
        searchList(head->below, data);
    } else if(data > head->next->data) {
        // printf("iterate "); 
        searchList(head->next, data);
    } else {
        return head->next;
    }
    
}

void displayList(SkipList list)
{

    Node trav1, trav2;
    for(trav1 = list.head; trav1 != NULL; trav1 = trav1->below) {
        printf("\n");
        for(trav2 = trav1; trav2 != NULL; trav2 = trav2->next) {
            printf("%d ", trav2->data);
        }
    }
    

}
