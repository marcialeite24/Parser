#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

// Declaração das funções
void aritmeticPrint(ExprArit* aritm, int tabs);
void booleanPrint(ExprBool* boolean, int tabs);
void comandPrint(Comand* cmd, int tabs);
void listaCmdPrint(Cmd_List* cmdlist, int tabs);

// Imprimir Espaços
void printSpaces(int n) {
  for(int i = 0; i < n; i++)
    printf(" ");
}

// Imprimir as Expressões Aritméticas
void aritmeticPrint(ExprArit* aritm, int tabs){
  //print das expressoes aritmeticas
  if(aritm != 0) {
    switch (aritm -> kind) {
      case E_INTEGER:
      printSpaces(tabs);
      printf("%d\n", aritm -> attr.value);
      break;
      case E_VARIABLE:
      printSpaces(tabs);
      printf("%s\n", strdup(aritm -> attr.var));
      break;
      case E_OPERATION:
      switch (aritm -> attr.op.operator) {
        case PLUS:
        printSpaces(tabs);
        printf("+\n");
        break;
        case SUB:
        printSpaces(tabs);
        printf("-\n");
        break;
        case MULT:
        printSpaces(tabs);
        printf("*\n");
        break;
        case DIV:
        printSpaces(tabs);
        printf("/\n");
        break;
        case MOD:
        printSpaces(tabs);
        printf("%%\n");
        break;
        default:
        yyerror("Unknown operator!\n");
      }
      aritmeticPrint(aritm -> attr.op.left, tabs+2);
      aritmeticPrint(aritm -> attr.op.right, tabs+2);
      break;
      case E_PARENTESIS:
      printSpaces(tabs);
      printf("(\n");
      aritmeticPrint(aritm -> attr.insideP.insideParentesis, tabs+2);
      printSpaces(tabs);
      printf(")\n");
      break;
      default:
      break;
    }
  }
}

// Imprimir as Expressões Booleanas
void booleanPrint(ExprBool* boolean, int tabs){
  //print das expressoes booleanas
  if(boolean != 0) {
    switch (boolean -> kind) {
    case E_BOOL:
    printSpaces(tabs);
    printf("%d\n", boolean -> attr.value);
    break;
    case E_OP:
    switch (boolean -> attr.opBool.operator) {
      case GT:
      printSpaces(tabs);
      printf(">\n");
      break;
      case LT:
      printSpaces(tabs);
      printf("<\n");
      break;
      case GTEQ:
      printSpaces(tabs);
      printf(">=\n");
      break;
      case LTEQ:
      printSpaces(tabs);
      printf("<=\n");
      break;
      case EQUAL:
      printSpaces(tabs);
      printf("==\n");
      break;
      case NOT_EQUAL:
      printSpaces(tabs);
      printf("!=\n");
      break;
      case AND:
      printSpaces(tabs);
      printf("&&\n");
      break;
      case OR:
      printSpaces(tabs);
      printf("||\n");
      break;
      default:
      yyerror("Unknown operator!\n");
    }
    aritmeticPrint(boolean -> attr.opBool.left, tabs+2);
    aritmeticPrint(boolean -> attr.opBool.right, tabs+2);
    break;
    case E_LOGICA:
    switch (boolean -> attr.logBool.p_logica) {
      case AND:
      printSpaces(tabs);
      printf("&&\n");
      break;
      case OR:
      printSpaces(tabs);
      printf("||\n");
      break;
      default:
      yyerror("Unknown operator!\n");
    }
    booleanPrint(boolean -> attr.logBool.leftLOG, tabs+2);
    booleanPrint(boolean -> attr.logBool.rightLOG, tabs+2);
    break;
    default:
    break;
  }
  }
}

// Imprimir os Comandos
void comandPrint(Comand* cmd, int tabs){
  //print dos comandos
  if(cmd != 0) {
    switch (cmd -> kind) {
    case IF:
    printSpaces(tabs);
    printf("if\n");
    booleanPrint(cmd -> attr.cmdIF.condicao_IF, tabs+2);
    listaCmdPrint(cmd -> attr.cmdIF.listC_IF, tabs+2);
    break;
    case IF_THEN_ELSE:
    printSpaces(tabs);
    printf("if\n");
    booleanPrint(cmd -> attr. cmdIF_THEN_ELSE.condicao_IF_THEN, tabs+2);
    listaCmdPrint(cmd -> attr. cmdIF_THEN_ELSE.listC_IF_THEN, tabs+2);
    printSpaces(tabs);
    printf("else\n");
    listaCmdPrint(cmd -> attr. cmdIF_THEN_ELSE.listC_ELSE, tabs+2);
    break;
    case LET1:
    printSpaces(tabs);
    printf("let\n");
    printSpaces(tabs+2);
    printf("=\n");
    printSpaces(tabs+4);
    printf("%s\n", cmd -> attr.cmdLET1.var);
    printSpaces(tabs+4);
    printf("%d\n", cmd -> attr.cmdLET1.num);
    break;
    case LET2:
    printSpaces(tabs);
    printf("let\n");
    printSpaces(tabs+2);
    printf("=\n");
    printSpaces(tabs+4);
    printf("%s\n", cmd -> attr.cmdLET2.var);
    aritmeticPrint(cmd -> attr.cmdLET2.var_data, tabs+4);
    break;
    case WHILE:
    printSpaces(tabs);
    printf("while\n");
    booleanPrint(cmd -> attr.cmdWHILE.condicao_WHILE, tabs+2);
    listaCmdPrint(cmd -> attr.cmdWHILE.listC_WHILE, tabs+2);
    break;
    case PRINTLN1:
    printSpaces(tabs);
    printf("println!()\n");
    printSpaces(tabs+2);
    printf("%s\n", strdup(cmd -> attr.cmdPRINTLN1.str));
    break;
    case PRINTLN2:
    printSpaces(tabs);
    printf("println!()\n");
    printSpaces(tabs+2);
    printf("%s\n", strdup(cmd -> attr.cmdPRINTLN2.str));
    printSpaces(tabs+2);
    printf("%s\n", strdup(cmd -> attr.cmdPRINTLN2.var));
    break;
    case READ_LINE:
    printSpaces(tabs);
    printf("read_line()\n");
    printSpaces(tabs+2);
    printf("%s\n", strdup(cmd -> attr.cmdREAD_LINE.str));
    break;
    default:
    yyerror("Unknown operator!\n");
  }
  }
}

// Imprimir a Lista de Comandos
void listaCmdPrint(Cmd_List* cmdlist, int tabs){
  //percorrer lista e chamar funcao print comando
  if(cmdlist != NULL) {
    comandPrint(cmdlist -> cmd, tabs);
    listaCmdPrint(cmdlist -> next, tabs);
  }
}

// Função Main
int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  }
  if (yyparse() == 0) {
    int tabs = 2;
    printf("root\n");
    printSpaces(tabs);
    printf("fn main()\n");
    listaCmdPrint(root, tabs+2);
  }
  return 0;
}
