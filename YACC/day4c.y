%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s) {
    printf("ERROR: %s\n", s);
}
%}

%token NUM

%left '+' '-'
%left '*' '/'
%left UMINUS

%%

input:
      /* empty */
    | input line
    ;

line:
      expr '\n'      { printf("= %d\n", $1); }
    | '\n'
    ;

expr:
      expr '+' expr  { $$ = $1 + $3; }
    | expr '-' expr  { $$ = $1 - $3; }
    | expr '*' expr  { $$ = $1 * $3; }
    | expr '/' expr  { $$ = $1 / $3; }
    | '-' expr %prec UMINUS  { $$ = -$2; }
    | '(' expr ')'   { $$ = $2; }
    | NUM            { $$ = $1; }
    ;
%%
int main(void) {
    printf("Joseph R Vayalat\n");
    printf("Enter Input:\n");
    yyparse();
    return 0;
}

