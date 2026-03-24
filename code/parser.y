%start start
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char *s);

int tempCount = 0;
FILE *tacFile;

char* newTemp() {
    char *temp = (char*)malloc(10);
    sprintf(temp, "t%d", tempCount++);
    return temp;
}
%}

%union {
    char* str;
}

%token <str> ID NUM
%token TYPE
%token EOL

%type <str> expr

%left '+' '-'
%left '*' '/'

%%
start:
    stmts
    ;

stmts:
    stmts stmt
    | stmt
    ;

stmt:
    ID '=' expr EOL {
        fprintf(tacFile, "%s = %s\n", $1, $3);
    }
    | ID '=' expr {
        fprintf(tacFile, "%s = %s\n", $1, $3);
    }
    | EOL { /* skip empty line */ }
    ;

expr:
    expr '+' expr {
        char* temp = newTemp();
        fprintf(tacFile, "%s = %s + %s\n", temp, $1, $3);
        $$ = temp;
    }
    | expr '-' expr {
        char* temp = newTemp();
        fprintf(tacFile, "%s = %s - %s\n", temp, $1, $3);
        $$ = temp;
    }
    | expr '*' expr {
        char* temp = newTemp();
        fprintf(tacFile, "%s = %s * %s\n", temp, $1, $3);
        $$ = temp;
    }
    | expr '/' expr {
        char* temp = newTemp();
        fprintf(tacFile, "%s = %s / %s\n", temp, $1, $3);
        $$ = temp;
    }
    | ID { $$ = $1; }
    | NUM { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    printf("Syntax Error: %s\n", s);
}