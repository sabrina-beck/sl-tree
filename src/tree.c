#include "tree.h"

#include <stdlib.h>

/**
 * Internal variables and functions declaration
 **/

int count(TreeNodePtr treeNodePtr, NodeCategory category);


/**
 * Public functions implementation
 **/
void *getTree() {
    return getSyntaxTree();
}

void counts(void *p, int *functions, int *funcalls, int *whiles, int *ifs, int *bin) {
    TreeNodePtr treeNodePtr = (TreeNodePtr) p;

    *functions = count(treeNodePtr, FUNCTION_NODE);
    *funcalls = count(treeNodePtr, FUNCTION_CALL_NODE);
    *whiles = count(treeNodePtr, WHILE_NODE);
    *ifs = count(treeNodePtr, IF_NODE);

    int relationalExpressions = count(treeNodePtr, RELATIONAL_OPERATOR_NODE);
    int additiveExpressions = count(treeNodePtr, ADDITIVE_OPERATOR_NODE);
    int multiplicativeExpressions = count(treeNodePtr, MULTIPLICATIVE_OPERATOR_NODE);
    *bin = relationalExpressions + additiveExpressions + multiplicativeExpressions;
}

/**
 * Internal functions implementation
 **/

int count(TreeNodePtr treeNodePtr, NodeCategory category) {
    if (treeNodePtr == NULL) {
        return 0;
    }

    int nodesWithCategory = 0;
    if(treeNodePtr->category == category) {
        nodesWithCategory++;
    }

    nodesWithCategory += count(treeNodePtr->next, category);

    for (int i = 0; i < MAX_CHILD_NODES; i++) {
        TreeNodePtr child = treeNodePtr->subtrees[i];
        nodesWithCategory += count(child, category);
    }

    return nodesWithCategory;
}