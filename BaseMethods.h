


// makes the sea and set every block to "."
void makeDefaultStatusArray(int rows, int cols, char sea[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sea[i][j] = '.';
        }
    }
}



// just changes font color.
void setColor(char chosenColor) {
    if (chosenColor == 'b' || chosenColor == 'B') {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_GREEN |
                                FOREGROUND_BLUE);
    }
    if (chosenColor == 'r' || chosenColor == 'R') {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_RED);
    }
    if (chosenColor == 'y' || chosenColor == 'Y') {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_RED | FOREGROUND_GREEN);
    }
    if (chosenColor == 'p' || chosenColor == 'P') {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_RED | FOREGROUND_BLUE);

    }

}



//                       WARNING: this method works with both banLocation and ship structure.
//                                if data's are not sync, this will fail.
void drawMap(int rows, int cols, char sea[rows][cols]) {
    char sp = ' ';

// Line 1 Numbers
    printf("%c%c%c%c", sp, sp, sp, sp);
    for (int a = 0; a < cols; a++) {
        setColor('y');
        printf("%d%c%c%c%c%c%c%c", 0 + a, sp, sp, sp, sp, sp, sp, sp);
        fflush(stdout);
    }
    printf("\n");
    setColor('p');
//first row (3 lines) with no number
    for (int b = 0; b < rows; b++) {


        // Seprator Line after 3 lines in one row
        for (int a = 0; a < cols; a++) {
            printf(" -------");
            fflush(stdout);
        }
        printf("\n");

        //row 1 line 1 / 3
        printf("|");
        for (int a = 0; a < cols; a++) {
            printf("%c%c%c%c%c%c%c|", sp, sp, sp, sp, sp, sp, sp);
            fflush(stdout);
        }
        printf("\n");

        //row 1 line 2 / 3
        setColor('y');
        printf("%d", b);
        fflush(stdout);
        setColor('p');
        fflush(stdout);

        for (int a = 0; a < cols; a++) {
            setColor('b');
            char ship = sea[a][b];  //---------------------------------CHARACTER IS HERE
            printf("%c%c%c%c%c%c%c", sp, sp, sp, ship, sp, sp, sp);
            fflush(stdout);
            setColor('p');
            printf("|");
            fflush(stdout);
            setColor('p');
        }
        printf("\n");
        //row 1 line 3/3
        printf("|");
        for (int a = 0; a < cols; a++) {
            printf("%c%c%c%c%c%c%c|", sp, sp, sp, sp, sp, sp, sp);
            fflush(stdout);
        }
        printf("\n");
    }
    // Last line --- ( out of loop)
    for (int a = 0; a < cols; a++) {
        printf(" -------");
        fflush(stdout);
    }
    printf("\n");

}

