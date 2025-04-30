%{
#include <stdio.h>
%}

%%

[0-9]+   { printf("%s\n", yytext); }  // Match numbers and print them
.        { }  // Ignore non-numeric characters

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
