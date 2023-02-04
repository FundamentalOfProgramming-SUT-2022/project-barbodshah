#include <stdio.h>
#include <direct.h>
#include "basicFunctions.c"
#include "inputFunctions.c"

void createFile(char *dirname, int temp){

    char* dir = dirname;

    int stringEnded = 0;
    int counter = 0;

    for(int i = 0; i < lenght; i++){
        if(dirname[i] == NULL) break;
        if(dirname[i] == '/') counter++;
    }

    int tempCounter = 0;

    for(int i = 0; i < lenght; i++)
    {
        if(dirname[i] == '/' || dirname[i] == NULL)
        {
            char* tempDir = malloc(sizeof(char) * lenght);

            for(int j = 0; j < lenght; j++)
            {
                tempDir[j] = NULL;
            }
            int index = 0;
            for(int j = 0; j < i; j++)
            {
                if(dirname[j] == '/')
                {
                    tempDir[index] = '\\';
                    index++;
                    tempDir[index] = '\\';
                }
                else
                {
                    tempDir[index] = dirname[j];
                }
                index++;
            }
            tempCounter++;

            if(tempCounter == counter + 1){
                stringEnded = 1;

                FILE* ptr;
                ptr = fopen(dirname, "r");

                if(ptr != NULL && temp == 0){
                    printf("File Already Exists\n");
                    return;
                }

                ptr = fopen(dirname, "w");

                fclose(ptr);

                break;
            }
            _mkdir(tempDir);

            if(dirname[i] == NULL)
            {
                stringEnded = 1;
                break;
            }
        }
        if(stringEnded == 1){
            break;
        }
    }
    if(temp == 1) return;
    printf("File Created Successfully\n");
}

void InsertStr(char* dirname, char str[lenght], int line, int character){

    FILE* ptr;
    ptr = fopen(dirname, "a+");

    if(ptr == NULL){
        printf("File not found\n");
        return;
    }

    dirname[0] = 't';
    dirname[1] = 'e';
    dirname[2] = 'm';
    dirname[3] = 'p';

    FILE* tempPtr;
    tempPtr = fopen(dirname, "w");

    char *fileStr = readFile(ptr);

    fputs(fileStr, tempPtr);
    fclose(tempPtr);

    int charCounter = 0;
    int lineCounter = 1;

    char* tempStr = malloc(sizeof(char) * lenght);
    for(int i = 0; i < lenght; i++) tempStr[i] = NULL;

    int index = 0;

    for(int i = 0; i < lenght; i++){
        if(lineCounter == line)
        {
            if(charCounter == character){
                int inputStrLenght = strlen(str);
                for(int j = 0; j < inputStrLenght; j++){
                    tempStr[index] = str[j];
                    index++;
                }
            }
            charCounter++;
        }
        if(fileStr[i] == '\n'){
            lineCounter++;
        }

        tempStr[index] = fileStr[i];
        index++;

        if(fileStr[i] == NULL) break;
    }
    dirname[0] = 'r';
    dirname[1] = 'o';
    dirname[2] = 'o';
    dirname[3] = 't';

    ptr = fopen(dirname, "w");

    tempStr[index] = '\0';
    fputs(tempStr, ptr);

    printf("%s", tempStr);
    printf("\n");

    //ptr = fopen(dirname, "w");
    //fprintf(ptr, tempStr);

    fclose( ptr );
}

void cat(char* dirname, int arman){

    FILE* ptr;
    ptr = fopen(dirname, "a+");

    if(ptr == NULL){
        printf("File not found\n");
        return;
    }
    char* fileStr = readFile(ptr);

    if(!arman){
        printf("%s", fileStr);
        printf("\n");
    }

    if(arman){
        FILE* ptr;
        ptr = fopen("arman.txt", "w");

        fputs(fileStr, ptr);
        fclose(ptr);

        armanOrder();
    }
}

void removeStr(char* dirname, int line, int character, int strLenght, int flag){

    FILE* ptr;
    ptr = fopen(dirname, "a+");

    if(ptr == NULL){
        printf("File not found\n");
        return;
    }

    dirname[0] = 't';
    dirname[1] = 'e';
    dirname[2] = 'm';
    dirname[3] = 'p';

    FILE* tempPtr;
    tempPtr = fopen(dirname, "w");

    char* fileStr = readFile(ptr);

    fputs(fileStr, tempPtr);
    fclose(tempPtr);

    char* tempStr = malloc(sizeof(char) * lenght);
    int index = 0;

    int lineCounter = 1;
    int charCounter = 0;

    for(int i = 0; i < lenght; i++){
        if(lineCounter == line)
        {
            if(charCounter == character){
                if(flag == 1){
                    i += strLenght;
                }
                else{
                    index -= strLenght;
                }
            }
            charCounter++;
        }
        if(fileStr[i] == '\n'){
            lineCounter++;
        }

        tempStr[index] = fileStr[i];
        index++;

        if(fileStr[i] == NULL) break;
    }
    dirname[0] = 'r';
    dirname[1] = 'o';
    dirname[2] = 'o';
    dirname[3] = 't';

    ptr = fopen(dirname, "w");

    tempStr[index] = '\0';
    fputs(tempStr, ptr);

    printf("%s", tempStr);
    printf("\n");

    fclose(ptr);
}

void copyStr(char* dirname, int line, int character, int strLenght, int flag){

    FILE* ptr;
    ptr = fopen(dirname, "a+");

    if(ptr == NULL){
        printf("File not found\n");
        return;
    }

    char* fileStr = readFile(ptr);

    char* tempStr = malloc(sizeof(char) * lenght);
    int index = 0;

    int lineCounter = 1;
    int charCounter = 0;

    for(int i = 0; i < lenght; i++){
        if(lineCounter == line)
        {
            if(charCounter == character){

                if(flag == 1){
                    for(int j = i; j < i + strLenght; j++){
                        tempStr[index] = fileStr[j];
                        index++;
                    }
                }
                else{
                    for(int j = i - strLenght; j < i; j++){
                        tempStr[index] = fileStr[j];
                        index++;
                    }
                }
            }
            charCounter++;
        }
        if(fileStr[i] == '\n'){
            lineCounter++;
        }

        if(fileStr[i] == NULL) break;
    }
    copyStringToClip(tempStr);

    fclose(ptr);
}

void cutStr(char* dirname, int line, int character, int strLenght, int flag){
    copyStr(dirname, line, character, strLenght, flag);
    removeStr(dirname, line, character, strLenght, flag);
}

void pasteStr(char* dirname, int line, int character){
    char* str = pasteClipboardToString();
    InsertStr(dirname, str, line, character);
}

void findWildCard(char* inputstr, char* filestr, int count, int at, int byword, int all, int atNum){

    int matchIndex = 0;

    int counter = 0, wordCounter = 1;

    if(inputstr[0] == '*') matchIndex = 1;

    for(int i = 0; i < strlen(filestr); i++)
    {
        if(inputstr[matchIndex] == filestr[i])
        {
            int match = 1;
            int index = 0;

            for(int j = 0; j < strlen(inputstr); j++)
            {
                if(inputstr[j] == '*'){
                    if(j == strlen(inputstr) - 1){
                        break;
                    }
                    while(filestr[i + index] != inputstr[j + 1]){
                        index++;

                        if(filestr[i + index] == ' '){
                            match = 0;
                            break;
                        }

                        if(i + index == strlen(inputstr)){
                            match = 0;
                            break;
                        }
                    }
                }
                else{
                    if(inputstr[j] != filestr[i + index]){
                        match = 0;
                        break;
                    }
                    index++;
                }
            }
            if(match == 1){
                if(count || at){
                    counter++;

                    if(at && atNum == counter){
                        if(byword){
                            printf("%d ", wordCounter);
                        }
                        else{
                            printf("%d ", i - matchIndex);
                        }
                    }
                }
                else{
                    if(byword){
                            printf("%d ", wordCounter);
                        }
                        else{
                            printf("%d ", i - matchIndex);
                    }
                    if(all == 0) break;
                }
            }
        }
    }
    if(count && at == 0){
        printf("%d\n", counter);
    }
    else if(at && atNum > counter){
        printf("-1\n");
    }
    else{
        printf("\n");
    }
}

void find(char* dirname, char* inputstr, int count, int at, int byword, int all, int atNum){

    FILE* ptr;
    ptr = fopen(dirname, "a+");

    int counter = 0, wordCounter = 1, wildCard = 0;

    if(ptr == NULL){
        printf("File not found\n");
        return;
    }

    for(int i = 0; i < strlen(inputstr); i++){
        if(inputstr[i] == '*'){
            if(i == 0){
                wildCard = 1;
                break;
            }
            else{
                if(inputstr[i - 1] != '\\'){
                    wildCard = 1;
                    break;
                }
            }
        }
    }

    char* fileStr = readFile(ptr);

    if(wildCard){
        findWildCard(inputstr, fileStr, count, at, byword, all, atNum);
        fclose(ptr);
        return;
    }

    for(int i = 0; i < strlen(fileStr); i++)
    {
        if(fileStr[i] == ' ') wordCounter++;

        if(inputstr[0] == fileStr[i]){
            int match = 1;
            for(int j = 0; j < strlen(inputstr); j++){
                if(fileStr[i + j] != inputstr[j]){
                    match = 0;
                    break;
                }
            }
            if(match == 1){
                if(count || at){
                    counter++;

                    if(at && atNum == counter){
                        if(byword){
                            printf("%d ", wordCounter);
                        }
                        else{
                            printf("%d ", i);
                        }
                    }
                }
                else{
                    if(byword){
                            printf("%d ", wordCounter);
                        }
                        else{
                            printf("%d ", i);
                    }
                    if(all == 0) break;
                }
            }
        }
    }
    if(count && at == 0){
        printf("%d\n", counter);
    }
    else if(at && atNum > counter){
        printf("-1\n");
    }
    else{
        printf("\n");
    }
    fclose(ptr);
}

void ReplaceWildCard(char* dirname, char* str1, char* str2, int all, int at, int atNum){

    FILE* ptr;
    ptr = fopen(dirname, "a+");

    int matchCounter = 0;

    if(ptr == NULL){
        printf("File not found\n");
        return;
    }

    dirname[0] = 't';
    dirname[1] = 'e';
    dirname[2] = 'm';
    dirname[3] = 'p';

    FILE* tempPtr;
    tempPtr = fopen(dirname, "w");

    char* fileStr = readFile(ptr);

    fputs(fileStr, tempPtr);
    fclose(tempPtr);

    char* finalStr = malloc(sizeof(char) * lenght);

    int index = 0;

    int wildCardLenght = 0;

    for(int i = 0; i < strlen(fileStr); i++)
    {
        if(str1[0] == fileStr[i]){

            int match = 1;
            int secIndex = 0;

            for(int j = 0; j < strlen(str1); j++)
            {
                if(str1[j] == '*'){
                    if(j == strlen(str1) - 1)
                    {
                        while(fileStr[i + secIndex] != ' '){
                            secIndex++;
                            wildCardLenght++;
                        }
                        break;
                    }
                    while(fileStr[i + secIndex] != str1[j + 1]){
                        secIndex++;
                        wildCardLenght++;

                        if(fileStr[i + secIndex] == ' '){
                            match = 0;
                            break;
                        }

                        if(i + secIndex == strlen(str1)){
                            match = 0;
                            break;
                        }
                    }
                }
                else{
                    if(str1[j] != fileStr[i + secIndex]){
                        match = 0;
                        break;
                    }
                    secIndex++;
                }
            }
            if(match == 1){

                matchCounter++;

                if((all) || (at && atNum == matchCounter) || (at == 0 && all == 0 && matchCounter == 1)){
                    for(int j = 0; j < strlen(str2); j++){
                        finalStr[index] = str2[j];
                        index++;
                    }
                    i = i + wildCardLenght + strlen(str1) - 2;
                    wildCardLenght = 0;
                }
                else{
                    finalStr[index] = fileStr[i];
                    index++;
                }
            }
        }
        else{
            finalStr[index] = fileStr[i];
            index++;
        }
    }
    dirname[0] = 'r';
    dirname[1] = 'o';
    dirname[2] = 'o';
    dirname[3] = 't';

    finalStr[index] = '\0';

    ptr = fopen(dirname, "w");
    fputs(finalStr, ptr);

    printf("%s", finalStr);
    printf("\n");

    fclose(ptr);
}

void Replace(char* dirname, char* str1, char* str2, int all, int at, int atNum){

    int wildCard = 0;

    for(int i = 0; i < strlen(str1); i++){
        if(str1[i] == '*'){
            if(i == 0){
                wildCard = 1;
                break;
            }
            else{
                if(str1[i - 1] != '\\'){
                    wildCard = 1;
                    break;
                }
            }
        }
    }
    if(wildCard){
        ReplaceWildCard(dirname, str1, str2, all, at, atNum);
        return;
    }

    FILE* ptr;
    ptr = fopen(dirname, "a+");

    int matchCounter = 0;

    if(ptr == NULL){
        printf("File not found\n");
        return;
    }

    dirname[0] = 't';
    dirname[1] = 'e';
    dirname[2] = 'm';
    dirname[3] = 'p';

    FILE* tempPtr;
    tempPtr = fopen(dirname, "w");

    char* fileStr = readFile(ptr);

    fputs(fileStr, tempPtr);
    fclose(tempPtr);

    char* finalStr = malloc(sizeof(char) * lenght);

    int index = 0;

    for(int i = 0; i < strlen(fileStr); i++)
    {
        if(str1[0] == fileStr[i]){
            int match = 1;
            for(int j = 0; j < strlen(str1); j++){
                if(fileStr[i + j] != str1[j]){
                    match = 0;
                    break;
                }
            }
            if(match == 1){

                matchCounter++;

                if((all) || (at && atNum == matchCounter) || (at == 0 && all == 0 && matchCounter == 1)){
                    for(int j = 0; j < strlen(str2); j++){
                        finalStr[index] = str2[j];
                        index++;
                    }
                    i = i + strlen(str1) - 1;
                }
                else{
                    finalStr[index] = fileStr[i];
                    index++;
                }
            }
        }
        else{
            finalStr[index] = fileStr[i];
            index++;
        }
    }
    dirname[0] = 'r';
    dirname[1] = 'o';
    dirname[2] = 'o';
    dirname[3] = 't';

    finalStr[index] = '\0';

    ptr = fopen(dirname, "w");
    fputs(finalStr, ptr);

    printf("%s", finalStr);
    printf("\n");

    fclose(ptr);
}

void Grep(int count, char directories[count][lenght], int l, int c, char* pattern){

    int lineCounter = 0;

    for(int i = 0; i < count; i++){

        FILE* ptr;
        ptr = fopen(removeFirstChar(directories[i]), "a+");

        if(ptr == NULL){
            printf("File Not Found\n");
            return;
        }
        if(c == 0 && l == 0) printf("%s:\n", directories[i]);
        char* fileStr = readFile(ptr);

        char currentLine[lenght];
        int lineIndex = 0, lineMatch = 0;

        int fileMatch = 0;

        for(int j = 0; j < strlen(fileStr); j++){

            if(fileStr[j] == '\n' || fileStr[j] == EOF || fileStr[j] == NULL){

                lineIndex = 0;

                if(lineMatch){
                    if(c == 0 && l == 0){
                        DisplayString(currentLine);
                        printf("\n");
                        lineMatch = 0;
                    }
                    else{
                        if(l == 1){
                            fileMatch = 1;
                        }
                        if(c == 1){
                            lineCounter++;
                        }
                    }
                }
                for(int k = 0; k < lenght; k++) currentLine[k] = NULL;
            }
            else{
                currentLine[lineIndex] = fileStr[j];
                lineIndex++;
            }

            if(pattern[0] == fileStr[j]){
                int match = 1;
                for(int k = 0; k < strlen(pattern); k++){
                    if(fileStr[k + j] != pattern[k]){
                        match = 0;
                        break;
                    }
                }
                if(match == 1){
                    lineMatch = 1;
                }
            }
        }
        if(c == 0 && l == 0){
            if(lineMatch){
                DisplayString(currentLine);
                printf("\n");
                lineMatch = 0;
            }
        }else if(l == 1){
            if(fileMatch){
                printf("%s\n", directories[i]);
            }
        }

        fclose(ptr);
    }
    if(c == 1){
        printf("%d\n", lineCounter);
    }
}

void autoIndent(char* dirname){

    FILE* ptr;
    ptr = fopen(dirname, "a+");

    if(ptr == NULL){
        printf("File not found\n");
        return;
    }

    dirname[0] = 't';
    dirname[1] = 'e';
    dirname[2] = 'm';
    dirname[3] = 'p';

    FILE* tempPtr;
    tempPtr = fopen(dirname, "w");

    char* fileStr = readFile(ptr);

    fputs(fileStr, tempPtr);
    fclose(tempPtr);

    char* finalStr = malloc(sizeof(char) * lenght);

    int index = 0;
    int tabCounter = 0;

    int newLine = 0;
    char lastChar = NULL;

    for(int i = 0; i < strlen(fileStr); i++)
    {
        if(fileStr[i] == NULL || fileStr[i] == EOF) break;

        if(fileStr[i] != '\n')
        {
            if(fileStr[i] == '{'){

                if(newLine){
                    for(int j = 0; j < tabCounter * 4; j++){
                        finalStr[index] = ' ';
                        index++;
                    }
                    newLine = 0;
                }

                tabCounter++;

                if(index == 0){
                }
                else if(finalStr[index - 1] == ' ' || finalStr[index - 1] == '\n'){
                }
                else{
                    finalStr[index] = ' ';
                    index++;
                }

                finalStr[index] = fileStr[i];
                index++;
                finalStr[index] = '\n';
                index++;

                newLine = 1;
            }
            else if(fileStr[i] == '}'){

                tabCounter--;

                if(lastChar == '{'){
                    finalStr[index] = '\n';
                    index++;
                }

                if(newLine){
                    for(int j = 0; j < tabCounter * 4; j++){
                        finalStr[index] = ' ';
                        index++;
                    }
                    newLine = 0;
                }
                finalStr[index] = fileStr[i];
                index++;
                finalStr[index] = '\n';
                index++;

                newLine = 1;
            }
            else if(fileStr[i] == ';'){

                if(newLine){
                    for(int j = 0; j < tabCounter * 4; j++){
                        finalStr[index] = ' ';
                        index++;
                    }
                    newLine = 0;
                }

                finalStr[index] = fileStr[i];
                index++;
                finalStr[index] = '\n';
                index++;

                newLine = 1;
            }
            else{
                if(fileStr[i] == ' ' && newLine){

                }
                else{
                    if(newLine){
                        for(int j = 0; j < tabCounter * 4; j++){
                            finalStr[index] = ' ';
                            index++;
                        }
                        newLine = 0;
                    }

                    finalStr[index] = fileStr[i];
                    index++;
                }
            }
        }
        if(fileStr[i] != ' ' && fileStr[i] != '\n') lastChar = fileStr[i];
    }
    dirname[0] = 'r';
    dirname[1] = 'o';
    dirname[2] = 'o';
    dirname[3] = 't';

    ptr = fopen(dirname, "w");

    finalStr[index] = '\0';
    fputs(finalStr, ptr);

    printf("%s", finalStr);
    printf("\n");

    fclose(ptr);
}

int analyzeLines(char lineOne[lenght], char lineTwo[lenght]){

    int wordOne = 0, lenghtOne = strlen(lineOne);
    int wordTwo = 0, lenghtTwo = strlen(lineTwo);

    for(int i = 0; i < lenghtOne; i++){
        if(lineOne[i] == ' '){
            wordOne++;
        }
    }
    wordOne++;

    for(int i = 0; i < lenghtTwo; i++){
        if(lineTwo[i] == ' '){
            wordTwo++;
        }
    }
    wordTwo++;

    if(wordOne != wordTwo) return -1;

    char wOne[wordOne][lenght];

    for(int i = 0; i < wordOne; i++){
        for(int j = 0; j < lenght; j++){
            wOne[i][j] = NULL;
        }
    }
    char wTwo[wordTwo][lenght];

    for(int i = 0; i < wordTwo; i++){
        for(int j = 0; j < lenght; j++){
            wTwo[i][j] = NULL;
        }
    }

    int temp1 = 0, temp2 = 0;
    int index1 = 0, index2 = 0;

    for(int i = 0; i < strlen(lineOne); i++){
        if(lineOne[i] == ' '){
            temp1++;
            index1 = 0;
        }
        else{
            wOne[temp1][index1] = lineOne[i];
            index1++;
        }
    }

    for(int i = 0; i < strlen(lineTwo); i++){
        if(lineTwo[i] == ' '){
            temp2++;
            index2 = 0;
        }
        else{
            wTwo[temp2][index2] = lineTwo[i];
            index2++;
        }
    }
    int diffs = 0;

    for(int i = 0; i < wordOne; i++){
        if(strcmp(wOne[i], wTwo[i]) != 0){
            diffs++;
        }
    }

    if(diffs != 1)
        return -1;

    int index = 0;

    for(int i = 0; i < wordOne; i++){
        if(strcmp(wOne[i], wTwo[i]) != 0){
            index = i;
        }
    }

    for(int i = 0; i < wordOne; i++){
        if(i != index){
            printf("%s ", wOne[i]);
        }
        else{
            printf(">>%s<< ", wOne[i]);
        }
    }
    printf("\n");

    for(int i = 0; i < wordTwo; i++){
        if(i != index){
            printf("%s ", wTwo[i]);
        }
        else{
            printf(">>%s<< ", wTwo[i]);
        }
    }

    printf("\n");
    return 0;
}

void compare(char* dir1, char* dir2){

    FILE* ptr1;
    ptr1 = fopen(dir1, "r");

    if(ptr1 == NULL){
        printf("File one not found\n");
        return;
    }

    FILE* ptr2;
    ptr2 = fopen(dir2, "r");

    if(ptr2 == NULL){
        printf("File two not found\n");
        return;
    }

    char* fileOneStr = readFile(ptr1);
    char* fileTwoStr = readFile(ptr2);

    int fileOneLines = 1;
    int fileTwoLines = 1;

    int index = 0;

    for(int i = 0; i < strlen(fileOneStr); i++){
        if(fileOneStr[i] == '\n')
            fileOneLines++;
    }
    for(int i = 0; i < strlen(fileTwoStr); i++){
        if(fileTwoStr[i] == '\n')
            fileTwoLines++;
    }

    char fileOne[fileOneLines][lenght];

    for(int i = 0; i < fileOneLines; i++){
        for(int j = 0; j < lenght; j++){
            fileOne[i][j] = NULL;
        }
    }
    char fileTwo[fileTwoLines][lenght];

    for(int i = 0; i < fileTwoLines; i++){
        for(int j = 0; j < lenght; j++){
            fileTwo[i][j] = NULL;
        }
    }

    int temp1 = 0, temp2 = 0;
    int index1 = 0, index2 = 0;

    for(int i = 0; i < strlen(fileOneStr); i++){
        if(fileOneStr[i] == '\n'){
            temp1++;
            index1 = 0;
        }
        else{
            fileOne[temp1][index1] = fileOneStr[i];
            index1++;
        }
    }

    for(int i = 0; i < strlen(fileTwoStr); i++){
        if(fileTwoStr[i] == '\n'){
            temp2++;
            index2 = 0;
        }
        else{
            fileTwo[temp2][index2] = fileTwoStr[i];
            index2++;
        }
    }
    int minLines = fileOneLines;
    if(fileTwoLines < fileOneLines) minLines = fileTwoLines;

    for(int i = 0; i < minLines; i++){
        if(strcmp(fileOne[i], fileTwo[i]) != 0){

            printf("======#%d======\n", i + 1);
            int analyze = analyzeLines(fileOne[i], fileTwo[i]);

            if(analyze == -1){
                printf("%s\n", fileOne[i]);
                printf("%s\n", fileTwo[i]);
            }
        }
    }
    if(fileOneLines == fileTwoLines){
        printf("\n");
        return;
    }

    if(fileOneLines > fileTwoLines){
        printf(">>>>>>>>>#%d - #%d>>>>>>>>>>>\n", minLines + 1, fileOneLines);
        for(int i = minLines; i < fileOneLines; i++){
            printf("%s\n", fileOne[i]);
        }
    }
    else{
        printf(">>>>>>>>>#%d - #%d>>>>>>>>>>>\n", minLines + 1, fileTwoLines);
        for(int i = minLines; i < fileTwoLines; i++){
            printf("%s\n", fileTwo[i]);
        }
    }
    fclose(ptr1);
    fclose(ptr2);
}

void tree(char path[], int root, const int mainroot){

    DIR *directory;
    struct dirent *entry;
    directory = opendir(path);

    if(directory == NULL)
    {
        printf("Directory Not Found");
        return 1;
    }

    while((entry = readdir(directory)) != NULL)
    {
        if(!strcmp((entry->d_name),"."))
            continue;
        if(!strcmp((entry->d_name),".."))
            continue;

        printf("├");
        strcat(arman_str,"├");
        for(int i = 0;i<mainroot-root+1;i++)
        {
            printf("──");
        }
        if(entry->d_type == DT_DIR)
        {
            printf(" %s:\n",entry->d_name);
            strcat(arman_str,entry->d_name);
            strcat(arman_str,":\n");
        }

        else
        {
            printf(" %s\n",entry->d_name);
            strcat(arman_str,entry->d_name);
            strcat(arman_str,"\n");
        }


        if(entry->d_type == DT_DIR && root > 0)
        {
            char newpath[maxl];
            int n = strlen(path);
            for(int i = 0;i<n;i++)
            {
                newpath[i] = path[i];
            }
            newpath[n] = '/';
            for(int i = 0;i<strlen(entry->d_name);i++)
            {
                newpath[i+n+1] = (entry->d_name)[i];
            }
            newpath[n+strlen(entry->d_name)+1] = '\0';
            tree(newpath,root-1,mainroot);
        }
    }
    closedir(directory);
}

void Undo(char* dirname){

    FILE* ptr;
    ptr = fopen(dirname, "w");

    if(ptr == NULL){
        printf("File not found\n");
        return;
    }

    dirname[0] = 't';
    dirname[1] = 'e';
    dirname[2] = 'm';
    dirname[3] = 'p';

    FILE* tempPtr;
    tempPtr = fopen(dirname, "r");

    char *fileStr = readFile(tempPtr);

    fputs(fileStr, ptr);

    fclose(ptr);
    fclose(tempPtr);
}

int main(){

    while(1){
        char inp[lenght];
        scanf("%s", inp);

        getOrder(inp);
    }
}
