#include "tree.h"
//----------------------------------------
//----------------------------------------
TreeErrors TreeInit (Root* mainRoot) {


    mainRoot->root = (Tree*) calloc (1, sizeof (Tree));

    if (IS_NULL (mainRoot->root)) {

        PrintTreeErr (NULL_POINTER_ON_TREE);
            return NULL_POINTER_ON_TREE;

    }
    // NAN shows root still has no any data 
    // mainRoot->root->value_1 = NAN; 
    // mainRoot->root->value_2 = NAN;
    // mainRoot->root->value_3 = NAN;

    

    return NO_TREE_ERR;
}
//----------------------------------------
//----------------------------------------
Tree* TreeInit_t () {

    Tree* mainRoot = NULL;
    mainRoot = (Tree*) calloc (1, sizeof (Tree));

    if (IS_NULL (mainRoot)) {

        PrintTreeErr (NULL_POINTER_ON_TREE);
            return NULL_POINTER_ON_TREE;

    }
    // NAN shows root still has no any data 
    // mainRoot->root->value_1 = NAN; 
    // mainRoot->root->value_2 = NAN;
    // mainRoot->root->value_3 = NAN;

    

    return mainRoot;
}
//----------------------------------------
//----------------------------------------
static TreeErrors InsertRoot (Tree* root, KeyType key, InfoType value_1, InfoType value_2, InfoType value_3) {

    if (IS_NULL (root)) {

        PrintTreeErr (NULL_POINTER_ON_TREE);
            return NULL_POINTER_ON_TREE;

    }

    root->key = key;
    root->value_1 = value_1;
    root->value_2 = value_2;
    root->value_3 = value_3;

    return NO_TREE_ERR;    
}
//----------------------------------------
//----------------------------------------
Tree* CreateNode (Tree* parent, KeyType key, InfoType value_1, InfoType value_2, InfoType value_3) { //TODO: Think about type (errors)

    Tree* node = NULL;

    node = (Tree*) calloc (1, sizeof (Tree));
    if (IS_NULL (node)) {

        PrintTreeErr (NULL_POINTER_ON_TREE);
            return NULL_POINTER_ON_TREE;

    }

    node->key = key;
    node->value_1 = value_1;
    node->value_2 = value_2;
    node->value_3 = value_3;
    node->parent = parent;

    return node;    
}
//----------------------------------------
//----------------------------------------
Tree* InsertIntoTree (Tree* root, KeyType key, InfoType value_1, InfoType value_2, InfoType value_3) {

    //Tree* root = NULL;
    
    if (root == NULL) {

        root = CreateNode (NULL, key, value_1, value_2, value_3);
        if (IS_NULL (root)) {

            PrintTreeErr (NULL_POINTER_ON_TREE);
                return NULL_POINTER_ON_TREE;
        }
    }

    

    if (key < root->key)
		root->left = InsertIntoTree(root->left, key, value_1, value_2, value_3);
	else if (key > root->key)
		root->right = InsertIntoTree(root->left, key, value_1, value_2, value_3);

	return TreeBalance (root);

    



    //root = mainRoot->root;

    // if (mainRoot->isRootFull == 0) {
        
    //     InsertRoot (root, key, value_1, value_2, value_3);
    //     mainRoot->isRootFull = 1;

    //     return NO_TREE_ERR;
    // }

    // while (1) {
        
    //     if (key == root->key) // TODO: FIX IT WITH THE REQUIREMENT OF TASK!
    //         return NO_TREE_ERR;

    //     if (key < root->key) {

    //         if (root->left)
    //             root = root->left;
    //         else {

    //             root->left = CreateNode (root, key, value_1, value_2, value_3);
    //             TreeBalance (root);
    //             break;
    //         }
    //     }
    //     else {

    //         if (root->right)
    //             root = root->right;
    //         else {

    //             root->right = CreateNode (root, key, value_1, value_2, value_3);
    //             TreeBalance (root);
    //             break;
    //         }
    //     }

    //}

    //return NO_TREE_ERR;

}
//----------------------------------------
//----------------------------------------
Tree* TreeBalance (Tree* node) {

    if (IS_NULL (node)) {

        PrintTreeErr (NULL_POINTER_ON_TREE);
            return NULL_POINTER_ON_TREE;
    }

    FixHeight (node);

    if (Difference (node) >= 2){

        if (Difference (node->right) < 0)
            node->right = RotateRight (node->right);
        return RotateLeft (node);
    }
    if (Difference (node) <= -2){

        if (Difference (node->right) > 0)
            node->left = RotateLeft (node->left);
        return RotateRight (node);
    }

    return node;
}
//----------------------------------------
//----------------------------------------
Tree* RotateRight (Tree* node) {

    Tree* balanceNode = NULL;
    if (IS_NULL (node)) {

        PrintTreeErr (NULL_POINTER_ON_TREE);
            return NULL_POINTER_ON_TREE;

    }   

    balanceNode = node->left;
    node->left  = node;
    FixHeight (node);
    FixHeight (balanceNode);

    return balanceNode;

}
//----------------------------------------
//----------------------------------------
Tree* RotateLeft (Tree* balanceNode) {

    Tree* node = NULL;
    if (IS_NULL (balanceNode)) {

        PrintTreeErr (NULL_POINTER_ON_TREE);
            return NULL_POINTER_ON_TREE;

    }   

    node = balanceNode->right;
    balanceNode->right = node->left;
    node->left = balanceNode;
    FixHeight (balanceNode);
    FixHeight (node);

    return node;
}
//----------------------------------------
//----------------------------------------
TreeErrors FixHeight (Tree* node) {


    unsigned char rightHeight = 0;
    unsigned char leftHeight = 0;
    if (IS_NULL (node)) { //TODO: Maybe make a define :) 

        PrintTreeErr (NULL_POINTER_ON_TREE);
            return NULL_POINTER_ON_TREE;

    }

    //hr = (node->right != NULL) ? (node->right)->h : 0;
	//hl = (node->left != NULL) ? (node->left)->h : 0;

    if (node->right)
        rightHeight = node->right->height;
    
    if (node->left)
        leftHeight  = node->left->height;

    if (leftHeight > rightHeight)
        node->height = leftHeight++;
    else    
        node->height = rightHeight++;

    return NO_TREE_ERR;
}
//----------------------------------------
//----------------------------------------
int Difference (Tree* node) { //bfactor 

    unsigned char rightHeight = 0;
    unsigned char leftHeight = 0;
    if (IS_NULL (node)) {

        PrintTreeErr (NULL_POINTER_ON_TREE);
            return NULL_POINTER_ON_TREE;

    }

    if (node->right)
        rightHeight = node->right->height;
    
    if (node->left)
        leftHeight  = node->left->height;

    return rightHeight - leftHeight;

}
//----------------------------------------
//----------------------------------------
void PrintTreeErr (TreeErrors err) {

    switch (err) {

        case NO_TREE_ERR:
            break;
        case NULL_POINTER_ON_TREE: {

            printf ("Null pointer on tree!\n");
            break;

        }
        default: {

            printf ("Unexpected table error was catched in function %s!\n", __FUNCTION__);
            break;
            
        }
    }
}
//----------------------------------------
//----------------------------------------