%{
#include "Token.h"
#include <fstream>
#include <iostream>
int token;

%}
%option yylineno
%%
[ \t]+ /*Skip spaces and tabs*/
\/\*[\s\S]*?\*\/|\/\/.* /*Skip comments*/

-> token = tok_return_type; return token;
fun token = tok_fun; return token;
func token = tok_fun; return token;
extern token = tok_extern; return token;
return token = tok_extern; return token;
[a-zA-Z][a-zA-Z0-9]* token = tok_identifier; return token;
[1-9][0-9.]* token = tok_number; return token;
0b[01]* token = tok_number; return token;
0x[1-9a-fA-F][0-9a-fA-F]* token = tok_number; return token;
0[1-7][0-7]* token = tok_number; return token;

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
<<EOF>> {token = tok_eof; return token;}
%%

int yyFlexLexer::yywrap(){return 1;}

int main(int argc, char **argv)
{
    std::ifstream infile(argv[1]);
    FlexLexer* lexer = new yyFlexLexer(infile,std::cerr);
    int tokenid;
    Token token;
    while ((tokenid = lexer->yylex()) != tok_eof)
    {
        token.type = TokenType(tokenid);
        switch (token.type){
        tok_fun:
        tok_extern:
        tok_return:
        tok_return_type:
        tok_eof:    break;
        default:
            token.tokenValue = lexer->YYText();
        }
        std::cout << token.dump() << std::endl;
    } 
}