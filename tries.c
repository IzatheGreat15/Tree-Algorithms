#include<stdio.h>
#include<stdlib.h>

#define CHILDREN_SIZE 26 //26 lowercase letters

typedef struct trieNode{
    struct trieNode *children[CHILDREN_SIZE]; //array of trie pointer
    int isEndofWord; //0 if not end and 1 if end
}*triePtr;

void main(){

}
