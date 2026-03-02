%{
#include <stdio.h>
%}

%%
[0-9]+\.[0-9]+    { printf("Floating point number: %s\n", yytext); }
[0-9]+            { printf("Integer: %s\n", yytext); }
[\+\-\*/%]        { printf("Arithmetic Operator: %s\n", yytext); }
[ \t\n]+          ;   
.                 ;   
%%

int main() {
    yylex();
    printf("\n\nJoseph R Vayalat\n\n");
    return 0;
}

int yywrap() {
    return 1;
}
