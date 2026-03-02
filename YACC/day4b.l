%{
#include "y.tab.h"
%}

%%
"if"        { return IF; }
"else"      { return ELSE; }
[><=!]=?    { return RELOP; }
[0-9]+      { return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }
[();]       { return yytext[0]; }
[ \t\n]     ;
.           { return yytext[0]; }
%%

int yywrap()
{
    return 1;
}
