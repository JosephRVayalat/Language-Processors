/*
 * Pass 2 of Two-Pass Assembler
 * Reads intermediate.txt + symtab.txt → prints object code (H, T, E records)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Opcode table: mnemonic → machine code */
#define OPTAB_SIZE 5
char optab_mnem[OPTAB_SIZE][10] = {"LDA", "ADD", "SUB", "STA", "RSUB"};
char optab_code[OPTAB_SIZE][10] = {"00",  "18",  "1C",  "0C",  "4C"};

int main()
{
    FILE *finter, *fsym;
    char label[20], opcode[20], operand[20], progname[20];
    int  loc, len, start;
    int  j;

    /* Symbol table */
    char sym_label[20][20];
    int  sym_addr[20];
    int  sym_count = 0;

    fsym   = fopen("symtab.txt",       "r");
    finter = fopen("intermediate.txt", "r");

    /* Load all symbols from symtab.txt */
    while (fscanf(fsym, "%d %s %x", &j, sym_label[sym_count], &sym_addr[sym_count]) != EOF)
        sym_count++;

    /* Read first line of intermediate */
    fscanf(finter, "%x %d %s %s %s", &loc, &len, label, opcode, operand);

    if (strcmp(opcode, "START") == 0)
    {
        start = strtol(operand, NULL, 16);
        strcpy(progname, label);
        fscanf(finter, "%x %d %s %s %s", &loc, &len, label, opcode, operand);
    }

    /* Buffer T record content so we can compute length before printing */
    char tbuf[512] = "";
    char tmp[64];
    int  text_bytes = 0;

    /* Process each line until END */
    while (strcmp(opcode, "END") != 0)
    {
        /* Look up opcode in optab */
        for (int i = 0; i < OPTAB_SIZE; i++)
        {
            if (strcmp(opcode, optab_mnem[i]) == 0)
            {
                /* Find operand address in symbol table */
                int address = 0;
                for (j = 0; j < sym_count; j++)
                {
                    if (strcmp(sym_label[j], operand) == 0)
                    {
                        address = sym_addr[j];
                        break;
                    }
                }
                sprintf(tmp, "%s%04X^", optab_code[i], address);
                strcat(tbuf, tmp);
                text_bytes += 3;
                break;
            }
        }

        /* BYTE directive: print hex of each character */
        if (strcmp(opcode, "BYTE") == 0)
        {
            for (int i = 2; i < strlen(operand) - 1; i++)
            {
                sprintf(tmp, "%02X", operand[i]);
                strcat(tbuf, tmp);
                text_bytes++;
            }
            strcat(tbuf, "^");
        }

        /* WORD directive: print 6-digit hex value */
        if (strcmp(opcode, "WORD") == 0)
        {
            sprintf(tmp, "%06X^", atoi(operand)); //atoi important
            strcat(tbuf, tmp);
            text_bytes += 3;
        }

        fscanf(finter, "%x %d %s %s %s", &loc, &len, label, opcode, operand);
    }

    /* Now loc holds the END address, so program length = loc - start */
    int prog_len = loc - start;

    /* Header record */
    printf("H^%s^%06X^%06X\n", progname, start, prog_len);

    /* Text record with computed length */
    printf("T^%06X^%02X^%s\n", start, text_bytes, tbuf);

    /* End record */
    printf("E^%06X\n", start);

    fclose(finter);
    fclose(fsym);

    return 0;
}