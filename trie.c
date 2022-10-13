#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CHILDREN_SIZE 26 //26 lowercase letters

typedef struct trieNode{
    struct trieNode* children[CHILDREN_SIZE]; //array of trie pointer
    char isEndofWord;
}*triePtr;

triePtr initializeTrie(){
    triePtr root = (triePtr)calloc(1, sizeof(struct trieNode));

    return root;
}

int getIndex(char input){
	
    return tolower(input) - 'a';
}

void insert(triePtr root, char word[]){
	if(search(root, word) == 0){
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
    	printf("\nWORD '%s' successfully inserted!", word);
	}else{
		printf("\nWORD '%s' already exists!", word);
	}
    
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
        	printf("\nWORD '%s' not found.", word);
            return 0;
        }
    }

	printf("\nWORD '%s' %s.", word, trav->isEndofWord == 0 ? "not found" : "found");
    return trav->isEndofWord;
}

// return 1 if node has children, otherwise return 0
int isPrefix(triePtr node){
    int x;
    for(x = 0; node->children[x] != NULL && x < CHILDREN_SIZE; x++){}

    return (x < CHILDREN_SIZE) ? 1 : 0;
}

void deleteWord(triePtr root, char word[]){
    if(search(root, word) != 0){
    	deleteNode(root, word, 0);
    	printf("\nWORD '%s' successfully deleted.", word);
	}	
}

int deleteNode(triePtr root, char word[], int curr){
	displayA(root);
	//printf("%c", word[curr]);
	int x, y = 0; //indicate if node is to be deleted
	
	if(word[curr] != '\0' && deleteNode(root->children[word[curr] - 'a'], word, curr + 1) > 0){
		free(root->children[word[curr] - 'a']);
		root->children[word[curr] - 'a'] = NULL;
	}
	
	if(word[curr] == '\0'){
      root->isEndofWord = 0;
    }
	
	for(x = 0; x < CHILDREN_SIZE; x++){
		if(root->children[x] != NULL){
			y++;
		}
	}
	
	return (y > 0) ? 0 : 1;
}

void displayArray(triePtr root){
	int x;
	for(x = 0; x < CHILDREN_SIZE; x++){
		if(root->children[x] != NULL){
			displayArray(root->children[x]);
		} 
	}
	
	for(x = 0; x < CHILDREN_SIZE; x++){
		if(root->children[x] != NULL){
			printf("%c", x + 'a');
		} 
	}
	printf("\n");
}

void displayA(triePtr root){
	int x;
	printf("\n");
	for(x = 0; x < CHILDREN_SIZE; x++){
		printf("%d ", root->children[x] == NULL ? 0 : 1);
	}
	printf("%c ", root->isEndofWord == 1 ? 'E' : 'N');
}

void startsWith(triePtr root, char string[]){
	printf("\n\nSearching for words starting in '%s'...", string);
	int curr;
	for(curr = 0; string[curr] != '\0'; root = root->children[string[curr] - 'a'], curr++);
	printWords(root, string);
}

void printWords(triePtr root, char string[]){
	if(root->isEndofWord == 1){
		printf("\n%s", string);
	}
	
	int x, y;
	triePtr next;
	char newString[32];
	for(x = 0; x < CHILDREN_SIZE; x++){
		next = root->children[x];
		if(next != NULL){
			memset(newString, '\0', sizeof(newString));
   			strcpy(newString, string);
   			for(y = 0; newString[y] != '\0'; y++);
   			newString[y] = x + 'a';
   			
			printWords(next, newString);
		}
		
	}
}

void main(){
    // get root node
    triePtr root = initializeTrie();

    typedef char String[32];
    String a[] = {
    	"keys",
    	"altercation",
		"enthusiasm",
		"importance",
		"president",
		"thought",
		"efficiency",
		"affair",
		"leadership",
		"county",
		"decision",
		"reality",
		"employee",
		"birthday",
		"basket",
		"transportation",
		"guidance",
		"orthopoedic",
		"arteries",
		"cat",
		"cataract",
		"contract",
		"contact",
		"infection",
		"comparison",
		"compare",
		"compared",
		"compares",
		"cats",
		"cataracts",
		"infection",
		"advertise",
		"portion",
		"deviation",
		"valley",
		"invisible",
		"punish",
		"recognize",
		"accountant",
		"complain",
		"national",
		"conscious",
		"autonomy",
		"wriggle",
		"shallow",
		"texture",
		"achieve",
		"fragrant",
		"contract",
		"intervention",
		"circle",
		"despair",
		"feminine",
		"burial",
		"diamond",
		"orchestra",
		"occupation",
		"crosswalk",
		"barrel",
		"vehicle",
		"courtship",
		"expose",
		"disability",
		"provide",
		"ancestor",
		"medium",
		"layout",
		"carbon",
		"patience",
		"liability",
		"absolute",
		"contribution",
		"contact",
		"please",
		"evening",
		"abandon",
		"colony",
		"install",
		"fitness",
		"reception",
		"sanctuary",
		"refund",
		"earthflax",
		"extinct",
		"forecast",
		"approach",
		"sausage",
		"mutual",
		"contraction",
		"strange",
		"stroll",
		"symptom",
		"fashionable",
		"material",
		"classify",
		"functional",
		"struggle",
		"lawyer",
		"fluctuation",
		"offspring",
		"acquit",
		"remark",
		"hunter",
		"failure",
		"freight",
		"belief",
		"winner",
		"obscure",
		"examination",
		"bronze",
		"efflux",
		"royalty",
		"formation",
		"church",
		"parallel",
		"coverage",
		"ribbon",
		"passion",
		"stimulation",
		"plaintiff",
		"curriculum",
		"useful",
		"weight",
		"safari",
		"franchise",
		"inhabitant",
		"simplicity",
		"minute",
		"mainstream",
		"railcar",
		"proper",
	};
	
	int x;
	for(x = 0; x < 131; x++){
		insert(root, a[x]);
	}
	
    //displayArray(root);
    startsWith(root, "c");
    deleteWord(root, "cataract");
    startsWith(root, "c");
}
