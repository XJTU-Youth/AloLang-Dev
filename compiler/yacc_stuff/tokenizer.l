%{
#include "Token.h"
#include <fstream>
#include <iostream>
int token;

%}
%option yylineno
%%
[ \t]+ {/*Skip spaces and tabs*/}
\/\*[.\n]*?\*\/|\/\/.* {/*Skip comments*/}

-> token = tok_return_type; return token;
fun token = tok_fun; return token;
func token = tok_fun; return token;
extern token = tok_extern; return token;
return token = tok_extern; return token;
[a-zA-Z][a-zA-Z0-9]* token = tok_identifier; return token;
0b[01]* token = tok_number; return token;
0x[1-9a-fA-F][0-9a-fA-F]* token = tok_number; return token;
0B[01]* token = tok_number; return token;
0X[1-9a-fA-F][0-9a-fA-F]* token = tok_number; return token;
0[1-7][0-7]* token = tok_number; return token;
[1-9][0-9.]* token = tok_number; return token;
0 token = tok_number; return token;

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
        if (token.type == tok_number)
        {
            int numTypeFlag = 10; //进制数
            if (token.tokenValue.substr(0,2)=="0x"||token.tokenValue.substr(0,2)=="0X")
                numTypeFlag = 16;
            else if (token.tokenValue.substr(0,2)=="0b"||token.tokenValue.substr(0,2)=="0B")
                numTypeFlag = 2;
            else if (token.tokenValue.substr(0,1)=="0")
                numTypeFlag = 8;
            char tmp[256];
		    sprintf(tmp, "%ld", strtol(token.tokenValue.c_str(), NULL, numTypeFlag));
	    	token.tokenValue = tmp;
        }
        std::cout << token.dump() << std::endl;
    } 
}