// Tokens
%token
  INT
  VAR
  STRING
  PLUS
  SUB
  DIV
  MULT
  MOD
  IGUAL

  GT
  GTEQ
  LT
  LTEQ
  EQUAL
  NOT_EQUAL
  TRUE
  FALSE
  AND
  OR

  IF_CMD
  ELSE_CMD
  LET_CMD
  WHILE_CMD
  PRINTLN_CMD
  READ_LINE_CMD

  FN
  MAIN

  CHAVETA1
  CHAVETA2
  PARENTESE1
  PARENTESE2
  PVIRGULA
  VIRGULA
  ASPAS
  PELICAS
  ECOM

// Operator associativity & precedence
%left PLUS
%left SUB
%left DIV
%left MULT
%left MOD

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  ExprArit* exprValue;
  char* charValue;
  ExprBool* boolValue;
  Comand* cmdValue;
  Cmd_List* cmdListValue;
}

%type <intValue> INT
%type <exprValue> expr
%type <charValue> VAR
%type <charValue> STRING
%type <boolValue> boolean
%type <cmdValue> comand
%type <cmdListValue> cmdList

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
  #include <stdio.h>
  #include <stdlib.h>
  #include "TP1.h"

  extern int yylex();
  extern int yyline;
  extern char* yytext;
  extern FILE* yyin;
  extern void yyerror(const char* msg);
  Cmd_List* root;
}

%%
program: FN MAIN PARENTESE1 PARENTESE2 CHAVETA1 cmdList CHAVETA2 { root=$6; }

expr:
  INT {
    $$ = expArit_Integer($1);
  }
  |
  VAR {
    $$ = expArit_Variable($1);
  }
  |
  expr PLUS expr {
    $$ = expArit_Operation(PLUS, $1, $3);
  }
  |
  expr SUB expr {
    $$ = expArit_Operation(SUB, $1, $3);
  }
  |
  expr DIV expr {
    $$ = expArit_Operation(DIV, $1, $3);
  }
  |
  expr MULT expr {
    $$ = expArit_Operation(MULT, $1, $3);
  }
  |
  expr MOD expr {
    $$ = expArit_Operation(MOD, $1, $3);
  }
  |
  PARENTESE1 expr PARENTESE2 {
    $$ = expArit_Parentesis($2);
  }
  ;

boolean:
  expr GT expr {
    $$ = expBool_Operation(GT,$1,$3);
  }
  |
  expr GTEQ expr {
    $$ = expBool_Operation(GTEQ,$1,$3);
  }
  |
  expr LT expr {
    $$ = expBool_Operation(LT,$1,$3);
  }
  |
  expr LTEQ expr {
    $$ = expBool_Operation(LTEQ,$1,$3);
  }
  |
  expr EQUAL expr {
    $$ = expBool_Operation(EQUAL,$1,$3);
  }
  |
  expr NOT_EQUAL expr {
    $$ = expBool_Operation(NOT_EQUAL,$1,$3);
  }
  ;

comand:
  IF_CMD boolean CHAVETA1 cmdList CHAVETA2 {
    $$ = comand_IF(IF_CMD, $2, $4);
  }
  |
  IF_CMD boolean CHAVETA1 cmdList CHAVETA2 ELSE_CMD CHAVETA1 cmdList CHAVETA2 {
    $$ = comand_IF_THEN_ELSE(ELSE_CMD, $2, $4, $8);
  }
  |
  LET_CMD VAR IGUAL INT PVIRGULA{
    $$ = comand_LET1(LET_CMD, $2, $4);
  }
  |
  LET_CMD VAR IGUAL expr PVIRGULA{
    $$ = comand_LET2(LET_CMD, $2, $4);
  }
  |
  WHILE_CMD boolean CHAVETA1 cmdList CHAVETA2 {
    $$ = comand_WHILE(WHILE_CMD, $2, $4);
  }
  |
  PRINTLN_CMD PARENTESE1 STRING PARENTESE2 PVIRGULA{
    $$ = comand_PRINTLN1(PRINTLN_CMD, $3);
  }
  |
  PRINTLN_CMD PARENTESE1 STRING VIRGULA VAR PARENTESE2 PVIRGULA{
    $$ = comand_PRINTLN2(PRINTLN_CMD, $3, $5);
  }
  |
  READ_LINE_CMD PARENTESE1 ECOM VAR PARENTESE2 PVIRGULA{
    $$ = comand_READ_LINE(READ_LINE_CMD, $4);
  }
  ;

cmdList:
  {
    $$ = NULL;
  }
  |
  comand cmdList {
    $$ = mkListC($1,$2);
  }
  ;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
