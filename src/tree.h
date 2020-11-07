
#define MAX_CHILD_NODES 5

typedef enum {
    FUNCTION_NODE = 1,

    FUNCTION_HEADER_NODE,
    EXPRESSION_PARAMETER_NODE,

    BLOCK_NODE,

    TYPE_DECLARATION_NODE,
    DECLARATION_NODE,
    TYPE_NODE,

    STATEMENT_NODE,
    LABEL_NODE,

    ASSIGNMENT_NODE,
    VARIABLE_NODE,

    FUNCTION_CALL_NODE,

    GOTO_NODE,

    RETURN_NODE,

    IF_NODE,

    WHILE_NODE,

    EXPRESSION_NODE,
    SIMPLE_EXPRESSION_NODE,
    UNARY_OPERATOR_EXPRESSION_NODE,
    ADDITION_SEQUENCE_NODE,
    TERM_NODE,
    MULTIPLICATIVE_SEQUENCE_NODE,

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

void *getTree();  // returns any pointer

void counts(void *p, int *functions, int *funcalls, int *whiles, int *ifs, int *bin);

void dumpTree(TreeNodePtr p, int indent);

/**
 * Tree generation
 **/
void addSequence();

void addFunction();
void addFunctionHeader();
void addExpressionParameter();
void addBlock();
void addTypeDeclaration();
void addDeclaration();
void addIdentifier(char *tokenValue);
void addType();
void addStatement();
void addUnlabeledStatement();
void addLabel();
void addAssignment();
void addVariable();
void addFunctionCall();
void addGoto();
void addReturn();
void addIf();
void addWhile();
void addExpression();
void addSimpleExpression();
void addUnaryOperatorExpression();
void addAdditionSequence();
void addTerm();
void addMultiplicativeSequence();
void addInteger(char *tokenValue);
void addRelationalOperator(char *tokenValue);
void addAdditiveOperator(char *tokenValue);
void addUnaryOperator(char *tokenValue);
void addMultiplicativeOperator(char *tokenValue);
void addEmpty();
