#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

int tempCount = 1;

// Stack functions
void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Infix to Postfix conversion
void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    char c;

    for (i = 0; infix[i] != '\0'; i++) {

        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(') {
            push(infix[i]);
        }
        else if (infix[i] == ')') {
            while ((c = pop()) != '(')
                postfix[j++] = c;
        }
        else {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i]))//if the operator in the stack has higher precedenc then it needs to 
                postfix[j++] = pop();
            push(infix[i]);
        }
    }

    while (top != -1)//rest of the operators from stack to postfix
        postfix[j++] = pop();

    postfix[j] = '\0';
}

// Generate Three Address Code
void generateTAC(char postfix[]) {

    char tacStack[MAX][10];
    int tacTop = -1;
    char temp[10];

    for (int i = 0; postfix[i] != '\0'; i++) {//abc*+

        if (isalnum(postfix[i])) {
            tacStack[++tacTop][0] = postfix[i];//abc goes here as 1,2,3
            tacStack[tacTop][1] = '\0';
        }
        else {
            char op = postfix[i];//* is encountered here

            char op2[10], op1[10];//b and c is stored in op 1 and 2
            strcpy(op2, tacStack[tacTop--]);//strcpy is used in both,no need of [0] or [1] here
            strcpy(op1, tacStack[tacTop--]);

            sprintf(temp, "t%d", tempCount++);
            printf("%s = %s %c %s\n", temp, op1, op, op2);// pringint it here

            strcpy(tacStack[++tacTop], temp);//idk why but temp has t1 rn and that is the top of the stack oh wait t1 needs to be used later as the operand ig it

        }
    }
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter Infix Expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("\nThree Address Code:\n");
    generateTAC(postfix);

    return 0;
}
/*sample OUTPUT :
PS C:\Users\Dhanwanth\Desktop\vscode\MINI-PROJ> gcc 3ac.c
PS C:\Users\Dhanwanth\Desktop\vscode\MINI-PROJ> ./a.exe
Enter Infix Expression: a+b*c

Three Address Code:
t1 = b * c
t2 = a + t1
*/