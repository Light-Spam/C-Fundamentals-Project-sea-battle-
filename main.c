#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "BaseMethods.h"
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