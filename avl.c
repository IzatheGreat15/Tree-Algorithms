#include<stdio.h>
#include<stdlib.h>
 
// An AVL tree node
typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
}*AVL;

int max(int a, int b){
  return (a > b) ? a : b;
}

int height(AVL root){
  if(root == NULL)
    return -1;
    
  root->height = max(height(root->left), height(root->right)) + 1;
  
  return root->height;
}

int getBalance(AVL root){
  int left = ((root->left != NULL) ? root->left->height : -1) + 1;
  int right = ((root->right != NULL) ? root->right->height : -1) + 1;
  return left - right;
}

//left rotate
void RR(AVL *root){
  AVL right = (*root)->right;
  AVL child = right->left;
  
  //perform rotation
  right->left = *root;
  (*root)->right = child;
  *root = right;
  
  //update height
  height(*root);
  height(right);
}

//right rotate
void LL(AVL *root){
  AVL left = (*root)->left;
  AVL child = left->right;
  
  //perform rotation
  left->right = *root;
  (*root)->left = child;
  *root = left;
  
  //update height
  height(*root);
  height(left);
}

void insert(AVL *root, int key){
  if((*root) == NULL){
    //insert key
    *root = (AVL)calloc(1, sizeof(struct Node));
    (*root)->key = key;
  }else{
    if(key < (*root)->key){
      insert(&(*root)->left, key);
    } else if (key > (*root)->key){
      insert(&(*root)->right, key);
    }
    
    //update height
    height(*root);
    
    //get balance factor
    int BF = getBalance(*root);
    
    //left
    if(BF > 1){
      //LL case
      if(key < (*root)->left->key){
        LL(root);
      }
      //LR case
      else if(key > (*root)->left->key){
        RR(&(*root)->left);
        LL(root);
      }
    }
    //right
    else if(BF < -1){
      //RL case
      if(key < (*root)->left->key){
        LL(&(*root)->right);
        RR(root);
      }
      //RR case
      else if(key > (*root)->left->key){
        RR(root);
      }
    }
  }
}

int main(){
  AVL root = NULL;
  
  insert(&root, 40);
  insert(&root, 10);
  insert(&root, 20);
  insert(&root, 25);
  insert(&root, 23);
 
  return 0;
}