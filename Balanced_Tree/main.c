#include "tree.h"

int main () {

    Root mainRoot = {};

    TreeInit (&mainRoot);
    InsertIntoTree (&mainRoot, 5, 7, 10, 13);
    InsertIntoTree (&mainRoot, 10, 7, 10, 13);
    InsertIntoTree (&mainRoot, 3, 7, 10, 13);
    InsertIntoTree (&mainRoot, 4, 7, 10, 13);
}