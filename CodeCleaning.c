#include <stdio.h>
#include <ctype.h>

int main() {
    printf("Joseph R Vayalat\n\n");
    FILE *in = fopen("input.c", "r");

    if (!in) {
        printf("Error: Could not open input.c\n");
        return 1;
    }

    int c, prev = 0;
    int in_single_comment = 0, in_multi_comment = 0;
    int newline_needed = 0;
    int line_number = 1;
    int wrote_something = 0;

    printf("%3d: ", line_number);
    line_number++;

    while ((c = fgetc(in)) != EOF) {

        if (in_single_comment) {
            if (c == '\n') {
                in_single_comment = 0;
                newline_needed = 1;
            }
            continue;
        }

        if (in_multi_comment) {
            if (c == '*' && (c = fgetc(in)) == '/') {
                in_multi_comment = 0;
            }
            continue;
        }

        if (c == '/') {
            int next = fgetc(in);

            if (next == '/') {
                in_single_comment = 1;
                continue;
            }
            else if (next == '*') {
                in_multi_comment = 1;
                continue;
            }
            else {
                putchar(c);
                c = next;
            }
        }

        if (isspace(c)) {
            if (c == '\n') {
                newline_needed = 1;
                continue;
            }
            if (prev == ' ' || prev == '\t' || prev == '\n')
                continue;
            c = ' ';
        }

        if (newline_needed) {
            if (wrote_something) {
                printf("\n%3d: ", line_number);
                line_number++;
                wrote_something = 0;
            }
            newline_needed = 0;
        }

        putchar(c);
        wrote_something = 1;
        prev = c;
    }


    printf("\n");

    fclose(in);

    printf("\nCleaning complete!\n");

    return 0;
}

