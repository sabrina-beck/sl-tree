#include "tree.h"
#include "stack.h"

#include <stdlib.h>

Stack stack;

void *getTree() {
    stack = newStack();
    // TODO
}

void counts(void *p, int *functions, int *funcalls, int *whiles, int *ifs, int *bin) {
    // TODO
}

void dumpTree(TreeNodePtr p, int indent) {
    // TODO
}

void addTreeNodeWithName(NodeCategory category, int numberOfChildNodes, char* name) {
    TreeNodePtr node = malloc(sizeof(TreeNode));
    node->category = category;
    node->name = name;
    node->next = NULL;

    for(int i = 0; i < numberOfChildNodes; i++) {
        TreeNodePtr childNode = pop(stack);
        node->subtrees[i] = childNode;
    }

    push(stack, node);
}

void addTreeNode(NodeCategory category, int numberOfChildNodes) {
    addTreeNodeWithName(category, numberOfChildNodes, NULL);
}

void addSequence() {
    // Reversed list!
    TreeNodePtr topNode = pop(stack);
    TreeNodePtr nextNode = pop(stack);

    topNode->next = nextNode;
    push(stack, topNode);
}

void addIdentifier(char *tokenValue) {
    addTreeNodeWithName(IDENTIFIER, 0, tokenValue);
}

void addEmpty() {
    push(stack, NULL);
}

void addFunction() {
    addTreeNode(FUNCTION, 2);
}
