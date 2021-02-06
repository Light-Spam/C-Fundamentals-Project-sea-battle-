#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_SHIP_SIZE 10

typedef struct shipNode {
    // H = healthy    D = damaged    E = exploded
    char fullStatus;

    // size of ship = 1*size
    int size;

    // H = Horizontal   V = Vertical
    char pos;

    // location of every part (later will be all set to -1)
    int x[MAX_SHIP_SIZE];
    int y[MAX_SHIP_SIZE];


    // Pointer to next ship structure
    struct shipNode *nextShip;
} buildShip;


// bans the area around the ship
//                       WARNING: pos of ships should be set corectly
void banLocation(struct shipNode ship, char position, int row, int cols, char sea[row][cols]) {

    int tx, ty;
    if (position == 'H') {
        tx = ship.x[0];
        ty = ship.y[0];

        // banning left and right block
        if ((tx - 1 >= 0) && (ty >= 0)) {
            sea[tx - 1][ty] = 'b';
        }

        if ((tx + ship.size >= 0) && (ty >= 0)) {
            sea[tx + ship.size][ty] = 'b';
        }

        //banning above  line
        for (int a = 0; a <= ship.size + 1; a++) {
            if (((tx - 1) + a <= 0) || (ty - 1) <= 0) continue;
            sea[(tx - 1) + a][ty - 1] = 'b';
        }

    }
    // baning bot line
    for (int a = 0; a <= ship.size + 1; a++) {
        if (ty + 1 <= 0) continue;
        sea[(tx - 1) + a][ty + 1] = 'b';

    }

    if (position == 'V') {
        tx = ship.x[0];
        ty = ship.y[0];
        // ban top block
        if ((tx >= 0) && (ty - 1 >= 0)) {
            sea[tx][ty - 1] = 'b';
        }

        // ban bot block
        if ((tx >= 0) && (ty + ship.size >= 0)) {
            sea[tx][ty + ship.size] = 'b';
        }

        // ban side lines
        for (int a = 0; a <= ship.size + 1; a++) {
            if (((ty - 1) + a <= 0) || (tx - 1) <= 0) continue;
            sea[(tx - 1)][(ty - 1) + a] = 'b';
        }
        
        for (int a = 0; a <= ship.size + 1; a++) {
            if (ty + 1 <= 0) continue;
            sea[(tx + 1)][((ty - 1) + a)] = 'b';
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

// makes the sea and set every block to "."
void makeDefaultStatusArray(int rows, int cols, char sea[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sea[i][j] = '.';
        }
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


int main() {

    char testSea[10][10];

    makeDefaultStatusArray(10, 10, testSea);
    drawMap(10, 10, testSea);


    buildShip testShip;
    testShip.x[0] = 0;
    testShip.x[1] = 0;
    testShip.x[2] = 0;
    testShip.y[0] = 2;
    testShip.y[1] = 3;
    testShip.y[2] = 4;
    testShip.pos = 'V';
    testShip.size = 3;

    testSea[0][2] = 's';
    testSea[0][3] = 's';
    testSea[0][4] = 's';
    drawMap(10, 10, testSea);
    banLocation(testShip, testShip.pos, 10, 10, testSea);
    drawMap(10, 10, testSea);


    getchar();
    return 0;
}