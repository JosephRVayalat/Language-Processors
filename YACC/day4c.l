%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+          { yylval = atoi(yytext); return NUM; }
[ \t]           { /* skip spaces and tabs */ }
\n              { return '\n'; }
[()+\-*/]       { return yytext[0]; }
.               { /* ignore anything else */ }
%%
int yywrap(void) { return 1; }

