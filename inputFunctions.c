#include <stdio.h>
#include <direct.h>

void getOrder(char inp[]){

    if(strcmp(inp, "createfile") == 0){
        char temp[lenght];
        scanf("%s", temp);

        if(strcmp(temp, "-file") == 0)
        {
            char* dirname = getString(1);
            createFile(removeFirstChar(dirname), 0);

            //Create Temp file for undo
            dirname[1] = 't';
            dirname[2] = 'e';
            dirname[3] = 'm';
            dirname[4] = 'p';

            createFile(removeFirstChar(dirname), 1);
        }
    }
    if(strcmp(inp, "insertstr") == 0){
        char temp[lenght];
        scanf("%s", temp);

        if(strcmp(temp, "-file") == 0)
        {
            char* dirname = getString(1);
            InsertStrInput(removeFirstChar(dirname));
        }
    }
    if(strcmp(inp, "cat") == 0){
        catInput();
    }
    if(strcmp(inp, "removestr") == 0){
        char temp[lenght];
        scanf("%s", temp);

        if(strcmp(temp, "-file") == 0)
        {
            char* dirname = getString(1);
            removeStrInput(removeFirstChar(dirname));
        }
    }
    if(strcmp(inp, "copystr") == 0){
        char temp[lenght];
        scanf("%s", temp);

        if(strcmp(temp, "-file") == 0)
        {
            char* dirname = getString(1);
            copyStrInput(removeFirstChar(dirname));
        }
    }
    if(strcmp(inp, "cutstr") == 0){
        char temp[lenght];
        scanf("%s", temp);

        if(strcmp(temp, "-file") == 0)
        {
            char* dirname = getString(1);
            cutStrInput(removeFirstChar(dirname));
        }
    }
    if(strcmp(inp, "pastestr") == 0){
        char temp[lenght];
        scanf("%s", temp);

        if(strcmp(temp, "-file") == 0)
        {
            char* dirname = getString(1);
            pasteStrInput(removeFirstChar(dirname));
        }
    }
    if(strcmp(inp, "find") == 0){
        char temp[lenght];
        scanf("%s", temp);

        if(strcmp(temp, "-str") == 0)
        {
            char* inputstr = getString(1);
            findInput(inputstr);
        }
    }
    if(strcmp(inp, "replace") == 0){
        ReplaceInput();
    }
    if(strcmp(inp, "grep") == 0){
        GrepInput();
    }
    if(strcmp(inp, "auto-indent") == 0){
        AutoIndentInput();
    }
    if(strcmp(inp, "compare") == 0){
        compareInput();
    }
    if(strcmp(inp, "tree") == 0){
        treeInput();
    }
    if(strcmp(inp, "undo") == 0){
        undoInput();
    }
}

void armanOrder(){
    char inp[lenght];
    scanf("%s", inp);

    if(strcmp(inp, "insertstr") == 0){
        ArmanInsert();
    }
}

void ArmanInsert(){

    char temp[lenght];
    scanf("%s", temp);

    if(strcmp(temp, "-file") != 0){
        printf("Invalid Input\n");
        return;
    }
    char* dirname = getString(1);

    scanf("%s", temp);

    if(strcmp(temp, "-pos") != 0){
        printf("Invalid Input\n");
        return;
    }
    int line, character;
    scanf("%d:%d", &line, &character);

    FILE* arPtr;
    arPtr = fopen("arman.txt", "r");

    char* inputStr = readFile(arPtr);
    InsertStr(removeFirstChar(dirname), inputStr, line, character);
}

void catInput(){

    char temp[lenght];
    scanf("%s", temp);

    if(strcmp(temp, "-file") != 0)
    {
        printf("Invid Input\n");
        return;
    }
    char* dirname = getString(0);

    if(dirname[strlen(dirname) - 1] == '\n'){
        cat(removeFirstAndLastChar(dirname), 0);
    }

    char arman[lenght];
    scanf("%s", arman);

    if(strcmp(arman, "=D") != 0){
        printf("Invalid Input\n");
        return;
    }
    cat(removeFirstAndLastChar(dirname), 1);
}

void undoInput(){

    char temp[lenght];
    scanf("%s", temp);

    if(strcmp(temp, "-file") != 0){
        printf("Invalid Input\n");
        return;
    }

    char* dirname = getString(1);
    Undo(removeFirstChar(dirname));
}

void treeInput(){

    int depth;
    scanf("%d", depth);

    tree("tree", depth, depth);
}

void compareInput(){

    char temp[lenght];
    scanf("%s", temp);

    if(strcmp(temp, "-files") != 0){
        printf("Invalid Input\n");
        return;
    }

    char* dir1 = getString(1);
    char* dir2 = getString(1);

    compare(removeFirstChar(dir1), dir2);
}

void AutoIndentInput(){

    char temp[lenght];
    scanf("%s", temp);

    if(strcmp(temp, "-file") != 0){
        printf("Invalid Input\n");
        return;
    }

    char* dirname = getString(1);

    autoIndent(removeFirstChar(dirname));
}

void GrepInput(){

    int c = 0, l = 0;

    char temp[lenght];
    scanf("%s", temp);

    char* inputstr;

    if(strcmp(temp, "-l") == 0){

        l++;
        scanf("%s", temp);

        if(strcmp(temp, "-str") == 0){
            inputstr = getString(1);
        }
        else{
            printf("Invalid Input\n");
            return;
        }
    }
    else if(strcmp(temp, "-c") == 0){

        c++;
        scanf("%s", temp);

        if(strcmp(temp, "-str") == 0){
            inputstr = getString(1);;
        }
        else{
            printf("Invalid Input\n");
            return;
        }
    }
    else if(strcmp(temp, "-str") == 0){
        inputstr = getString(1);
    }
    else{
        printf("Invalid Input\n");
        return;
    }

    scanf("%s", temp);

    if(strcmp(temp, "-files") != 0){
        printf("Invalid Input\n");
        return;
    }

    char ch;
    char directories[10][lenght];

    int count = 0;

    do{
        scanf("%s", directories[count]);
        count++;

        ch = getchar();

    } while(ch != '\n');

    Grep(count, directories, l, c, inputstr);
}

void ReplaceInput(){

    char temp[lenght];
    scanf("%s", temp);

    if(strcmp(temp, "-str1") != 0){
        printf("Invalid Input\n");
        return;
    }

    //char str1[lenght];
    //scanf("%s", str1);
    char* str1 = getString(1);

    scanf("%s", temp);

    if(strcmp(temp, "-str2") != 0){
        printf("Invalid Input\n");
        return;
    }

    //char str2[lenght];
    //scanf("%s", str2);
    char* str2 = getString(1);

    scanf("%s", temp);

    if(strcmp(temp, "-file") != 0){
        printf("Invalid Input\n");
        return;
    }

    //char dirname[lenght];
    //scanf("%s", dirname);

    char* dirname = getString(0);

    int at = 0, all = 0, atNum = 0, invalidInput = 0;

    char c;

    if(dirname[strlen(dirname) - 1] == '\n'){
        Replace(removeFirstAndLastChar(dirname), str1, str2, 0, 0, 0);
    }

    do{
        char temp2[lenght];
        scanf("%s", temp2);

        if(strcmp(temp2, "-at") == 0){
            at++;

            if(at == 1)
                scanf("%d", &atNum);
            else{
                invalidInput = 1;
                break;
            }
        }
        if(strcmp(temp2, "-all") == 0){
            all++;

            if(all > 1){
                invalidInput = 1;
                break;
            }
        }

        c = getchar();

    }while(c != '\n');

    if(invalidInput != 0){
        printf("Invalid Input\n");
        return;
    }

    if(at){
        if(all){
            printf("Invalid Input\n");
            return;
        }
    }
    Replace(removeFirstAndLastChar(dirname), str1, str2, all, at, atNum);
}

void findInput(char* inputstr){

    char temp[lenght];
    scanf("%s", temp);

    if(strcmp(temp, "-file") != 0){
        printf("Invalid Input\n");
        return;
    }

    char* dirname = getString(0);

    int count = 0, at = 0, byword = 0, all = 0;
    int atNum;

    int invalidInput = 0;

    if(dirname[strlen(dirname) - 1] == '\n'){
        find(removeFirstAndLastChar(dirname), inputstr, 0, 0, 0, 0, 0);
        return;
    }

    char c;

    do{
        char temp2[lenght];
        scanf("%s", temp2);

        if(strcmp(temp2, "-at") == 0){
            at++;

            if(at == 1)
                scanf("%d", &atNum);
            else{
                invalidInput = 1;
                break;
            }
        }
        if(strcmp(temp2, "-count") == 0){
            count++;

            if(count > 1){
                invalidInput = 1;
                break;
            }
        }
        if(strcmp(temp2, "-byword") == 0){
            byword++;

            if(byword > 1){
                invalidInput = 1;
                break;
            }
        }
        if(strcmp(temp2, "-all") == 0){
            all++;

            if(all > 1){
                invalidInput = 1;
                break;
            }
        }

        c = getchar();

    } while(c != '\n');

    if(invalidInput != 0){
        printf("Invalid Input\n");
        return;
    }

    //check for invalid inputs
    if(count){
        if(at || all || byword){
            printf("Invalid Input\n");
            return;
        }
    }
    if(at){
        if(all){
            printf("Invalid Input\n");
            return;
        }
    }

    find(removeFirstAndLastChar(dirname), inputstr, count, at, byword, all, atNum);
}

void InsertStrInput(char* dirname){

    char temp[lenght];
    scanf("%s", temp);

    if(strcmp(temp, "-str") != 0){
        printf("Invalid Input\n");
        return;
    }

    //char str[lenght];
    //scanf("%s", str);
    char* str = getString(1);

    char temp2[lenght];
    scanf("%s", temp2);

    if(strcmp(temp2, "-pos") != 0){
        printf("Invalid Input\n");
        return;
    }

    int line, character;
    scanf("%d:%d", &line, &character);

    InsertStr(dirname, str, line, character);
}

void removeStrInput(char* dirname){

    char temp1[lenght];
    scanf("%s", temp1);

    if(strcmp(temp1, "-pos") != 0){
        printf("Invalid Input pos\n");
        return;
    }

    int line, character;
    scanf("%d:%d", &line, &character);

    char temp2[lenght];
    scanf("%s", temp2);

    if(strcmp(temp2, "-size") != 0){
        printf("Invalid Input size\n");
        return;
    }

    int strLenght;
    scanf("%d", &strLenght);

    char direction[lenght];
    scanf("%s", direction);

    if(strcmp("-b", direction) != 0 && strcmp("-f", direction) != 0){
        printf("Invalid Input direction\n");
        return;
    }
    int flag = 0;
    if(strcmp("-f", direction) == 0) flag = 1;

    removeStr(dirname, line, character, strLenght, flag);
}

void cutStrInput(char* dirname){

    char temp1[lenght];
    scanf("%s", temp1);

    if(strcmp(temp1, "-pos") != 0){
        printf("Invalid Input pos\n");
        return;
    }

    int line, character;
    scanf("%d:%d", &line, &character);

    char temp2[lenght];
    scanf("%s", temp2);

    if(strcmp(temp2, "-size") != 0){
        printf("Invalid Input size\n");
        return;
    }

    int strLenght;
    scanf("%d", &strLenght);

    char direction[lenght];
    scanf("%s", direction);

    if(strcmp("-b", direction) != 0 && strcmp("-f", direction) != 0){
        printf("Invalid Input direction\n");
        return;
    }
    int flag = 0;
    if(strcmp("-f", direction) == 0) flag = 1;

    cutStr(dirname, line, character, strLenght, flag);
}

void copyStrInput(char* dirname){

    char temp1[lenght];
    scanf("%s", temp1);

    if(strcmp(temp1, "-pos") != 0){
        printf("Invalid Input pos\n");
        return;
    }

    int line, character;
    scanf("%d:%d", &line, &character);

    char temp2[lenght];
    scanf("%s", temp2);

    if(strcmp(temp2, "-size") != 0){
        printf("Invalid Input size\n");
        return;
    }

    int strLenght;
    scanf("%d", &strLenght);

    char direction[lenght];
    scanf("%s", direction);

    if(strcmp("-b", direction) != 0 && strcmp("-f", direction) != 0){
        printf("Invalid Input direction\n");
        return;
    }
    int flag = 0;
    if(strcmp("-f", direction) == 0) flag = 1;

    copyStr(dirname, line, character, strLenght, flag);
}

void pasteStrInput(char* dirname){

    char temp1[lenght];
    scanf("%s", temp1);

    if(strcmp(temp1, "-pos") != 0){
        printf("Invalid Input pos\n");
        return;
    }

    int line, character;
    scanf("%d:%d", &line, &character);

    pasteStr(dirname, line, character);
}
