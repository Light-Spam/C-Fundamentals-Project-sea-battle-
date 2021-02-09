#define D 845


// makes the sea and set every block to " "
void makeDefaultSeaArray(int rows, int cols, char sea[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sea[i][j] = ' ';
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
    setColor('n');

}

// bans the area around the ship
//                       WARNING: pos of ships should be set correctly
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

void printShipDataForUser(acc* user,int mapX,int mapY,char user1Sea[mapX][mapY],int shipSizeArr[10]){

    printf("\n\n\nThis is your Territory, You have to defend it with your honor!\n\n\n");
    drawMap(mapX,mapY,user1Sea);

    printf("\n\n\nWe have limited recourse commander %s , but our captains do believe in you !\n"
           "Now is the time to set the position of our Army!\n ", user->username);


    //printing ships data
    printf("\nOur humble army is full of :\n");
    for (int a = 0 ; a < 10 ; a++){
        if ( shipSizeArr[a] == 0) continue;
        printf(" %d ships of %d by 1\n", shipSizeArr[a], a+1);
    }
    printf("\n\n");

}


// This method pushes the list
//Warning : Head is not representing any Ships
ship * makeShipsList(ship** listHead,acc* user, int const shipSizeArr[10]) {


    //getting the count of ships for every size
    int countOfShip = 0;
    for (int b = 0; b < 10; b++) {
        if (shipSizeArr[b] == 0) continue;
        countOfShip = shipSizeArr[b];


        for ( int c = 0 ; c < countOfShip ; c++) {
            ship *pNewShip = (ship *) malloc(sizeof(ship));
            if (pNewShip == NULL) {
                printf("out of memory");
            } else {
                //------------------------------------------getting ship data
                //set the coord array all to -1 for new ship
                for (int a = 0; a < MAX_SHIP_SIZE; a++) {
                    pNewShip->x[a] = -1;
                    pNewShip->y[a] = -1;
                }
                pNewShip->fullStatus = 'H';
                pNewShip->size = b+1;
                pNewShip->pos = '?';

                //adding to the end of list and setting the head on new ship we created
                pNewShip->pNextShip = *listHead;
                *listHead = pNewShip;
#if D
                setColor('G');
                printf("New Ship With size of %d and status of %c created and added to the list \n",b+1, pNewShip->fullStatus);
                fflush(stdout);
                setColor('n');
#endif

            }
        }
    }
}
