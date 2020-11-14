#include "stack.h"

#define MAX_CHILD_NODES 5

typedef enum {
    FUNCTION_NODE = 1,

    FUNCTION_HEADER_NODE,
    EXPRESSION_PARAMETER_BY_REFERENCE_NODE,
    EXPRESSION_PARAMETER_BY_VALUE_NODE,
    FUNCTION_PARAMETER_NODE,

    BLOCK_NODE,
    LABELS_NODE,
    TYPES_NODE,
    VARIABLES_NODE,
    FUNCTIONS_NODE,
    BODY_NODE,

    TYPE_DECLARATION_NODE,
    DECLARATION_NODE,
    TYPE_NODE,
    ARRAY_SIZE_NODE,

    STATEMENT_NODE,
    LABEL_NODE,

    ASSIGNMENT_NODE,
    VARIABLE_NODE,
    ARRAY_INDEX_NODE,

    FUNCTION_CALL_NODE,

    GOTO_NODE,

    RETURN_NODE,

    IF_NODE,

    WHILE_NODE,

    COMPOUND_NODE,

    EXPRESSION_NODE,
    BINARY_OPERATOR_EXPRESSION_NODE,
    UNARY_OPERATOR_EXPRESSION_NODE,
    ADDITIVE_OPERATION_NODE,
    TERM_NODE,
    MULTIPLICATIVE_OPERATION_NODE,
    FACTOR_NODE,

    INTEGER_NODE,
    IDENTIFIER_NODE,

    RELATIONAL_OPERATOR_NODE,
    ADDITIVE_OPERATOR_NODE,
    UNARY_OPERATOR_NODE,
    MULTIPLICATIVE_OPERATOR_NODE
} NodeCategory;

typedef struct _treeNode {
    NodeCategory category;
    char *name;
    struct _treeNode *next;
    struct _treeNode *subtrees[MAX_CHILD_NODES];
} TreeNode, *TreeNodePtr;

/**
 * Stack
 **/
TreeNodePtr getSyntaxTree();

/**
 * Tree generation
 **/
void addSequence();

void addEmpty();

void addFunction();

void addFunctionHeader();
void addExpressionParameterByReference();
void addExpressionParameterByValue();
void addFunctionParameter();

void addBlock();
void addLabels();
void addTypes();
void addVariables();
void addFunctions();
void addBody();

void addTypeDeclaration();
void addDeclaration();

void addIdentifier(char *tokenValue);

void addType();
void addArraySize();

void addStatement();
void addUnlabeledStatement();

void addLabel();

void addAssignment();

void addVariable();
void addArrayIndex();

void addFunctionCall();

void addGoto();
void addReturn();
void addIf();
void addWhile();

void addCompound();

void addExpression();
void addBinaryOperatorExpression();
void addUnaryOperatorExpression();
void addAdditiveOperation();
void addTerm();
void addMultiplicativeOperation();
void addFactor();

void addInteger(char *tokenValue);

void addRelationalOperator(char *tokenValue);
void addAdditiveOperator(char *tokenValue);
void addUnaryOperator(char *tokenValue);
void addMultiplicativeOperator(char *tokenValue);