#include "tree_visualizer.h"
#include <stdio.h>

typedef enum {false, true} bool;

void dumpSyntaxTree(TreeNodePtr node, int indent, bool isNext);
const char *getCategoryName(NodeCategory category);
void addIndent(int indent);

void dumpTree(void *root) {
    TreeNodePtr tree = (TreeNodePtr) root;
    dumpSyntaxTree(tree, 0, false);
}

void dumpSyntaxTree(TreeNodePtr node, int indent, bool isNext) {
    if(node == NULL) {
        return;
    }

    addIndent(indent);
    if(isNext) {
        printf("|-> ");
    }

    if(node->name == NULL) {
        printf("%s\n", getCategoryName(node->category));
    } else {
        printf("%s(%s)\n", getCategoryName(node->category), node->name);
    }

    for (int i = MAX_CHILD_NODES-1; i >= 0; i--) {
        TreeNodePtr subtree = node->subtrees[i];
        dumpSyntaxTree(subtree, indent + 1, false);
    }

    dumpSyntaxTree(node->next, indent, true);

}

void addIndent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("\t");
    }
}

const char *getCategoryName(NodeCategory category) {
    switch (category) {
        case FUNCTION_NODE:
            return "FUNCTION";

        case FUNCTION_HEADER_NODE:
            return "FUNCTION_HEADER";
        case EXPRESSION_PARAMETER_BY_REFERENCE_NODE:
            return "EXPRESSION_PARAMETER_BY_REFERENCE";
        case EXPRESSION_PARAMETER_BY_VALUE_NODE:
            return "EXPRESSION_PARAMETER_BY_VALUE";
        case FUNCTION_PARAMETER_NODE:
            return "FUNCTION_PARAMETER";

        case BLOCK_NODE:
            return "BLOCK";
        case LABELS_NODE:
            return "LABELS";
        case TYPES_NODE:
            return "TYPES";
        case VARIABLES_NODE:
            return "VARIABLES";
        case FUNCTIONS_NODE:
            return "FUNCTIONS";
        case BODY_NODE:
            return "BODY";

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
        case BOOLEAN_EXPRESSION_NODE:
            return "BOOLEAN_EXPRESSION";
        case BINARY_EXPRESSION_NODE:
            return "BINARY_EXPRESSION";
        case UNARY_EXPRESSION_NODE:
            return "UNARY_OPERATOR_EXPRESSION";
        case TERM_NODE:
            return "TERM";
        case FACTOR_NODE:
            return "FACTOR";

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