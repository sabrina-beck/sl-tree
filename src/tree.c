#include "tree.h"
#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

Stack *stack = NULL;

const char *getCategoryName(NodeCategory category);

Stack *getStack() {
    if (stack == NULL) {
        stack = newStack();
    }
    return stack;
}

void *getTree() {
    Stack *stack = getStack();
    return pop(stack);
}

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

void dumpTree(TreeNodePtr p, int indent) {
    // TODO
}

void addTreeNodeWithName(NodeCategory category, int numberOfChildNodes, char *name) {

    TreeNodePtr node = malloc(sizeof(TreeNode));
    node->category = category;
    node->name = name;
    node->next = NULL;

    Stack *stack = getStack();

    for (int i = 0; i < numberOfChildNodes; i++) {
        TreeNodePtr childNode = pop(stack);
        node->subtrees[i] = childNode;
    }

    for (int i = numberOfChildNodes; i < MAX_CHILD_NODES; i++) {
        node->subtrees[i] = NULL;
    }

    push(stack, node);
}

void addTreeNode(NodeCategory category, int numberOfChildNodes) {
    addTreeNodeWithName(category, numberOfChildNodes, NULL);
}

void addSequence() {
    Stack *stack = getStack();

    TreeNodePtr topNode = pop(stack);
    TreeNodePtr nextNode = pop(stack);

    if (nextNode != NULL) {
        nextNode->next = topNode;
        push(stack, nextNode);
    } else {
        push(stack, topNode);
    }
}

void addEmpty() {
    Stack *stack = getStack();
    push(stack, NULL);
}

void addFunction() {
    addTreeNode(FUNCTION_NODE, 2);
}

void addFunctionHeader() {
    addTreeNode(FUNCTION_HEADER_NODE, 3);
}

void addExpressionParameter() {
    addTreeNode(EXPRESSION_PARAMETER_NODE, 2);
}

void addBlock() {
    addTreeNode(BLOCK_NODE, 5);
}

void addTypeDeclaration() {
    addTreeNode(TYPE_DECLARATION_NODE, 2);
}

void addDeclaration() {
    addTreeNode(DECLARATION_NODE, 2);
}

void addType() {
    addTreeNode(TYPE_NODE, 2);
}

void addStatement() {
    addTreeNode(STATEMENT_NODE, 2);
}

void addUnlabeledStatement() {
    Stack *stack = getStack();
    void *topNode = pop(stack);
    addEmpty();
    push(stack, topNode);
    addStatement();
}

void addLabel() {
    addTreeNode(LABEL_NODE, 1);
}

void addAssignment() {
    addTreeNode(ASSIGNMENT_NODE, 2);
}

void addVariable() {
    addTreeNode(VARIABLE_NODE, 2);
}

void addFunctionCall() {
    addTreeNode(FUNCTION_CALL_NODE, 2);
}

void addGoto() {
    addTreeNode(GOTO_NODE, 1);
}

void addReturn() {
    addTreeNode(RETURN_NODE, 1);
}

void addIf() {
    addTreeNode(IF_NODE, 2);
}

void addWhile() {
    addTreeNode(WHILE_NODE, 2);
}

void addExpression() {
    addTreeNode(EXPRESSION_NODE, 3);
}

void addSimpleExpression() {
    addTreeNode(SIMPLE_EXPRESSION_NODE, 2);
}

void addUnaryOperatorExpression() {
    addTreeNode(UNARY_OPERATOR_EXPRESSION_NODE, 3);
}

void addAdditionSequence() {
    addTreeNode(ADDITION_SEQUENCE_NODE, 3);
}

void addTerm() {
    addTreeNode(TERM_NODE, 2);
}

void addMultiplicativeSequence() {
    addTreeNode(MULTIPLICATIVE_SEQUENCE_NODE, 3);
}

void addInteger(char *tokenValue) {
    addTreeNodeWithName(INTEGER_NODE, 0, tokenValue);
}

void addIdentifier(char *tokenValue) {
    addTreeNodeWithName(IDENTIFIER_NODE, 0, tokenValue);
}

void addRelationalOperator(char *tokenValue) {
    addTreeNodeWithName(RELATIONAL_OPERATOR_NODE, 0, tokenValue);
}

void addAdditiveOperator(char *tokenValue) {
    addTreeNodeWithName(ADDITIVE_OPERATOR_NODE, 0, tokenValue);
}

void addUnaryOperator(char *tokenValue) {
    addTreeNodeWithName(UNARY_OPERATOR_NODE, 0, tokenValue);
}

void addMultiplicativeOperator(char *tokenValue) {
    addTreeNodeWithName(MULTIPLICATIVE_OPERATOR_NODE, 0, tokenValue);
}

const char *getCategoryName(NodeCategory category) {
    switch (category) {
        case FUNCTION_NODE:
            return "FUNCTION";

        case FUNCTION_HEADER_NODE:
            return "FUNCTION_HEADER";
        case EXPRESSION_PARAMETER_NODE:
            return "EXPRESSION_PARAMETER";

        case BLOCK_NODE:
            return "BLOCK";

        case TYPE_DECLARATION_NODE:
            return "TYPE_DECLARATION";
        case DECLARATION_NODE:
            return "DECLARATION";
        case TYPE_NODE:
            return "TYPE";

        case STATEMENT_NODE:
            return "STATEMENT";
        case LABEL_NODE:
            return "LABEL";

        case ASSIGNMENT_NODE:
            return "ASSIGNMENT";
        case VARIABLE_NODE:
            return "VARIABLE";

        case FUNCTION_CALL_NODE:
            return "FUNCTION_CALL";

        case GOTO_NODE:
            return "GOTO";

        case RETURN_NODE:
            return "RETURN";

        case IF_NODE:
            return "IF";

        case WHILE_NODE:
            return "WHILE";

        case EXPRESSION_NODE:
            return "EXPRESSION";
        case SIMPLE_EXPRESSION_NODE:
            return "SIMPLE_EXPRESSION";
        case UNARY_OPERATOR_EXPRESSION_NODE:
            return "UNARY_OPERATOR_EXPRESSION";
        case ADDITION_SEQUENCE_NODE:
            return "ADDITION_SEQUENCE";
        case TERM_NODE:
            return "TERM";
        case MULTIPLICATIVE_SEQUENCE_NODE:
            return "MULTIPLICATIVE_SEQUENCE";

        case INTEGER_NODE:
            return "INTEGER";
        case IDENTIFIER_NODE:
            return "IDENTIFIER";

        case RELATIONAL_OPERATOR_NODE:
            return "RELATIONAL_OPERATOR";
        case ADDITIVE_OPERATOR_NODE:
            return "ADDITIVE_OPERATOR";
        case UNARY_OPERATOR_NODE:
            return "UNARY_OPERATOR";
        case MULTIPLICATIVE_OPERATOR_NODE:
            return "MULTIPLICATIVE_OPERATOR";
    }
}