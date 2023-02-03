#include <stdio.h>
#include <direct.h>
#include <windows.h>
#include <sys/types.h>

int lenght = 1000;
int fileLineLenght = 1000;

char* readFile(FILE* fp);

int GetLines(char* str){

    printf("a1");
    int lines = 1;

    for(int i = 0; strlen(str); i++){
        printf("a2");
        if(str[i] == '\n'){
            lines++;
        }
    }
    printf("a3");
    return lines;
}

char* getString(int readeLastChar){

    char temp = getchar();

    char c = getchar();
    char* inp = malloc(sizeof(char) * lenght);

    for(int i = 0; i < lenght; i++) inp[i] = NULL;

    if(c == '"')
    {
        int index = 0;
        int specialCharacter = 0;

        int cotEntered = 0;

        do{
            c = getchar();

            if(c != '"')
            {
                if(cotEntered)
                {
                    if(c == ' ' || c == '\n') break;
                    else
                    {
                        inp[index] = '"';
                        index++;

                        cotEntered = 0;
                    }
                }

                if(specialCharacter){
                    if(c == '\\'){
                        inp[index] = '\\';
                    }
                    else{
                        if(c == 'n')
                            inp[index] = '\n';
                    }
                    index++;
                    specialCharacter = 0;
                }
                else{
                    if(c == '\\'){
                        specialCharacter = 1;
                    }
                    else{
                        inp[index] = c;
                        index++;

                        specialCharacter = 0;
                    }
                }
            }
            else{
                cotEntered = 1;
            }
        } while(1);

        if(readeLastChar == 0){
            inp[index] = c;
         }
         else{
            inp[index] = '\0';
         }
    }
    else{

        int index = 1;
        inp[0] = c;
        c = getchar();

         while(c != ' ' && c != '\n'){
            inp[index] =  c;
            index++;

            c = getchar();
         }
         if(readeLastChar == 0){
            inp[index] = c;
         }
         else{
            inp[index] = '\0';
         }
    }
    return inp;
}

char* cutString(int index, char* inputStr);

void copyStringToClip(char* str){

    printf("%s", str);
    FILE* ptr;
    ptr = fopen("Clipboard.txt", "w");

    fputs(str, ptr);
    fclose(ptr);
}

char* pasteClipboardToString(){

    FILE* ptr;
    ptr = fopen("Clipboard.txt", "r");

    return readFile(ptr);

}

char* readFile(FILE* fp){

    char* str = malloc(sizeof(char) * lenght);
    int index = 0;

    do
    {
        char c = fgetc(fp);

        if (feof(fp))
            break;

        str[index] = c;
        index++;
    }
    while(1);

    str[index] = '\0';

    return str;
}

void DisplayString(char* str){
    for(int i = 0; i < lenght; i++){
        if(str[i] == NULL) break;
        printf("%c", str[i]);
    }
}

char* cutString(int index, char* inputStr){

    char* finalStr = malloc(sizeof(char) * index);

    for(int i = 0; i < index; i++){
        finalStr[i] = inputStr[i];
    }

    return finalStr;
}

char* removeFirstChar(char* str){
    char *s = malloc(sizeof(char) * lenght);
    for(int i = 0; i < lenght; i++) s[i] = NULL;

    for(int i = 1; i < lenght; i++){
        if(str[i] == NULL) break;
        s[i - 1] = str[i];
    }
    return s;
}

char* removeLastChar(char* str){
    char* s = malloc(sizeof(char) * lenght);

    for(int i = 0; i < strlen(str) - 1; i++){
        s[i] = str[i];
    }
    s[strlen(str) - 1] = '\0';
    return s;
}

char* removeFirstAndLastChar(char* str){
    char *s = malloc(sizeof(char) * lenght);
    for(int i = 0; i < lenght; i++) s[i] = NULL;

    for(int i = 0; i < strlen(str) - 1; i++){
        if(str[i] == NULL) break;
        s[i - 1] = str[i];
    }
    return s;
}


