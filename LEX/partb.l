%{
#include <stdio.h>

int vowels = 0, consonants = 0, digits = 0, special = 0;
%}

%%
[aeiouAEIOU]      { vowels++; }
[a-zA-Z]          { consonants++; }
[0-9]             { digits++; }
[^a-zA-Z0-9 \t\n] { special++; }
[ \t\n]           ;  
%%

int main() {
    yylex();
    printf("Joseph R Vayalat\n\n");
    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", special);
    return 0;
}

int yywrap() {
    return 1;
}
