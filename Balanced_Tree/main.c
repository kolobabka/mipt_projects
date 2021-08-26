#include "tree.h"

int main () {

    Root mainRoot = {};
    Tree* root = NULL;

    root = TreeInit_t ();
    //TreeInit (&mainRoot);
    InsertIntoTree (root, 5, 7, 10, 13);
    InsertIntoTree (root, 10, 7, 10, 13);
    InsertIntoTree (root, 3, 7, 10, 13);
    InsertIntoTree (root, 4, 7, 10, 13);
    for (int i = 20; i < 100000; i++)
    {
        InsertIntoTree (root, i, 7, 10, 13);
        printf ("%d\n", i);
    }
    
}