#include<stdio.h>
#include<stdlib.h>

#define CHILDREN_SIZE 26 //26 lowercase letters

typedef struct trieNode{
    struct trieNode *children[CHILDREN_SIZE]; //array of trie pointer
    int isEndofWord; //0 if not end and 1 if end
}*triePtr, trieNode;

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

    for(x = 0, trav = root; word[x + 1] != '\0'; x++, trav = trav->children[index]){
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
    for(x = 0, trav = root; word[x + 1] != '\0'; x++, trav = trav->children[index]){
        index = getIndex(word[x]);

        // check if the current letter exists
        if(trav->children[index] == NULL){
            return 0;
        }
    }

    return trav->isEndofWord;
}

// return 1 if node has children, otherwise return 0
int isPrefix(trieNode node){
    int x;
    for(x = 0; node.children[x] != NULL && x < CHILDREN_SIZE; x++){}

    return (x < CHILDREN_SIZE) ? 1 : 0;
}

void delete(triePtr *root, char word[], int letter){
    if(word[letter] == '\0')
        return;
    
    int index = getIndex(word[letter]);
    // get to the last character
    delete(&(*root)->children[index], word, letter++);

    triePtr *trav = root, temp;

    if((*trav)->isEndofWord == 1){
        temp = *trav;
        temp->isEndofWord = 0;
    }
}

void main(){
    // get root node
    triePtr root = initializeTrie();

    // insert "words" to the trie
    insert(root, "keys");
    int found = search(root, "keys");
}
