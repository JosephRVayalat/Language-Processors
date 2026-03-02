#include <stdio.h>
#include <stdlib.h>

/* Global variables */
char input[100];
int pos = 0;
char lookahead;

/* Function declarations */
void S();
void Sprime();
void A();
void Aprime();
void B();
void match(char);

/* Match function */
void match(char t) {
    if (lookahead == t) {
        pos++;
        lookahead = input[pos];
    } else {
        printf("Syntax Error: Expected '%c' but found '%c'\n", t, lookahead);
        exit(1);
    }
}

/* S → a S' | b */
void S() {
    if (lookahead == 'a') {
        match('a');
        Sprime();
    }
    else if (lookahead == 'b') {
        match('b');
    }
    else {
        printf("Syntax Error in S\n");
        exit(1);
    }
}

/* S' → A d | B */
void Sprime() {
    if (lookahead == 'a') {
        A();
        match('d'); // After A() finishes, we MUST find a 'd'
    }
    else if (lookahead == 'c' || lookahead == 'd') {
        B();
    }
    else {
        printf("Syntax Error in S'\n");
        exit(1);
    }
}

/* A → a A' | a c */
void A() {
    if (lookahead == 'a') {
        match('a');
        /* If the next char is 'c', we follow A -> ac.
           Otherwise, we follow A -> aA' (where A' can be 'b' or epsilon).
        */
        if (lookahead == 'c') {
            match('c');
        } else {
            Aprime(); 
        }
    }
    else {
        printf("Syntax Error in A\n");
        exit(1);
    }
}

/* A' → b | ε */
void Aprime() {
    if (lookahead == 'b') {
        match('b');
    }
    
}

/* B → c c d | d d c */
void B() {
    if (lookahead == 'c') {
        match('c');
        match('c');
        match('d');
    }
    else if (lookahead == 'd') {
        match('d');
        match('d');
        match('c');
    }
    else {
        printf("Syntax Error in B\n");
        exit(1);
    }
}

int main() {
    printf("Enter the string: ");
    scanf("%s", input);

    lookahead = input[0];
    S();

    if (lookahead == '\0') {
        printf("Parsing Successful\n");
    } else {
        printf("Syntax Error: Extra characters at end of input\n");
    }

    return 0;
}
