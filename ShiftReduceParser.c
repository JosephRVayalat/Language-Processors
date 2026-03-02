#include <stdio.h>
#include <string.h>

#define MAX 20

char stack[50], input[50];
char prod[MAX][10];
int top = -1, ip = 0;
int n;

void printState(char action[]) {
    printf("%-15s %-15s %s\n", stack, &input[ip], action);
}

int reduce() {
    for (int i = 0; i < n; i++) {
        int len = strlen(prod[i]) - 3; // RHS length
        if (top + 1 >= len) {
            if (strncmp(&stack[top - len + 1], &prod[i][3], len) == 0) {
                top = top - len + 1;
                stack[top] = prod[i][0]; // LHS
                stack[top + 1] = '\0';
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    printf("Joseph R Vayalat\n\n");
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g., E->E+E):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
    }

    printf("Enter input string: ");
    scanf("%s", input);

    printf("\nSTACK           INPUT           ACTION\n");	
    printf("--------------------------------------\n");

    while (1) {
        if (reduce()) {
            printState("REDUCE");
        } else if (input[ip] != '\0') {
            stack[++top] = input[ip++];
            stack[top + 1] = '\0';
            printState("SHIFT");
        } else {
            break;
        }
    }

    if (top == 0 && stack[top] == prod[0][0]) {
        printf("\nACCEPTED\n");
    } else {
        printf("\nREJECTED\n");
    }

    return 0;
}

