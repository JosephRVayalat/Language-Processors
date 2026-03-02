#include <stdio.h>
#include <string.h>
#include <ctype.h>

char expr[20];
int tempCount = 1;

void generateTAC() {
    int i;
    char temp;

    /* First handle * and / */
    for (i = 0; i < strlen(expr); i++) {
        if (expr[i] == '*' || expr[i] == '/') {
            printf("t%d = %c %c %c\n", tempCount, expr[i-1], expr[i], expr[i+1]);

            expr[i-1] = 't';
            expr[i] = tempCount + '0';

            // Shift expression left
            for (int j = i + 1; j < strlen(expr) - 1; j++)
                expr[j] = expr[j + 1];

            expr[strlen(expr) - 1] = '\0';
            tempCount++;
            i = -1;
        }
    }

    /* Then handle + and - */
    for (i = 0; i < strlen(expr); i++) {
        if (expr[i] == '+' || expr[i] == '-') {
            printf("t%d = %c %c %c\n", tempCount, expr[i-1], expr[i], expr[i+1]);

            expr[i-1] = 't';
            expr[i] = tempCount + '0';

            for (int j = i + 1; j < strlen(expr) - 1; j++)
                expr[j] = expr[j + 1];

            expr[strlen(expr) - 1] = '\0';
            tempCount++;
            i = -1;
        }
    }
}

int main() {
    printf("Joseph R Vayalat\n\n");
    printf("Enter expression: ");
    scanf("%s", expr);

    printf("\nThree Address Code:\n");

    printf("Assignment:\n");
    char lhs = expr[0];

    /* Remove lhs and '=' */
    memmove(expr, expr + 2, strlen(expr));

    generateTAC();

    printf("%c = t%d\n", lhs, tempCount - 1);

    return 0;
}
