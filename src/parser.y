%{

#include "tree_builder.h"
#include<stdio.h>

/* FLEX functions */
extern int yylex (void);
void yyerror(char *);
char *tokenValue;

%}

%{ /* Comparison operators */ %}
%token EQUAL
%token DIFFERENT
%token LESS
%token LESS_OR_EQUAL
%token GREATER
%token GREATER_OR_EQUAL

%{ /* Integer Operations */ %}
%token PLUS
%token MINUS
%token MULTIPLY
%token DIV

%{ /* Boolean Operations */ %}
%token OR
%token AND
%token NOT

%{ /* Ponctuation */ %}
%token OPEN_BRACE
%token CLOSE_BRACE
%token OPEN_BRACKET
%token CLOSE_BRACKET
%token OPEN_PAREN
%token CLOSE_PAREN
%token COLON
%token COMMA
%token SEMI_COLON

%{ /* Assignment */ %}
%token ASSIGN

%{ /* Reserved words */ %}
%token ELSE
%token FUNCTIONS
%token GOTO
%token IF
%token LABELS
%token RETURN
%token TYPES
%token VAR
%token VARS
%token VOID
%token WHILE

%{ /* End of file */ %}
%token END_OF_FILE

%{ /* Integers */ %}
%token INTEGER

%{ /* Identifiers */ %}
%token IDENTIFIER

%{ /* Lexical error */ %}
%token LEXICAL_ERROR

%%
program                     : function END_OF_FILE {return 0;}
                            ;

function                    : function_header block { addFunction(); }
                            ;


function_header             : function_return_type identifier formal_parameters { addFunctionHeader(); }
                            ;
function_return_type        : VOID { addEmpty(); }
                            | identifier
                            ;
formal_parameters           : OPEN_PAREN CLOSE_PAREN { addEmpty(); }
                            | OPEN_PAREN formal_parameter_list CLOSE_PAREN
                            ;
formal_parameter_list       : formal_parameter
                            | formal_parameter COMMA formal_parameter_list { addSequence(); }
                            ;
formal_parameter            : expression_parameter
                            | function_parameter
                            ;
expression_parameter        : VAR identifier_list COLON identifier { addExpressionParameter(); }
                            | identifier_list COLON identifier { addExpressionParameter(); }
                            ;
function_parameter          : function_header { addFunctionParameter(); }
                            ;


block                       : labels_section types_section variables_section functions_section body { addBlock(); }
                            ;

labels_section              : { addEmpty(); }
                            | labels
                            ;
labels                      : LABELS identifier_list SEMI_COLON { addLabels(); }
                            ;

types_section               : { addEmpty(); }
                            | types
                            ;
types                       : TYPES type_declaration_list { addTypes(); }
                            ;
type_declaration_list       : type_declaration
                            | type_declaration type_declaration_list { addSequence(); }
                            ;
type_declaration            : identifier ASSIGN type SEMI_COLON { addTypeDeclaration(); }
                            ;

variables_section           : { addEmpty(); }
                            | variables
                            ;
variables                   : VARS declarations_list { addVariables(); }
                            ;
declarations_list           : declaration SEMI_COLON
                            | declaration SEMI_COLON declarations_list { addSequence(); }
                            ;
declaration                 : identifier_list COLON type { addDeclaration(); }
                            ;

functions_section           : { addEmpty(); }
                            | functions
                            ;
functions                   : FUNCTIONS functions_list { addFunctions(); }
                            ;
functions_list              : function
                            | function functions_list { addSequence(); }
                            ;


identifier_list             : identifier
                            | identifier COMMA identifier_list { addSequence(); }
                            ;
identifier                  : IDENTIFIER { addIdentifier(tokenValue); }
                            ;


type                        : identifier array_size_declaration_list { addType(); }
                            ;
array_size_declaration_list : { addEmpty(); }
                            | array_size_declaration array_size_declaration_list { addSequence(); }
                            ;
array_size_declaration      : OPEN_BRACKET integer CLOSE_BRACKET
                            ;


body                        : OPEN_BRACE statement_list CLOSE_BRACE { addBody(); }
                            ;
statement_list              : { addEmpty(); }
                            | statement statement_list { addSequence(); }
                            ;
statement                   : label unlabeled_statement { addStatement(); }
                            | unlabeled_statement { addUnlabeledStatement(); }
                            ;
label                       : identifier COLON { addLabel(); }
                            ;
unlabeled_statement         : assignment
                            | function_call_statement
                            | goto
                            | return
                            | conditional
                            | repetitive
                            | compound
                            | empty_statement
                            ;

assignment                  : variable ASSIGN expression SEMI_COLON { addAssignment(); }
                            ;
variable                    : identifier array_index_list { addVariable(); }
                            ;
array_index_list            : { addEmpty(); }
                            | array_index array_index_list { addSequence(); }
                            ;
array_index                 : OPEN_BRACKET expression CLOSE_BRACKET
                            ;

function_call_statement     : function_call SEMI_COLON
                            ;
function_call               : identifier OPEN_PAREN expression_list CLOSE_PAREN { addFunctionCall(); }
expression_list             : { addEmpty(); }
                            | expression
                            | expression COMMA expression_list { addSequence(); }
                            ;

goto                        : GOTO identifier SEMI_COLON { addGoto(); }
                            ;

return                      : RETURN SEMI_COLON { addEmpty(); addReturn(); }
                            | RETURN expression SEMI_COLON { addReturn(); }
                            ;

conditional                 : IF OPEN_PAREN expression CLOSE_PAREN compound { addEmpty(); addIf(); }
                            | IF OPEN_PAREN expression CLOSE_PAREN compound ELSE compound { addIf(); }
                            ;

repetitive                  : WHILE OPEN_PAREN expression CLOSE_PAREN compound { addWhile(); }
                            ;

compound                    : OPEN_BRACE unlabeled_statement_list CLOSE_BRACE
                            ;
unlabeled_statement_list    : { addEmpty(); }
                            | unlabeled_statement unlabeled_statement_list { addSequence(); }
                            ;

empty_statement             : SEMI_COLON { addEmpty(); }

expression                  : term
                            | unop_expression
                            | binary_expression
                            | boolean_expression
                            ;
boolean_expression          : expression relational_operator expression  { addBooleanExpression(); }
                            ;
binary_expression           : term additive_operator term  { addBinaryExpression(); }
                            ;
unop_expression             : unary_operator expression { addUnaryExpression(); }
                            ;

term                        : term multiplicative_operator term { addTerm(); }
                            | factor { addEmpty(); addEmpty(); addTerm(); }
                            ;

factor                      : variable { addFactor(); }
                            | integer { addFactor(); }
                            | function_call { addFactor(); }
                            | OPEN_PAREN expression CLOSE_PAREN { addFactor(); }
                            ;


integer                     : INTEGER { addInteger(tokenValue); }
                            ;


relational_operator         : LESS_OR_EQUAL { addRelationalOperator(tokenValue); }
                            | LESS { addRelationalOperator(tokenValue); }
                            | EQUAL { addRelationalOperator(tokenValue); }
                            | DIFFERENT { addRelationalOperator(tokenValue); }
                            | GREATER_OR_EQUAL { addRelationalOperator(tokenValue); }
                            | GREATER { addRelationalOperator(tokenValue); }
                            ;
additive_operator           : PLUS { addAdditiveOperator(tokenValue); }
                            | MINUS { addAdditiveOperator(tokenValue); }
                            | OR { addAdditiveOperator(tokenValue); }
                            ;
unary_operator              : PLUS { addUnaryOperator(tokenValue); }
                            | MINUS { addUnaryOperator(tokenValue); }
                            | NOT { addUnaryOperator(tokenValue); }
                            ;
multiplicative_operator     : MULTIPLY { addMultiplicativeOperator(tokenValue); }
                            | DIV { addMultiplicativeOperator(tokenValue); }
                            | AND { addMultiplicativeOperator(tokenValue); }
                            ;
%%
