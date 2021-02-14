%{
#include "../Token.h"
#include <fstream>
#include <iostream>
int token;

%}
%option yylineno
%option c++
%%
[ \t]+                      {/*Skip spaces and tabs*/};
\/\*[.\n]*?\*\/|\/\/.*      {/*Skip comments*/};

->                          token = tok_return_type; return token;
fun                         token = tok_fun; return token;
func                        token = tok_fun; return token;
extern                      token = tok_extern; return token;
return                      token = tok_extern; return token;
[a-zA-Z_][a-zA-Z0-9_]*        token = tok_identifier; return token;
0b[01]*                     token = tok_number; return token;
0x[1-9a-fA-F][0-9a-fA-F]*   token = tok_number; return token;
0B[01]*                     token = tok_number; return token;
0X[1-9a-fA-F][0-9a-fA-F]*   token = tok_number; return token;
0[1-7][0-7]*                token = tok_number; return token;
[1-9][0-9.]*                token = tok_number; return token;
0                           token = tok_number; return token;

!                           token = tok_syntax; return token;
%                           token = tok_syntax; return token;
\^                          token = tok_syntax; return token;
&                           token = tok_syntax; return token;
\*                          token = tok_syntax; return token;
\(                          token = tok_syntax; return token;
\)                          token = tok_syntax; return token;
\+                          token = tok_syntax; return token;
=                           token = tok_syntax; return token;
\{                          token = tok_syntax; return token;
\}                          token = tok_syntax; return token;
\|                          token = tok_syntax; return token;
~                           token = tok_syntax; return token;
\[                          token = tok_syntax; return token;
\]                          token = tok_syntax; return token;
\\                          token = tok_syntax; return token;
;                           token = tok_syntax; return token;
'                           token = tok_syntax; return token;
:                           token = tok_syntax; return token;
\"                          token = tok_syntax; return token;
,                           token = tok_syntax; return token;
\<                          token = tok_syntax; return token;
\>                          token = tok_syntax; return token;
\?                          token = tok_syntax; return token;
\.                          token = tok_syntax; return token;
\/                          token = tok_syntax; return token;
#                           token = tok_syntax; return token;
<<EOF>>                     {token = tok_eof; return token;}
.                           token = tok_err; return token;
%%

int yyFlexLexer::yywrap(){return 1;}
%{
#include "../Token.h"
#include <fstream>
#include <iostream>
int token;

%}
%option yylineno
%%
[ \t]+                      {/*Skip spaces and tabs*/};
\/\*[.\n]*?\*\/|\/\/.*      {/*Skip comments*/};

->                          token = tok_return_type;    return token;
fun                         token = tok_fun;            return token;
func                        token = tok_fun;            return token;
extern                      token = tok_extern;         return token;
return                      token = tok_extern;         return token;
[a-zA-Z_][a-zA-Z0-9_]*      token = tok_identifier;     return token;
0b[01]*                     token = tok_number;         return token;
0x[1-9a-fA-F][0-9a-fA-F]*   token = tok_number;         return token;
0B[01]*                     token = tok_number;         return token;
0X[1-9a-fA-F][0-9a-fA-F]*   token = tok_number;         return token;
0[1-7][0-7]*                token = tok_number;         return token;
[1-9][0-9.]*                token = tok_number;         return token;
0                           token = tok_number;         return token;

!                           token = tok_syntax;         return token;
%                           token = tok_syntax;         return token;
\^                          token = tok_syntax;         return token;
&                           token = tok_syntax;         return token;
\*                          token = tok_syntax;         return token;
\(                          token = tok_syntax;         return token;
\)                          token = tok_syntax;         return token;
\+                          token = tok_syntax;         return token;
=                           token = tok_syntax;         return token;
\{                          token = tok_syntax;         return token;
\}                          token = tok_syntax;         return token;
\|                          token = tok_syntax;         return token;
~                           token = tok_syntax;         return token;
\[                          token = tok_syntax;         return token;
\]                          token = tok_syntax;         return token;
\\                          token = tok_syntax;         return token;
;                           token = tok_syntax;         return token;
'                           token = tok_syntax;         return token;
:                           token = tok_syntax;         return token;
\"                          token = tok_syntax;         return token;
,                           token = tok_syntax;         return token;
\<                          token = tok_syntax;         return token;
\>                          token = tok_syntax;         return token;
\?                          token = tok_syntax;         return token;
\.                          token = tok_syntax;         return token;
\/                          token = tok_syntax;         return token;
#                           token = tok_syntax;         return token;
<<EOF>>                     {token = tok_eof;           return token;}
.                           token = tok_error;          return token;
%%

int yyFlexLexer::yywrap(){return 1;}
