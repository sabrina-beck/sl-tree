
typedef enum {
    FUNCTION = 1,
    BLOCK,
    TYPE,

    BINARY_EXPRESSION,
    UNARY_EXPRESSION,

    ASSIGNMENT,
    WHILE,

    FUNCTION_CALL,
    IDENTIFIER,
    INTEGER,
    OPERATOR
    //TODO
} NodeCategory;

typedef struct _treeNode {
    NodeCategory category;
    struct _treeNode *next;
    struct _treeNode *subtrees;
    char *name;
} TreeNode, *TreeNodePtr;

void *getTree();  // returns any pointer

void counts(void *p, int *functions, int *funcalls, int *whiles, int *ifs, int *bin);

void dumpTree(TreeNodePtr p, int indent);