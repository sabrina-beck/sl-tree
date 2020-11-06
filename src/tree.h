
#define MAX_CHILD_NODES 3

typedef enum {
    FUNCTION = 1,
    BLOCK,
    TYPE,

    BINARY_EXPRESSION,
    UNARY_EXPRESSION,

    ASSIGNMENT,
    WHILE,
    IF_ELSE,

    FUNCTION_CALL,
    IDENTIFIER,
    INTEGER,
    OPERATOR
    //TODO
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