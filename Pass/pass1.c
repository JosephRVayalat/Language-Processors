#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50

struct symtab {
    char label[20];
    int addr;
} s[MAX];

int main() {

    FILE *fp, *sym, *inter;

    char label[20], opcode[20], operand[20];
    char line[100], t1[20], t2[20], t3[20];

    int lc = 0, start = 0, i = 0;

    fp = fopen("input.txt", "r");
    sym = fopen("SYMTAB.txt", "w");
    inter = fopen("intermediate.txt", "w");

    if (fp == NULL || sym == NULL || inter == NULL) {
        printf("Error opening files\n");
        return 1;
    }

    /* 🔹 Header for intermediate file */
    fprintf(inter, "%-10s %-10s %-10s %-10s\n",
            "LOCCTR", "LABEL", "OPCODE", "OPERAND");
    fprintf(inter, "-------------------------------------------------\n");

    /* 🔹 Read input line by line */
    while (fgets(line, sizeof(line), fp)) {

        int count = sscanf(line, "%s %s %s", t1, t2, t3);

        if (count == 3) {
            strcpy(label, t1);
            strcpy(opcode, t2);
            strcpy(operand, t3);
        }
        else if (count == 2) {
            strcpy(label, "-");
            strcpy(opcode, t1);
            strcpy(operand, t2);
        }
        else if (count == 1) {
            strcpy(label, "-");
            strcpy(opcode, t1);
            strcpy(operand, "-");
        }
        else {
            continue;
        }

        /* 🔹 START */
        if (strcmp(opcode, "START") == 0) {

            start = (int)strtol(operand, NULL, 16);
            lc = start;

            fprintf(inter, "%04X      %-10s %-10s %-10s\n",
                    lc, label, opcode, operand);
        }

        else {

            /* 🔹 Add label to SYMTAB */
            if (strcmp(label, "-") != 0) {

                int duplicate = 0;
                for (int k = 0; k < i; k++) {
                    if (strcmp(s[k].label, label) == 0) {
                        duplicate = 1;
                        break;
                    }
                }

                if (!duplicate) {
                    strcpy(s[i].label, label);
                    s[i].addr = lc;

                    fprintf(sym, "%-10s %04X\n", s[i].label, s[i].addr);
                    i++;
                }
            }

            /* 🔹 Write to intermediate file */
            fprintf(inter, "%04X      %-10s %-10s %-10s\n",
                    lc, label, opcode, operand);

            /* 🔹 Update LOCCTR */
            if (strcmp(opcode, "WORD") == 0)
                lc += 3;

            else if (strcmp(opcode, "RESW") == 0)
                lc += 3 * atoi(operand);

            else if (strcmp(opcode, "RESB") == 0)
                lc += atoi(operand);

            else if (strcmp(opcode, "BYTE") == 0) {

                if (operand[0] == 'C')
                    lc += strlen(operand) - 3;

                else if (operand[0] == 'X')
                    lc += (strlen(operand) - 3) / 2;
            }

            else
                lc += 3;   // default instruction size
        }

        /* 🔹 END */
        if (strcmp(opcode, "END") == 0)
            break;
    }

    /* 🔹 Program Length */
    int length = lc - start;

    fprintf(inter, "\nProgram Length = %04X\n", length);

    fclose(fp);
    fclose(sym);
    fclose(inter);

    printf("\nPASS 1 Completed Successfully!\n");
    printf("SYMTAB.txt and intermediate.txt generated.\n");
    printf("Program Length = %04X\n", length);

    return 0;
}
