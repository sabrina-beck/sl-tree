#include "tree_builder.h"

#include <stdlib.h>
#include <stdio.h>

/**
 * Internal variables and functions declaration
 **/
Stack *stack = NULL;

void addTreeNodeWithName(NodeCategory category, int numberOfChildNodes, char *name);
void addTreeNode(NodeCategory category, int numberOfChildNodes);
Stack *getStack();

/**
 * Public functions implementation
 **/

TreeNodePtr getSyntaxTree() {
    Stack *stack = getStack();

    if (stack->size > 1) {
        fprintf(stderr, "Stack should have only one element which is the syntax tree root, but it has %d elements", stack->size);
        exit(EXIT_FAILURE);
    }

    TreeNodePtr syntaxTree = (TreeNodePtr) pop(stack);

    free(stack);

    return syntaxTree;
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