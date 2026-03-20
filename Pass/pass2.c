#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct symtab {
    char label[20];
    int addr;
} sym[MAX];

struct optab {
    char opcode[10];
    char code[10];
} opt[] = {
    {"LDA","00"},
    {"STA","0C"},
    {"ADD","18"},
    {"SUB","1C"},
    {"RSUB","4C"}
};

int symcount = 0;

/* Search SYMTAB */
int searchSym(char *operand) {
    for (int i = 0; i < symcount; i++) {
        if (strcmp(sym[i].label, operand) == 0)
            return sym[i].addr;
    }
    return -1;
}

/* Search OPTAB */
int searchOp(char *opcode) {
    for (int i = 0; i < 5; i++) {
        if (strcmp(opt[i].opcode, opcode) == 0)
            return i;
    }
    return -1;
}

int main() {

    FILE *symf, *inter, *out;

    char line[100];
    char label[20], opcode[20], operand[20];
    int locctr, start = 0;

    char objcode[50];
    char text[500] = "";

    int text_len = 0, text_start = 0;

    symf = fopen("SYMTAB.txt", "r");
    inter = fopen("intermediate.txt", "r");
    out = fopen("output.txt", "w");

    if (!symf || !inter || !out) {
        printf("File error\n");
        return 1;
    }

    /* 🔹 Load SYMTAB */
while (fgets(line, sizeof(line), symf)) {

    if (strlen(line) < 3) continue;  // skip empty lines

    if (sscanf(line, "%s %x", sym[symcount].label, &sym[symcount].addr) == 2) {
        symcount++;
    }
}
    /* 🔹 Skip header lines */
    fgets(line, sizeof(line), inter);
    fgets(line, sizeof(line), inter);

    /* 🔹 Read first actual line */
    fgets(line, sizeof(line), inter);
    sscanf(line, "%x %s %s %s", &locctr, label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = locctr;
        printf("H^%s^%06X\n", label, start);
        fprintf(out, "H^%s^%06X\n", label, start);
    }

    text_start = start;

    /* 🔹 Process rest of lines */
    while (fgets(line, sizeof(line), inter)) {

        /* Stop before program length line */
        if (strncmp(line, "Program Length", 14) == 0)
            break;

        if (sscanf(line, "%x %s %s %s", &locctr, label, opcode, operand) != 4)
            continue;

        if (strcmp(opcode, "END") == 0)
            break;

        objcode[0] = '\0';

        int opIndex = searchOp(opcode);

        /* Machine Instructions */
        if (opIndex != -1) {

            if (strcmp(opcode, "RSUB") == 0) {
                strcpy(objcode, "4C0000");
            } else {
                int addr = searchSym(operand);
                if (addr == -1) addr = 0;

                sprintf(objcode, "%s%04X", opt[opIndex].code, addr);
            }
        }

        /* WORD */
        else if (strcmp(opcode, "WORD") == 0) {
            sprintf(objcode, "%06X", atoi(operand));
        }

        /* BYTE */
        else if (strcmp(opcode, "BYTE") == 0) {

            if (operand[0] == 'C') {
                int len = strlen(operand);
                for (int i = 2; i < len - 1; i++) {
                    char temp[5];
                    sprintf(temp, "%02X", operand[i]);
                    strcat(objcode, temp);
                }
            }
            else if (operand[0] == 'X') {
                strncpy(objcode, operand + 2, strlen(operand) - 3);
                objcode[strlen(operand) - 3] = '\0';
            }
        }

        /* RESW / RESB → break text record */
        else if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0) {

            if (text_len > 0) {
                printf("T^%06X^%02X^%s\n", text_start, text_len, text);
                fprintf(out, "T^%06X^%02X^%s\n", text_start, text_len, text);
            }

            text[0] = '\0';
            text_len = 0;
            continue;
        }

        /* Add to text record */
        if (strlen(objcode) > 0) {

            if (text_len == 0)
                text_start = locctr;

            strcat(text, objcode);
            text_len += strlen(objcode) / 2;
        }
    }

    /* Flush remaining text record */
    if (text_len > 0) {
        printf("T^%06X^%02X^%s\n", text_start, text_len, text);
        fprintf(out, "T^%06X^%02X^%s\n", text_start, text_len, text);
    }

    /* End record */
    printf("E^%06X\n", start);
    fprintf(out, "E^%06X\n", start);

    fclose(symf);
    fclose(inter);
    fclose(out);

    return 0;
}
