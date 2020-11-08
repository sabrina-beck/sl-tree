#include "tree_visualizer.h"

const char *getCategoryName(NodeCategory category);

void dumpTree(void *p, int indent) {
    // TODO
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