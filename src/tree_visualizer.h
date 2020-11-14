/**
 * This file provides facilities to visualize the syntax tree
 **/

#ifndef   TREE_BUILDER_H
    #define   TREE_BUILDER_H
    #include "tree_builder.h"
#endif

/**
 * It prints the syntax tree on standard output
 * Subtrees which form a sequence (ex: sequence of statements, sequence of identifiers, etc.) will be represented with
 * the prefix "|->" before all the elements on the sequence except the first one
 **/
void dumpTree(void *p);