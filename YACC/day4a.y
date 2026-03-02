%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s) { printf("Invalid Input: %s\n", s); }
%}

%token NUM

%left '+' '-'
%left '*' '/'
%left UMINUS

%%
input:
    | input line
    ;

line:
      expr '\n'           { printf("Input Valid\n"); }
    | error '\n'          {}
    | '\n'
    ;

expr:
      expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '-' expr %prec UMINUS
    | '(' expr ')'
    | NUM
    ;
%%


int main(void) {
    printf("Joseph R Vayalat\n\n");
    printf("Enter Input:\n");
    return yyparse();
}

