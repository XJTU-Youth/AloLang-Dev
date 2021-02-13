%{
#include "Token.h"
#include "Token.h"
// #include <FlexLexer.h>
#include <fstream>
#include <iostream>
int token;

%}
%%
[ \t]+ /*Skip spaces and tabs*/
\/\*[\s\S]*?\*\/|\/\/.* /*Skip comments*/

!  token = tok_syntax; return token;
%  token = tok_syntax; return token;
\^  token = tok_syntax; return token;
&  token = tok_syntax; return token;
\*  token = tok_syntax; return token;
\(  token = tok_syntax; return token;
\)  token = tok_syntax; return token;
\+  token = tok_syntax; return token;
=  token = tok_syntax; return token;
\{  token = tok_syntax; return token;
\}  token = tok_syntax; return token;
\|  token = tok_syntax; return token;
~  token = tok_syntax; return token;
\[  token = tok_syntax; return token;
\]  token = tok_syntax; return token;
\\  token = tok_syntax; return token;
;  token = tok_syntax; return token;
'  token = tok_syntax; return token;
:  token = tok_syntax; return token;
\"  token = tok_syntax; return token;
,  token = tok_syntax; return token;
\<  token = tok_syntax; return token;
\>  token = tok_syntax; return token;
\?  token = tok_syntax; return token;
\.  token = tok_syntax; return token;
\/  token = tok_syntax; return token;
#  token = tok_syntax; return token;

fun token = tok_fun; return token;
func token = tok_fun; return token;
extern token = tok_extern; return token;
return token = tok_extern; return token;
[a-zA-Z][a-zA-Z0-9]* token = tok_identifier; return token;
[1-9][0-9.]* token = tok_number; return token;
0b[01]* token = tok_number; return token;
0x[1-9a-fA-F][0-9a-fA-F]* token = tok_number; return token;
0[1-7][0-7]* token = tok_number; return token;

%%

int yyFlexLexer::yywrap(){return 1;}

int main(int argc, char **argv)
{
    std::ifstream infile(argv[1]);
    FlexLexer* lexer = new yyFlexLexer(infile,std::cerr);
    int token;
    while ((token = lexer->yylex()) != 0)
    {
        std::cout << lexer->YYText() << ": " << token << std::endl;
    }
}