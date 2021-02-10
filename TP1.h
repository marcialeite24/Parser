#ifndef __TP1_h__
#define __TP1_h__

typedef struct _ExprArit ExprArit;
typedef struct _ExprBool ExprBool;
typedef struct _Comand Comand;
typedef struct _Cmd_List Cmd_List;

// Estruturas

/* **** EXPRESSÕES ARITMÉTICAS (INTEIROS) **** */

struct _ExprArit {
  enum {
    E_INTEGER,
    E_OPERATION,
    E_VARIABLE,
    E_PARENTESIS
  } kind;
  union {
    int value;
    char* var;
    struct {
      int operator;
      struct _ExprArit* left;
      struct _ExprArit* right;
    } op;
    struct {
      struct _ExprArit* insideParentesis;
    } insideP;
  } attr;
};

/* **** EXPRESSÕES BOOLEANAS (TRUE/FALSE) **** */

struct _ExprBool {
  enum {
    E_BOOL,
    E_OP,
    E_LOGICA
  } kind;
  union {
    int value;
    struct {
      int operator;
      struct _ExprArit* left;
      struct _ExprArit* right;
    } opBool;
    struct {
      int p_logica;
      struct _ExprBool* leftLOG;
      struct _ExprBool* rightLOG;
    } logBool;
  } attr;
};

/* **** COMANDOS (IF, IF THEN ELSE, LET, WHILE, PRINTLN, READ_LINE) **** */

struct _Comand {
  enum {
    IF,
    IF_THEN_ELSE,
    LET1,
    LET2,
    WHILE,
    PRINTLN1,
    PRINTLN2,
    READ_LINE
  } kind;
  union {
    struct { // 2 campos
      int operator;
      ExprBool* condicao_IF;
      Cmd_List* listC_IF;
    } cmdIF;

    struct { // 3 campos
      int operator;
      ExprBool* condicao_IF_THEN;
      Cmd_List* listC_IF_THEN;
      Cmd_List* listC_ELSE;
    } cmdIF_THEN_ELSE;

    struct { // 2 campos
      int operator;
      char* var;
      int num;
    } cmdLET1;

    struct { // 2 campos
      int operator;
      char* var;
      ExprArit* var_data;
    } cmdLET2;

    struct { // 2 campos
      int operator;
      ExprBool* condicao_WHILE;
      Cmd_List* listC_WHILE;
    } cmdWHILE;

    struct { // 1 campo
      int operator;
      char* str;
    } cmdPRINTLN1;

    struct { // 1 campo
      int operator;
      char* str;
      char* var;
    } cmdPRINTLN2;

    struct { // 1 campo
      int operator;
      char* str;
    } cmdREAD_LINE;
  } attr;
};

/* **** LISTA DE COMANDOS **** */

struct _Cmd_List {
  Comand* cmd;
  struct _Cmd_List* next;
};

// Construtores

/* **** EXPRESSÕES ARITMÉTICAS (INTEIROS) **** */
ExprArit* expArit_Integer(int v);
ExprArit* expArit_Operation(int operator, ExprArit* left, ExprArit* right);
ExprArit* expArit_Variable(char* var);
ExprArit* expArit_Parentesis(ExprArit* expr);

/* **** EXPRESSÕES BOOLEANAS (TRUE/FALSE) **** */
ExprBool* expBool_Value(int v);
ExprBool* expBool_Operation(int operator, ExprArit* left, ExprArit* right);
ExprBool* expBool_Logic(int operator, ExprBool* left, ExprBool* right);

/* **** COMANDOS (IF, IF THEN ELSE, LET, WHILE, PRINTLN, READ_LINE) **** */
Comand* comand_IF(int operator, ExprBool* c, Cmd_List* lc);
Comand* comand_IF_THEN_ELSE(int operator, ExprBool* c, Cmd_List* lc_if, Cmd_List* lc_else);
Comand* comand_LET1(int operator, char* v, int num);
Comand* comand_LET2(int operator, char* v, ExprArit* expA);
Comand* comand_WHILE(int operator, ExprBool* c, Cmd_List* lc);
Comand* comand_PRINTLN1(int operator, char* str);
Comand* comand_PRINTLN2(int operator, char* str, char* var);
Comand* comand_READ_LINE(int operator, char* str);

/* **** LISTA DE COMANDOS **** */
Cmd_List* mkListC(Comand* cmd, Cmd_List* cmdList);

#endif
