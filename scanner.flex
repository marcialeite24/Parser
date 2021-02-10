%{
// HEADERS
#include <stdlib.h>
#include <string.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

"+" { return PLUS; }
"-" { return SUB; }
"/" { return DIV; }
"*" { return MULT; }
"%" { return MOD; }
"=" { return IGUAL; }

">" { return GT; }
">=" { return GTEQ; }
"<" { return LT; }
"<=" { return LTEQ; }
"==" { return EQUAL; }
"!=" { return NOT_EQUAL; }
"true" { return TRUE; }
"false" { return FALSE; }
"&&" { return AND; }
"||" { return OR; }

"if" { return IF_CMD; }
"else" { return ELSE_CMD; }
"let" { return LET_CMD; }
"while" { return WHILE_CMD; }
"println!" { return PRINTLN_CMD; }
"read_line" { return READ_LINE_CMD; }

"fn" { return FN; }
"main" { return MAIN; }

"{" { return CHAVETA1; }
"}" { return CHAVETA2; }
"(" { return PARENTESE1; }
")" { return PARENTESE2; }
";" { return PVIRGULA; }
"," { return VIRGULA; }
"'" { return PELICAS; }
"\"" { return ASPAS; }
"&" { return ECOM; }

\-?[0-9]+ {
   yylval.intValue = atoi(yytext);
   return INT;
}

\-?[a-zA-Z]+[_0-9]*[_a-zA-Z0-9]* {
   yylval.charValue = strdup(yytext);
   return VAR;
}

\".*\" {
	yylval.charValue = strdup(yytext);
	return STRING;
}

.  { yyerror("unexpected character"); }
%%
