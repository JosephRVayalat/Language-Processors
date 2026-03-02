#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//creating a structure for TAC calculation.
typedef struct {
    char result[10];
    char arg1[10];
    char op[5];     // +, -, *, /
    char arg2[10];
} TAC;
//this fucntion checks if the opernds are constants.
int isConstant(char *s) {
    if (*s == '-' || *s == '+')
        s++;
    while (*s) {
        if (!isdigit(*s))
            return 0;
        s++;
    }
    return 1;
}

//evaluation happens here(only  +, -, *, /)
int evaluate(int a, int b, char *op) {
    if (strcmp(op, "+") == 0) return a + b;
    if (strcmp(op, "-") == 0) return a - b;
    if (strcmp(op, "*") == 0) return a * b;
    if (strcmp(op, "/") == 0) return b != 0 ? a / b : 0;
    return 0;
}

//core. constant folding function.
void constantFolding(TAC code[], int n) {
    for (int i = 0; i < n; i++) {
       if (strcmp(code[i].op, "=") == 0)
            continue;
        if (isConstant(code[i].arg1) && isConstant(code[i].arg2)) {

            int a = atoi(code[i].arg1);
            int b = atoi(code[i].arg2);
            int result = evaluate(a, b, code[i].op);

            // Replace instruction with constant assignment
            sprintf(code[i].arg1, "%d", result);
            strcpy(code[i].op, "=");
            strcpy(code[i].arg2, "");
        }
    }
}

// printing as TAC
void printTAC(TAC code[], int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(code[i].op, "=") == 0)
            printf("%s = %s\n", code[i].result, code[i].arg1);
        else
            printf("%s = %s %s %s\n",
                   code[i].result,
                   code[i].arg1,
                   code[i].op,
                   code[i].arg2);
    }
}
/* TAC code[] = {
        {"t1", "5", "+", "3"},
        {"a", "t1"},
        {"t2", "a", "*", "2"},
        {"b","t2"}
    };
*/
int main() {
    TAC code[10];
    int n;
    printf("Joseph R Vayalat\n\n");
    printf("Enter no. of instructions:");
    scanf("%d",&n);
    
    for(int i = 0;i<n;i++)
    {
      printf("instruction %d",i+1);
      printf("\nLHS: ");
      scanf("%s",code[i].result);
      printf("left operand: ");
      scanf("%s",code[i].arg1);
      printf("operator: ");
      scanf("%s",code[i].op);
      printf("right operand: ");
      scanf("%s",code[i].arg2);
     } 

    printf("Before Constant Folding:\n");
    printTAC(code, n);

    constantFolding(code, n);

    printf("\nAfter Constant Folding:\n");
    printTAC(code, n);

    return 0;
}

