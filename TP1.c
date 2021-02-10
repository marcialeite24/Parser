#include <stdlib.h>
#include <string.h>
#include "TP1.h"

/* **** EXPRESSÕES ARITMÉTICAS (INTEIROS) **** */

ExprArit* expArit_Integer(int v) {
  ExprArit* expA = (ExprArit*) malloc(sizeof(ExprArit));
  expA -> kind = E_INTEGER;
  expA -> attr.value = v;
  return expA;
}

ExprArit* expArit_Operation(int operator, ExprArit* left, ExprArit* right) {
  ExprArit* expA = (ExprArit*) malloc(sizeof(ExprArit));
  expA -> kind = E_OPERATION;
  expA -> attr.op.operator = operator;
  expA -> attr.op.left = left;
  expA -> attr.op.right = right;
  return expA;
}

ExprArit* expArit_Variable(char* var) {
  ExprArit* expA = (ExprArit*) malloc(sizeof(ExprArit));
  expA -> kind = E_VARIABLE;
  expA -> attr.var = strdup(var);
  return expA;
}

ExprArit* expArit_Parentesis(ExprArit* expr) {
  ExprArit* expA = (ExprArit*) malloc(sizeof(ExprArit));
  expA -> kind = E_PARENTESIS;
  expA -> attr.insideP.insideParentesis = expr;
  return expA;
}

/* **** EXPRESSÕES BOOLEANAS (TRUE/FALSE) **** */

ExprBool* expBool_Value(int v) {
  ExprBool* expB = (ExprBool*) malloc(sizeof(ExprBool));
  expB -> kind = E_BOOL;
  expB -> attr.value = v;
  return expB;
}

ExprBool* expBool_Operation(int operator, ExprArit* left, ExprArit* right) {
  ExprBool* expB = (ExprBool*) malloc(sizeof(ExprBool));
  expB -> kind = E_OP;
  expB -> attr.opBool.operator = operator;
  expB -> attr.opBool.left = left;
  expB -> attr.opBool.right = right;
  return expB;
}

ExprBool* expBool_Logic(int operator, ExprBool* left, ExprBool* right) {
  ExprBool* expB = (ExprBool*) malloc(sizeof(ExprBool));
  expB -> kind = E_LOGICA;
  expB -> attr.logBool.p_logica = operator;
  expB -> attr.logBool.leftLOG = left;
  expB -> attr.logBool.rightLOG = right;
  return expB;
}

/* **** COMANDOS (IF, IF THEN ELSE, LET, WHILE, PRINTLN, READ_LINE) **** */

Comand* comand_IF(int operator, ExprBool* c, Cmd_List* lc) {
  Comand* cmd = (Comand*) malloc(sizeof(Comand));
  cmd -> kind = IF;
  cmd -> attr.cmdIF.operator = operator;
  cmd -> attr.cmdIF.condicao_IF = c;
  cmd -> attr.cmdIF.listC_IF = lc;
  return cmd;
}

Comand* comand_IF_THEN_ELSE(int operator, ExprBool* c, Cmd_List* lc_if, Cmd_List* lc_else) {
  Comand* cmd = (Comand*) malloc(sizeof(Comand));
  cmd -> kind = IF_THEN_ELSE;
  cmd -> attr.cmdIF_THEN_ELSE.operator = operator;
  cmd -> attr.cmdIF_THEN_ELSE.condicao_IF_THEN = c;
  cmd -> attr.cmdIF_THEN_ELSE.listC_IF_THEN = lc_if;
  cmd -> attr.cmdIF_THEN_ELSE.listC_ELSE = lc_else;
  return cmd;
}

Comand* comand_LET1(int operator, char* v, int num) {
  Comand* cmd = (Comand*) malloc(sizeof(Comand));
  cmd -> kind = LET1;
  cmd -> attr.cmdLET1.operator = operator;
  cmd -> attr.cmdLET1.var = strdup(v);
  cmd -> attr.cmdLET1.num = num;
  return cmd;
}

Comand* comand_LET2(int operator, char* v, ExprArit* expA) {
  Comand* cmd = (Comand*) malloc(sizeof(Comand));
  cmd -> kind = LET2;
  cmd -> attr.cmdLET2.operator = operator;
  cmd -> attr.cmdLET2.var = strdup(v);
  cmd -> attr.cmdLET2.var_data = expA;
  return cmd;
}

Comand* comand_WHILE(int operator, ExprBool* c, Cmd_List* lc) {
  Comand* cmd = (Comand*) malloc(sizeof(Comand));
  cmd -> kind = WHILE;
  cmd -> attr.cmdWHILE.operator = operator;
  cmd -> attr.cmdWHILE.condicao_WHILE = c;
  cmd -> attr.cmdWHILE.listC_WHILE = lc;
  return cmd;
}

Comand* comand_PRINTLN1(int operator, char* str) {
  Comand* cmd = (Comand*) malloc(sizeof(Comand));
  cmd -> kind = PRINTLN1;
  cmd -> attr.cmdPRINTLN1.operator = operator;
  cmd -> attr.cmdPRINTLN1.str = strdup(str);
  return cmd;
}

Comand* comand_PRINTLN2(int operator, char* str, char* var) {
  Comand* cmd = (Comand*) malloc(sizeof(Comand));
  cmd -> kind = PRINTLN2;
  cmd -> attr.cmdPRINTLN2.operator = operator;
  cmd -> attr.cmdPRINTLN2.str = strdup(str);
  cmd -> attr.cmdPRINTLN2.var = strdup(var);
  return cmd;
}

Comand* comand_READ_LINE(int operator, char* str) {
  Comand* cmd = (Comand*) malloc(sizeof(Comand));
  cmd -> kind = READ_LINE;
  cmd -> attr.cmdREAD_LINE.operator = operator;
  cmd -> attr.cmdREAD_LINE.str = strdup(str);
  return cmd;
}

/* **** LISTA DE COMANDOS **** */

Cmd_List* mkListC(Comand* cmd, Cmd_List* cmdList) {
  Cmd_List* cl = (Cmd_List*) malloc(sizeof(Cmd_List));
  cl -> cmd = cmd;
  cl -> next = cmdList;
  return cl;
}
