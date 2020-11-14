#include "tree.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Internal variables and functions declaration
 **/

/**
 * Always use getStack() to get the stack, it will ensure that the stack is initialized
 **/
Stack *stack = NULL;
Stack *getStack();

/**
 * Initializes a tree node considering that the "numberOfChildNodes" top elements on the stack
 * are the subtrees of the new node.
 **/
void addTreeNodeWithName(NodeCategory category, int numberOfChildNodes, char *name);
void addTreeNode(NodeCategory category, int numberOfChildNodes);

int count(TreeNodePtr treeNodePtr, NodeCategory category);


/**
 * Public functions implementation
 **/

/**
 * The syntax tree will be on top of the stack at the end of the parsing phase
 * This function should be called only after the parser has finished
 * If there is more than one element on the stack, this function will terminate the program with error
 **/
void *getTree() {
    Stack *stack = getStack();

    if (stack->size > 1) {
        fprintf(stderr, "Stack should have only one element which is the syntax tree root, but it has %d elements", stack->size);
        exit(EXIT_FAILURE);
    }

    TreeNodePtr syntaxTree = (TreeNodePtr) pop(stack);

    free(stack);

    return syntaxTree;
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
 * A sequence is defined by the "next" attribute in a tree node, each subtree can have another subtree in its sequence
 * this is used by sequence of statements, sequence of identifiers, etc.
 **/
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

void addExpressionParameterByReference() {
    addTreeNode(EXPRESSION_PARAMETER_BY_REFERENCE_NODE, 2);
}

void addExpressionParameterByValue() {
    addTreeNode(EXPRESSION_PARAMETER_BY_VALUE_NODE, 2);
}

void addFunctionParameter() {
    addTreeNode(FUNCTION_PARAMETER_NODE, 1);
}

void addBlock() {
    addTreeNode(BLOCK_NODE, 5);
}

void addLabels() {
    addTreeNode(LABELS_NODE, 1);
}

void addTypes() {
    addTreeNode(TYPES_NODE, 1);
}

void addVariables() {
    addTreeNode(VARIABLES_NODE, 1);
}

void addFunctions() {
    addTreeNode(FUNCTIONS_NODE, 1);
}

void addBody() {
    addTreeNode(BODY_NODE, 1);
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

void addArraySize() {
    addTreeNode(ARRAY_SIZE_NODE, 1);
}

void addStatement() {
    addTreeNode(STATEMENT_NODE, 2);
}

/**
 * Changing the grammar to add an empty node before an unlabeled statement cause the parser to always consider
 * that a statement will have a label.
 * Therefore, this function will add the empty node for the nonexistent label before the unlabeled statement
 * so the construction of a Statement subtree works fine with two subtrees.
 **/
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

void addArrayIndex() {
    addTreeNode(ARRAY_INDEX_NODE, 1);
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
    addTreeNode(IF_NODE, 3);
}

void addWhile() {
    addTreeNode(WHILE_NODE, 2);
}

void addCompound() {
    addTreeNode(COMPOUND_NODE, 1);
}

void addExpression() {
    addTreeNode(EXPRESSION_NODE, 3);
}

void addBinaryOperatorExpression() {
    addTreeNode(BINARY_OPERATOR_EXPRESSION_NODE, 2);
}

void addUnaryOperatorExpression() {
    addTreeNode(UNARY_OPERATOR_EXPRESSION_NODE, 3);
}

void addAdditiveOperation() {
    addTreeNode(ADDITIVE_OPERATION_NODE, 3);
}

void addTerm() {
    addTreeNode(TERM_NODE, 2);
}

void addMultiplicativeOperation() {
    addTreeNode(MULTIPLICATIVE_OPERATION_NODE, 3);
}

void addFactor() {
    addTreeNode(FACTOR_NODE, 1);
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

Stack *getStack() {
    if (stack == NULL) {
        stack = newStack();
    }
    return stack;
}