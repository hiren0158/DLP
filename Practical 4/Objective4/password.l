%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_lower = 0, has_upper = 0, has_digit = 0, has_symbol = 0;
int length = 0;

void check_password();
%}

%%

[a-z]      { has_lower = 1; length++; }
[A-Z]      { has_upper = 1; length++; }
[0-9]      { has_digit = 1; length++; }
[*;#$@]    { has_symbol = 1; length++; }
.          { length++; }
\n         { check_password(); return 0; }

%%

void check_password() {
    if (length >= 9 && length <= 15 && has_lower && has_upper && has_digit && has_symbol) {
        printf("Valid password\n");
    } else {
        printf("Invalid password\n");
    }
}

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
