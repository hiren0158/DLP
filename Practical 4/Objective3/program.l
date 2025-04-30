%{
#include <stdio.h>

int char_count = 0, word_count = 0, line_count = 0;
%}

%%
\n          { line_count++; char_count++; }  // Count newlines and characters
[ \t]+      { char_count += yyleng; }       // Count spaces and tabs
[a-zA-Z0-9\+\=]+ { word_count++; char_count += yyleng; } // Count words and characters
.           { char_count++; }               // Count other characters
%%

int main() {
    yylex();  // Start lexical analysis

    // If there's any input, adjust line_count for the last line if not ending with newline
    if (char_count > 0 && line_count == 0) {
        line_count = 1;  // In case the input doesn't end with a newline
    }

    // Handle edge case if the last line doesn't end with a newline, ensuring line_count is accurate
    if (line_count == 0) {
        line_count = 1;  // If no line count increment has occurred, treat as one line
    }

    printf("Characters : %d\n", char_count);
    printf("Words : %d\n", word_count);
    printf("Lines : %d\n", line_count);

    return 0;
}

int yywrap() {
    return 1;
}