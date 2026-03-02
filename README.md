# Language-Processors
LP lab programs
All Programs:
1.Write a C program that removes all unnecessary whitespace (such as extra spaces, tabs, and
blank lines) from a given C source code. The program should also remove all single-line
comments (// ...) and multi-line comments (/* ... */). After cleaning the code, print the resulting
program along with line numbers.

2.Implement a lexical analyzer in C for a given language that tokenizes input and detects
lexical errors.

3.Implementation of Lexical Analyzer using Lex Tool. 
a) Develop a Lex program to recognize integers, floating-point numbers, and
arithmetic operators.
b) Implement a Lex specification to count the number of vowels, consonants, digits,
and special characters in a text.
c) Write a Lex program to extract all email IDs from a text file.

4.Generate YACC specification for a few syntactic categories. 
a) Write a YACC specification to parse arithmetic expressions containing +, -, *, /,
integer constants and parentheses.
b) YACC specification for if-else statements. Support if (cond) stmt and if (cond)
stmt else stmt.
c) Write a program to implement an arithmetic calculator.

5.Construct a recursive descent parser for a given grammar.
Grammer:
S  → a S' | b
S' → A d | B
A  → a A' | a c
A' → b | ε
B  → c c d | d d c

6.Construct a Shift Reduce Parser for any given grammar.
7. Generate three-address intermediate code for simple expressions.
8. Implement basic optimization techniques -constant folding.
9.Implement the back end of the compiler which takes the three address code and produces the assembly language instructions.
