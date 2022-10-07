#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CHILDREN_SIZE 26 //26 lowercase letters

typedef struct trieNode{
    struct trieNode *children[CHILDREN_SIZE]; //array of trie pointer
    int isEndofWord; //0 if not end and 1 if end
}*triePtr;

triePtr initializeTrie(){
    triePtr root = (triePtr)calloc(1, sizeof(struct trieNode));

    return root;
}

int getIndex(char input){
    return input - 'a';
}

void insert(triePtr root, char word[]){
    triePtr trav = NULL;
    int x, index = 0;

    for(x = 0, trav = root; word[x] != '\0'; x++, trav = trav->children[index]){
        // get the index of the current character
        index = getIndex(word[x]);

        // check if the current character exists in the trie
        // if not, initialize character
        if(trav->children[index] == NULL){
            trav->children[index] = initializeTrie();
        }
    }

    // set the last character as the end of the word
    trav->isEndofWord = 1;
}

// returns 1 if word is found, otherwise return 0
int search(triePtr root, char word[]){
    triePtr trav = NULL;
    int x, index = 0;

    // traverse the given word
    for(x = 0, trav = root; word[x] != '\0'; x++, trav = trav->children[index]){
        index = getIndex(word[x]);

        // check if the current letter exists
        if(trav->children[index] == NULL){
            return 0;
        }
    }

    return trav->isEndofWord;
}

// return 1 if node has children, otherwise return 0
int isPrefix(triePtr node){
    int x = 0;
    
    if(node != NULL)
      for(; node->children[x] == NULL && x < CHILDREN_SIZE; x++){}

    return (x < CHILDREN_SIZE) ? 1 : 0;
}

void delete(triePtr *root, char word[], int letter){
    if(letter == strlen(word) + 1){
        return;
    }
    
    int index = getIndex(word[letter]);
    int next = letter + 1;
    // triePtr *address = (index >= 0 && index < CHILDREN_SIZE) ? &(*root)->children[index] : NULL;
    // get to the last character
    delete(&(*root)->children[index], word, next);

    triePtr *trav = root, temp = *trav;
    // check if the letter is the end of the word
    if(letter == strlen(word) && temp->isEndofWord == 1){
        temp->isEndofWord = 0;

        // if the node has no children, just delete it
        if(isPrefix(temp) == 0){
            *trav = NULL;
            free(temp);
            temp = NULL;
        }
    }

    // if the node has no children and it is not the end of the word, delete it
    if(isPrefix(temp) == 0 && temp->isEndofWord == 0){
        *trav = NULL;
        free(temp);
        temp = NULL;
    }
}

void main(){
    // get root node
    triePtr root = initializeTrie();

    // insert "words" to the trie
    insert(root, "keys");
    delete(&root, "keys", 0);
}