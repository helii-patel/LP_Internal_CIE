%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

extern FILE *yyout;

static char current_type[32] = "id"; // track latest declared type for symbol table
%}

digit      [0-9]
letter     [a-zA-Z]

%%

"int"|"float"|"char"   {
    strncpy(current_type, yytext, sizeof(current_type)-1);
    current_type[sizeof(current_type)-1] = '\0';
    return TYPE;
}

{letter}({letter}|{digit})*  {
    insert_symbol(yytext, current_type);
    fprintf(yyout, "IDENTIFIER: %s\n", yytext);
    return ID;
}

{digit}+   {
    fprintf(yyout, "CONSTANT: %s\n", yytext);
    return NUM;
}

"+"|"-"|"*"|"/"|"="   {
    fprintf(yyout, "OPERATOR: %s\n", yytext);
    return *yytext;
}

"\n" {
    strcpy(current_type, "id");
    return EOL;
}

[ \t\r]+   ;
. {
    printf("Lexical Error: Invalid token %s\n", yytext);
}

%%

int yywrap() {
    return 1;
}