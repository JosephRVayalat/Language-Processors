%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+        { yylval = atoi(yytext); return NUM; }
[ \t]         { /* skip */ }
\n            { return '\n'; }
[()+\-*/]     { return yytext[0]; }
.             { /* ignore */ }
%%
int yywrap(void) { return 1; }

