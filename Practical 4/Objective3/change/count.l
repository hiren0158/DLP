%{
#include <stdio.h>

int char_count = 0, word_count = 0, line_count = 0, tab_count = 0, ident_count = 0, special_count = 0, space_count = 0, keyword_count = 0, constant_count = 0;
extern FILE *yyin;
%}

DIGIT    [0-9]+
IDENT    [a-zA-Z_][a-zA-Z0-9_]*
KEYWORD  "int"|"char"|"return"|"if"|"else"|"while"|"for"|"do"|"void"
SPECIAL  [!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?]+

%%

\n          { line_count++; char_count++; }
\t          { tab_count++; char_count++; }
[ ]         { space_count++; char_count++; }
{KEYWORD}   { keyword_count++; word_count++; char_count += yyleng; }
{IDENT}     { ident_count++; word_count++; char_count += yyleng; }
{DIGIT}     { constant_count++; word_count++; char_count += yyleng; }
{SPECIAL}   { special_count++; char_count += yyleng; }
.           { char_count++; }

%%

int main() {
    char filename[100];
    printf("Enter the name of the file: ");
    scanf("%s", filename);

    yyin = fopen(filename, "r");
    if (!yyin) {
        perror("Error opening file");
        return 1;
    }

    yylex();
    fclose(yyin);

    printf("Characters : %d\n", char_count);
    printf("Words : %d\n", word_count);
    printf("Lines : %d\n", line_count);
    printf("Tabs : %d\n", tab_count);
    printf("Identifiers : %d\n", ident_count);
    printf("Keywords : %d\n", keyword_count);
    printf("Special Characters : %d\n", special_count);
    printf("Spaces : %d\n", space_count);
    printf("Constants : %d\n", constant_count);

    return 0;
}

int yywrap() {
    return 1;
}