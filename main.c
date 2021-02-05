#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


void TextBlue (){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_GREEN |
                            FOREGROUND_BLUE);
}
void TextYELLOW (){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_RED|FOREGROUND_GREEN);
}
void TextRed (){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_RED);
}

void makeDefaultStatusArray( int rows, int cols,char StatusArray[rows][cols]){
    for ( int i = 0 ; i < rows ; i++){
        for ( int j = 0 ; j<cols ; j++){
            StatusArray[i][j] = 'W';
        }
    }
}
void drawMap (int rows,int cols,char StatusArray[rows][cols]){
    char sp = ' ';

// Line 1 Alphabets
    printf("%c%c%c%c",sp, sp,sp,sp);
    for ( int a = 0 ; a < cols ; a++){
        TextYELLOW();
        printf("%c%c%c%c%c%c%c%c", 65+a ,sp,sp,sp,sp,sp,sp,sp);
        fflush(stdout);
    }printf("\n");
    TextBlue();
//first row (3 lines) with no number
    for (int b = 0 ; b < rows ; b++) {


        // Seprator Line after 3 lines in one row
        for (int a = 0; a < cols; a++) {
            printf(" -------");
            fflush(stdout);
        }printf("\n");

        //row 1 line 1 / 3
        printf("|");
        for (int a = 0; a < cols; a++) {
            printf("%c%c%c%c%c%c%c|", sp, sp, sp, sp, sp, sp, sp);
            fflush(stdout);
        }printf("\n");

        //row 1 line 2 / 3
        TextYELLOW();
        printf("%d", b);
        fflush(stdout);
        TextBlue();
        fflush(stdout);
        for (int a = 0; a < cols; a++) {
            char ship=StatusArray[b][a];  //---------------------------------CHARACTER IS HERE
            printf("%c%c%c%c%c%c%c|", sp, sp, sp, ship, sp, sp, sp );
            fflush(stdout);
        }printf("\n");
        //row 1 line 3/3
        printf("|");
        for (int a = 0; a < cols; a++) {
            printf("%c%c%c%c%c%c%c|", sp, sp, sp, sp, sp, sp, sp );
            fflush(stdout);
        }printf("\n");
    }
    // Last line --- ( out of loop)
    for (int a = 0; a < cols; a++) {
        printf(" -------");
        fflush(stdout);
    }printf("\n");





}





int main() {
    char FirstArray[5][5];

    makeDefaultStatusArray(5,5,FirstArray);
    FirstArray[2][2]='K';
    drawMap(5,5,FirstArray);


    return 0;
}