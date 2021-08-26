#pragma once
//----------------------------------------
//----------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
//----------------------------------------
//----------------------------------------
#define IS_NULL(ptr)    !ptr
//----------------------------------------
//----------------------------------------
typedef unsigned int KeyType; //Use type "KeyType" instead of the basic type "unsigned int"
typedef double       InfoType;
typedef char         Balance;
//----------------------------------------
//----------------------------------------
// Declarations of structers and enums
typedef enum TreeErrors {

    NULL_POINTER_ON_TREE,
    NO_TREE_ERR

}   TreeErrors;
//----------------------------------------
//----------------------------------------
typedef struct Tree {

    Balance       difference;
    int           height;
  // Key field
    KeyType        key;
  // Address fields
    struct Tree*  parent;  
    struct Tree*  left;
    struct Tree*  right;
  // Informational fields 
    InfoType      value_1;
    InfoType      value_2;
    InfoType      value_3;

} Tree;
//----------------------------------------
//----------------------------------------
typedef struct Root {

  // Root of the tree 
    Tree* root;
    char  isRootFull;
    
} Root;
//----------------------------------------
//----------------------------------------
//Prototypes of functions
Tree* InsertIntoTree (Tree* mainRoot, KeyType key, InfoType value_1, InfoType value_2, InfoType value_3);
TreeErrors TreeInit (Root* mainRoot);
Tree* RotateLeft (Tree* balanceNode);
void PrintTreeErr (TreeErrors err);
TreeErrors FixHeight (Tree* node);
Tree* TreeBalance (Tree* node);
Tree* RotateRight (Tree* node);
int Difference (Tree* node);
Tree* TreeInit_t ();
