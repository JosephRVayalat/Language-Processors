/*
 * Pass 1 of Two-Pass Assembler
 * Reads input.txt → writes intermediate.txt and symtab.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fin, *finter, *fsym;
    char label[20], opcode[20], operand[20];
    int locctr = 0, start = 0, len;

    /* Symbol table stored as two parallel arrays */
    char sym_label[50][20];
    int  sym_addr[50];
    int  sym_count = 0;

    fin    = fopen("input.txt",        "r");
    finter = fopen("intermediate.txt", "w");
    fsym   = fopen("symtab.txt",       "w");

    /* Read first line */
    fscanf(fin, "%s %s %s", label, opcode, operand);

    /* If program starts with START, set location counter */
    if (strcmp(opcode, "START") == 0)
    {
        start  = strtol(operand, NULL, 16);   /* operand is hex e.g. "1000" */
        locctr = start;
        fprintf(finter, "%04X\t0\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        fscanf(fin, "%s %s %s", label, opcode, operand);
    }

    /* Process lines until END */
    while (strcmp(opcode, "END") != 0)
    {
        /* If line has a label, save it in symbol table */
        if (strcmp(label, "-") != 0)
        {
            strcpy(sym_label[sym_count], label);
            sym_addr[sym_count] = locctr;
            sym_count++;
        }

        /* Calculate how many bytes this directive/instruction takes */
        if      (strcmp(opcode, "WORD") == 0)  len = 3;
        else if (strcmp(opcode, "RESW") == 0)  len = 3 * atoi(operand);
        else if (strcmp(opcode, "RESB") == 0)  len = atoi(operand);
        else if (strcmp(opcode, "BYTE") == 0)
            len = (operand[0] == 'C') ? strlen(operand) - 3 : 1;
        else
            len = 3;   /* all normal instructions are 3 bytes */

        fprintf(finter, "%04X\t%d\t%s\t%s\t%s\n", locctr, len, label, opcode, operand);
        locctr += len;

        fscanf(fin, "%s %s %s", label, opcode, operand);
    }

    /* Write the END line to intermediate */
    fprintf(finter, "%04X\t0\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    /* Write symbol table to file */
    for (int i = 0; i < sym_count; i++)
        fprintf(fsym, "%d\t%s\t%04X\n", i + 1, sym_label[i], sym_addr[i]);

    fclose(fin);
    fclose(finter);
    fclose(fsym);

    printf("PASS 1 Completed Successfully\n");
    printf("Program Length = %X\n", locctr - start);

    return 0;
}