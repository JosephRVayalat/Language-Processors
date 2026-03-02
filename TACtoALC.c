#include <stdio.h>
#include <string.h>

void generate(char result, char arg1, char arg2, char op) {
    switch (op) {
        case '+':
            printf("MOV R1, %c\n", arg1);
            printf("MOV R2, %c\n", arg2);
            printf("ADD R1,R2\n");
            printf("MOV %c,R1\n\n", result);
            break;

        case '-':
            printf("MOV R1, %c\n", arg1);
            printf("MOV R2, %c\n", arg2);
            printf("SUB R1,R2\n");
            printf("MOV %c,R1\n\n", result);
            break;

        case '*':
            printf("MOV R1, %c\n", arg1);
            printf("MOV R2, %c\n", arg2);
            printf("MUL R1,R2\n");
            printf("MOV %c,R1\n\n", result);
            break;

        case '/':
            printf("MOV R1, %c\n", arg1);
            printf("MOV R2, %c\n", arg2);
            printf("DIV R1,R2\n");
            printf("MOV %c,R1\n\n", result);
            break;

        case '=':
            printf("MOV R1, %c\n", arg1);
            printf("MOV %c,R1\n\n", result);
            break;

        default:
            printf("; Unsupported operation\n\n");
    }
}

int main() {
    int n;
    char line[50];
    char result, arg1, arg2, op;
    printf("Joseph R Vayalat\n\n");
    printf("Enter number of TAC statements: ");
    scanf("%d", &n);
    getchar(); // clear buffer

    for (int i = 0; i < n; i++) {
        printf("\nEnter TAC: ");
        fgets(line, sizeof(line), stdin);

        // for x = y op z
        if (sscanf(line, " %c = %c %c %c", &result, &arg1, &op, &arg2) == 4) {
            generate(result, arg1, arg2, op);
        }
        // for x = y
        else if (sscanf(line, " %c = %c", &result, &arg1) == 2) {
            generate(result, arg1, 0, '=');
        }
        else {
            printf("; Invalid TAC format\n\n");
        }
    }

    return 0;
}

