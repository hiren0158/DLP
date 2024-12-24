#include <stdio.h>

int isValid(char str[], int length) {
    int i = 0;

    while (i < length && str[i] == 'a') {
        i++;
    }


    if (i + 1 < length && str[i] == 'b' && str[i + 1] == 'b') {
        i += 2;
    } else {
        return 0;
    }

    if (i == length) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int n;


    printf("Enter the length of string: ");
    scanf("%d", &n);

    if (n<0) {
        printf("Invalid input.\n");
        return 1;
    }

    char input[n + 1];

    printf("Enter the string  ");
    scanf("%s", input);

    if (isValid(input, n)) {
        printf("The string \"%s\" is valid \n", input);
    } else {
        printf("The string \"%s\" is NOT valid .\n", input);
    }

    return 0;
}
