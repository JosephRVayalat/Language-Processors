%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token IF ELSE ID NUMBER RELOP

%nonassoc IFX
%nonassoc ELSE

%%

stmt:
      IF '(' cond ')' stmt            %prec IFX  
    | IF '(' cond ')' stmt ELSE stmt  
    | ID ';'                          
    ;

cond:
      ID RELOP ID
    | ID RELOP NUMBER
    ;

%%
void yyerror(const char *s)
{
    printf("Error: %s\n", s);
    exit(1);
}

int main()
{
    printf("Joseph R Vayalat\n");
    printf("Enter if-else statement:\n");
    yyparse();
    printf("Valid if-else statement\n");
    return 0;
}
