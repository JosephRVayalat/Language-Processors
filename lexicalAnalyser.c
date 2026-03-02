#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SYM 100

char keywords[][10] = {
    "int","float","if","else","for","while","return","printf"
};

char symtab[MAX_SYM][50];
int symcount = 0;

int isKeyword(char *str){
    for(int i=0;i<8;i++){
        if(strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int searchSymbol(char *id){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i], id) == 0)
            return i;
    }
    return -1;
}

int addSymbol(char *id){
    int index = searchSymbol(id);
    if(index != -1)
        return index;

    strcpy(symtab[symcount], id);
    symcount++;
    return symcount - 1;
}

int main(){
    printf("Joseph R Vayalat\n\n");
    FILE *fp;
    char ch, buffer[50];
    int state = 0, i = 0;

    fp = fopen("test.txt","r");
    if(fp == NULL){
        printf("File not found\n");
        return 0;
    }

    while((ch = fgetc(fp)) != EOF){
        switch(state){

        case 0:
            if(isspace(ch))
                state = 0;

            else if(ch=='<'){
                buffer[i++]=ch;
                state=1;
            }
            else if(ch=='>'){
                buffer[i++]=ch;
                state=4;
            }
            else if(ch=='!'){
                buffer[i++]=ch;
                state=7;
            }
            else if(ch=='='){
                buffer[i++]=ch;
                state=10;
            }

            else if(isalpha(ch)){
                buffer[i++]=ch;
                state=12;
            }
            else if(isdigit(ch)){
                buffer[i++]=ch;
                state=14;
            }
            else if(ch=='+'){
                buffer[i++]=ch;
                state=15;
            }
            else if(ch=='-'){
                buffer[i++]=ch;
                state=18;
            }
            else if(ch=='*'){
                buffer[i++]=ch;
                state=21;
            }
            else if(ch=='/'){
                buffer[i++]=ch;
                state=23;
            }
            else if(ch=='&'){
                buffer[i++]=ch;
                state=25;
            }
            else if(ch=='|'){
                buffer[i++]=ch;
                state=28;
            }

            else
                printf("%c - special symbol\n", ch);
            break;
        case 1:
            if(ch=='='){
                buffer[i++]=ch;
                buffer[i]='\0';
                printf("%s - LE\n",buffer);
            }
            else{
                buffer[i]='\0';
                printf("%s - LT\n",buffer);
                fseek(fp,-1,SEEK_CUR);
            }
            i=0;
            state=0;
            break;

        case 4:
            if(ch=='='){
                buffer[i++]=ch;
                buffer[i]='\0';
                printf("%s - GE\n",buffer);
            }
            else{
                buffer[i]='\0';
                printf("%s - GT\n",buffer);
                fseek(fp,-1,SEEK_CUR);
            }
            i=0;
            state=0;
            break;

        case 7:
            if(ch=='='){
                buffer[i++]=ch;
                buffer[i]='\0';
                printf("%s - NE\n",buffer);
            }
            else{
                buffer[i]='\0';
                printf("%s - NOT\n",buffer);
                fseek(fp,-1,SEEK_CUR);
            }
            i=0;
            state=0;
            break;

        case 10:
            if(ch=='='){
                buffer[i++]=ch;
                buffer[i]='\0';
                printf("%s - EQ\n",buffer);
            }
            else{
                buffer[i]='\0';
                printf("%s - ASSIGN\n",buffer);
                fseek(fp,-1,SEEK_CUR);
            }
            i=0;
            state=0;
            break;

        case 12:
            if(isalnum(ch))
                buffer[i++]=ch;
            else{
                buffer[i]='\0';

                if(isKeyword(buffer)){
                    printf("%s - KEYWORD\n",buffer);
                }
                else{
                    int idx = addSymbol(buffer);
                    printf("%s <identifier, #%d>\n", buffer, idx);
                }

                i=0;
                state=0;
                fseek(fp,-1,SEEK_CUR);
            }
            break;

        case 14:
            if(isdigit(ch))
                buffer[i++]=ch;
            else{
                buffer[i]='\0';
                printf("%s - CONSTANT\n",buffer);
                i=0;
                state=0;
                fseek(fp,-1,SEEK_CUR);
            }
            break;

        case 15:
            if(ch=='+'){
                buffer[i++]=ch;
                buffer[i]='\0';
                printf("%s - INC\n",buffer);
            }
            else{
                buffer[i]='\0';
                printf("%s - ADD\n",buffer);
                fseek(fp,-1,SEEK_CUR);
            }
            i=0;
            state=0;
            break;

        case 18:
            if(ch=='-'){
                buffer[i++]=ch;
                buffer[i]='\0';
                printf("%s - DEC\n",buffer);
            }
            else{
                buffer[i]='\0';
                printf("%s - SUB\n",buffer);
                fseek(fp,-1,SEEK_CUR);
            }
            i=0;
            state=0;
            break;

        case 21:
            buffer[i]='\0';
            printf("%s - MUL\n",buffer);
            i=0; state=0;
            fseek(fp,-1,SEEK_CUR);
            break;

        case 23:
            buffer[i]='\0';
            printf("%s - DIV\n",buffer);
            i=0; state=0;
            fseek(fp,-1,SEEK_CUR);
            break;

        case 25:
            if(ch=='&'){
                buffer[i++]=ch; buffer[i]='\0'; printf("%s - AND\n",buffer);
            }
            else{
                buffer[i]='\0';
                printf("%s - BIT_AND\n",buffer);
                fseek(fp,-1,SEEK_CUR);
            }
            i=0;
            state=0;
            break;

        case 28:
            if(ch=='|'){
                buffer[i++]=ch;
                buffer[i]='\0';
                printf("%s - OR\n",buffer);
            }
            else{
                buffer[i]='\0';
                printf("%s - BIT_OR\n",buffer);
                fseek(fp,-1,SEEK_CUR);
            }
            i=0;
            state=0;
            break;
        }
    }

    fclose(fp);

    printf("\nSYMBOL TABLE\n");
    printf("Index\tIdentifier\n");
    for(int i=0;i<symcount;i++){
        printf("%d\t%s\n", i, symtab[i]);
    }

    return 0;
}
