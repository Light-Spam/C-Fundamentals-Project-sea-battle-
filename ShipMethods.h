#define D 0

#include <math.h>

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
void drawCusMap(int rows, int cols, char sea[rows][cols]) {
    char sp = ' ';
    int z = 0;// Line 1 Numbers

    for (int a = 0; a < cols; a++) {
        setColor('p');
        fflush(stdout);
        printf("----");
        fflush(stdout);
        setColor('y');
        fflush(stdout);
        printf("%d", a);
        fflush(stdout);
        setColor('p');
        fflush(stdout);
        printf("---");
        fflush(stdout);
    }
    setColor('p');
//first row (3 lines) with no number
    for (int b = 0; b < rows; b++) {


// Seprator Line after 3 lines in one row
        if (z != 0) {
            for (int a = 0; a < cols; a++) {
                printf(" -------");
                fflush(stdout);
            }
        }
        z++;
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

        int k = 0;
        for (int a = 0; a < cols ; a++) {
            setColor('b');
            char ship = sea[a][b];  //---------------------------------CHARACTER IS HERE
            printf("%c%c%c%c%c%c%c", sp, sp, sp, ship, sp, sp, sp);
            fflush(stdout);
            setColor('p');
            if (k < cols -1) {
                printf("|");
                fflush(stdout);
                k++;
            }
        }


        fflush(stdout);
        setColor('y');
        fflush(stdout);
        printf("%d", b);
        fflush(stdout);
        setColor('p');
        fflush(stdout);
        printf("\n");
        //row 1 line 3/3
        printf("|");
        for (int a = 0; a < cols; a++) {
            printf("%c%c%c%c%c%c%c|", sp, sp, sp, sp, sp, sp, sp);
            fflush(stdout);
        }
        printf("\n");
    }
    char srt[5] = "----";
    int k = 0;
    // Last line --- ( out of loop)
    for (int a = 0; a < cols; a++) {
        setColor('p');
        if (k == 0) {
            k++;
            srt[5] = " ---";
        }
        fflush(stdout);
        printf("%s", srt);
        fflush(stdout);
        setColor('y');
        fflush(stdout);
        printf("%d", a);
        fflush(stdout);
        setColor('p');
        fflush(stdout);
        printf("---");
        fflush(stdout);
    }
    setColor('p');

    printf("\n");
    setColor('n');

}
// don't print bans
void drawOrgMap(int rows, int cols, char sea[rows][cols]) {
    char sp = ' ';
    int z = 0;// Line 1 Numbers


    for (int a = 0; a < cols; a++) {
        setColor('p');
        fflush(stdout);
        printf("----");
        fflush(stdout);
        setColor('y');
        fflush(stdout);
        printf("%d", a);
        fflush(stdout);
        setColor('p');
        fflush(stdout);
        printf("---");
        fflush(stdout);
    }
    setColor('p');
//first row (3 lines) with no number
    for (int b = 0; b < rows; b++) {


// Seprator Line after 3 lines in one row
        if (z != 0) {
            for (int a = 0; a < cols; a++) {
                printf(" -------");
                fflush(stdout);
            }
        }
        z++;
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

        int k = 0;
        for (int a = 0; a < cols ; a++) {
            setColor('b');
            char ship = sea[a][b];  //---------------------------------CHARACTER IS HERE
            if (ship == '`') ship = ' ';
            printf("%c%c%c%c%c%c%c", sp, sp, sp, ship, sp, sp, sp);
            fflush(stdout);
            setColor('p');
            if (k < cols -1) {
                printf("|");
                fflush(stdout);
                k++;
            }
        }


        fflush(stdout);
        setColor('y');
        fflush(stdout);
        printf("%d", b);
        fflush(stdout);
        setColor('p');
        fflush(stdout);
        printf("\n");
        //row 1 line 3/3
        printf("|");
        for (int a = 0; a < cols; a++) {
            printf("%c%c%c%c%c%c%c|", sp, sp, sp, sp, sp, sp, sp);
            fflush(stdout);
        }
        printf("\n");
    }
    char srt[5] = "----";
    int k = 0;
    // Last line --- ( out of loop)
    for (int a = 0; a < cols; a++) {
        setColor('p');
        if (k == 0) {
            k++;
            srt[5] = " ---";
        }
        fflush(stdout);
        printf("%s", srt);
        fflush(stdout);
        setColor('y');
        fflush(stdout);
        printf("%d", a);
        fflush(stdout);
        setColor('p');
        fflush(stdout);
        printf("---");
        fflush(stdout);
    }
    setColor('p');

    printf("\n");
    setColor('n');

}
// for battle
void drawBattleMap(int rows, int cols, char sea[rows][cols]) {
    char sp = ' ';
    int z = 0;// Line 1 Numbers


    for (int a = 0; a < cols; a++) {
        setColor('p');
        fflush(stdout);
        printf("----");
        fflush(stdout);
        setColor('y');
        fflush(stdout);
        printf("%d", a);
        fflush(stdout);
        setColor('p');
        fflush(stdout);
        printf("---");
        fflush(stdout);
    }
    setColor('p');
//first row (3 lines) with no number
    for (int b = 0; b < rows; b++) {


// Seprator Line after 3 lines in one row
        if (z != 0) {
            for (int a = 0; a < cols; a++) {
                printf(" -------");
                fflush(stdout);
            }
        }
        z++;
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

        int k = 0;
        for (int a = 0; a < cols ; a++) {
            setColor('b');
            char ship = sea[a][b];  //---------------------------------CHARACTER IS HERE
            if (ship == '`') ship = ' ';
            if (ship>= '1' && ship<='9') ship = ' ';
            if( ship == 'X'){
                setColor('r');
                fflush(stdout);
                printf("%c%c%c%c%c%c%c", sp, sp, sp, ship, sp, sp, sp);
                fflush(stdout);
                setColor('n');
                fflush(stdout);
            }
            if( ship == 'W'){
                    setColor('b');
                    fflush(stdout);
                    printf("%c%c%c%c%c%c%c", sp, sp, sp, ship, sp, sp, sp);
                    fflush(stdout);
                setColor('n');
                fflush(stdout);
            }
            if( ship == '#'){
                setColor('n');
                fflush(stdout);
                printf("%c%c%c%c%c%c%c", sp, sp, sp, ship, sp, sp, sp);
                fflush(stdout);
            }
            if( ship != '#' && ship != 'W' && ship != 'X') {
                printf("%c%c%c%c%c%c%c", sp, sp, sp, ship, sp, sp, sp);
                fflush(stdout);
            }
            setColor('p');
            if (k < cols -1) {
                printf("|");
                fflush(stdout);
                k++;
            }
        }


        fflush(stdout);
        setColor('y');
        fflush(stdout);
        printf("%d", b);
        fflush(stdout);
        setColor('p');
        fflush(stdout);
        printf("\n");
        //row 1 line 3/3
        printf("|");
        for (int a = 0; a < cols; a++) {
            printf("%c%c%c%c%c%c%c|", sp, sp, sp, sp, sp, sp, sp);
            fflush(stdout);
        }
        printf("\n");
    }
    char srt[5] = "----";
    int k = 0;
    // Last line --- ( out of loop)
    for (int a = 0; a < cols; a++) {
        setColor('p');
        if (k == 0) {
            k++;
            srt[5] = " ---";
        }
        fflush(stdout);
        printf("%s", srt);
        fflush(stdout);
        setColor('y');
        fflush(stdout);
        printf("%d", a);
        fflush(stdout);
        setColor('p');
        fflush(stdout);
        printf("---");
        fflush(stdout);
    }
    setColor('p');

    printf("\n");
    setColor('n');

}
//bans the area around the ship
//WARNING: pos of ships should be set correctly
int banOnSea(ship *ship, int mapX, int mapY, char sea[mapX][mapY]) {
    // banning 8 side of every part if it's ' ' or '`'
    int x, y;
    for (int a = 0; a < ship->size; a++) {
        x = ship->coordArray[a].x;
        y = ship->coordArray[a].y;

        //top
        if ((sea[x][y + 1] == '`' || sea[x][y + 1] == ' ') && (y + 1 >= 0 && y + 1 <= 9)) {
            sea[x][y + 1] = '`';
        }
        //bot
        if ((sea[x][y - 1] == '`' || sea[x][y - 1] == ' ') && (y - 1 >= 0 && y - 1 <= 9)) {
            sea[x][y - 1] = '`';
        }
        //left
        if ((sea[x - 1][y] == '`' || sea[x - 1][y] == ' ') && (x - 1 >= 0 && x - 1 <= 9)) {
            sea[x - 1][y] = '`';
        }
        //right
        if ((sea[x + 1][y] == '`' || sea[x + 1][y] == ' ') && (x + 1 >= 0 && x + 1 <= 9)) {
            sea[x + 1][y] = '`';
        }
        //top right
        if (((x + 1) >= 0 && (x + 1) <= 9) && ((y - 1) >= 0 && (y - 1) <= 9)) {
            if (sea[x + 1][y - 1] == '`' || sea[x + 1][y - 1] == ' ') {
                sea[x + 1][y - 1] = '`';
            }
        }
        // top left
        if (((x - 1) >= 0 && (x - 1) <= 9) && ((y - 1) >= 0 && (y - 1) <= 9)) {
            if (sea[x - 1][y - 1] == '`' || sea[x - 1][y - 1] == ' ') {
                sea[x - 1][y - 1] = '`';
            }
        }
        if (((x + 1) >= 0 && (x + 1) <= 9) && ((y + 1) >= 0 && (y + 1) <= 9)) {
            if (sea[x + 1][y + 1] == '`' || sea[x + 1][y + 1] == ' ') {
                sea[x + 1][y + 1] = '`';
            }
        }
        if (((x - 1) >= 0 && (x - 1) <= 9) && ((y + 1) >= 0 && (y + 1) <= 9)) {
            if (sea[x - 1][y + 1] == '`' || sea[x - 1][y + 1] == ' ') {
                sea[x - 1][y + 1] = '`';
            }
        }
    }

    return 1;
}
int showAroundOfTerminatedShip(ship *ship, int mapX, int mapY, char sea[mapX][mapY]) {
    // banning 8 side of every part if it's ' ' or '`'
    int x, y;
    for (int a = 0; a < ship->size; a++) {
        x = ship->coordArray[a].x;
        y = ship->coordArray[a].y;

        //top
        if ((sea[x][y + 1] == '`' || sea[x][y + 1] == ' ') && (y + 1 >= 0 && y + 1 <= 9)) {
            sea[x][y + 1] = 'W';
#if D
            printf("Exposed [%d][%d]\n", x, y + 1);
#endif

            fflush(stdout);
        }
        //bot
        if ((sea[x][y - 1] == '`' || sea[x][y - 1] == ' ') && (y - 1 >= 0 && y - 1 <= 9)) {
            sea[x][y - 1] = 'W';
#if D
            printf("Exposed [%d][%d]\n", x, y - 1);
#endif
            fflush(stdout);
        }
        //left
        if ((sea[x - 1][y] == '`' || sea[x - 1][y] == ' ') && (x - 1 >= 0 && x - 1 <= 9)) {
            sea[x - 1][y] = 'W';
#if D
            printf("Exposed [%d][%d]\n", x - 1, y);
#endif
            fflush(stdout);
        }
        //right
        if ((sea[x + 1][y] == '`' || sea[x + 1][y] == ' ') && (x + 1 >= 0 && x + 1 <= 9)) {
            sea[x + 1][y] = 'W';
#if D
            printf("Exposed [%d][%d]\n", x + 1, y);
#endif
            fflush(stdout);
        }
        //top right
        if (((x + 1) >= 0 && (x + 1) <= 9) && ((y - 1) >= 0 && (y - 1) <= 9)) {
            if (sea[x + 1][y - 1] == '`' || sea[x + 1][y - 1] == ' ') {
                sea[x + 1][y - 1] = 'W';
#if D
                printf("Exposed [%d][%d]\n", x + 1, y - 1);
#endif
                fflush(stdout);
            }
        }
        // top left
        if (((x - 1) >= 0 && (x - 1) <= 9) && ((y - 1) >= 0 && (y - 1) <= 9)) {
            if (sea[x - 1][y - 1] == '`' || sea[x - 1][y - 1] == ' ') {
                sea[x - 1][y - 1] = 'W';
#if D
                printf("Exposed [%d][%d]\n", x - 1, y - 1);
#endif
                fflush(stdout);
            }
        }
        if (((x + 1) >= 0 && (x + 1) <= 9) && ((y + 1) >= 0 && (y + 1) <= 9)) {
            if (sea[x + 1][y + 1] == '`' || sea[x + 1][y + 1] == ' ') {
                sea[x + 1][y + 1] = 'W';
#if D
                printf("Exposed [%d][%d]\n", x + 1, y + 1);

#endif
                fflush(stdout);
            }
        }
        if (((x - 1) >= 0 && (x - 1) <= 9) && ((y + 1) >= 0 && (y + 1) <= 9)) {
            if (sea[x - 1][y + 1] == '`' || sea[x - 1][y + 1] == ' ') {
                sea[x - 1][y + 1] = 'W';
#if D
                printf("Exposed [%d][%d]\n", x - 1, y + 1);
#endif
                fflush(stdout);
            }
        }
    }

    return 1;
}

int setShipOnSea(ship *ship, int mapX, int mapY, char sea[mapX][mapY]) {

    int x, y, index = 0;
    while (ship->coordArray[index].x != -1) {

        x = ship->coordArray[index].x;
        y = ship->coordArray[index].y;
#if D
        setColor('g');
        printf("Trying to set ship by size =%d, part = %d, in map block [%d][%d] = '%c' \n\n", ship->size, index + 1,
               x, y, sea[x][y]);
        fflush(stdout);

#endif
        if (sea[x][y] != ' ') return 0;
        sea[x][y] = ship->size + '0';
        index++;
#if D
        printf("confirmed that block [%d][%d] = '%c' \n", x, y, sea[x][y]);
        fflush(stdout);
#endif
        setColor('n');
    }


    return 1;
}


void printShipDataForUser(acc *user, int mapX, int mapY, char userSea[mapX][mapY], int shipSizeArr[10]) {


    printf("\n\n\nThis is your Territory, You have to defend it with your honor!\n\n\n");
    drawCusMap(mapX, mapY, userSea);
    printf("\n\n\nWe have limited recourses commander %s , but our captains do believe in you !\n"
           "Now is the time to set the position of our Army!\n ", user->username);

    //printing ships data
    printf("\nOur humble army is full of :\n");
    for (int a = 0; a < 10; a++) {
        if (shipSizeArr[a] == 0) continue;
        printf(" %d Ship(s) with the size of %d by 1\n", shipSizeArr[a], a + 1);
    }
    printf("\n\n");

}


// This method pushes the list
// Warning : last node is not representing any Ships
ship *makeShipsList(ship **listHead, acc *user, int const shipSizeArr[10]) {


    //getting the count of ships for every size
    int countOfShip = 0;
    for (int b = 0; b < 10; b++) {
        if (shipSizeArr[b] == 0) continue;
        countOfShip = shipSizeArr[b];


        for (int c = 0; c < countOfShip; c++) {
            ship *pNewShip = (ship *) malloc(sizeof(ship));
            if (pNewShip == NULL) {
                printf("out of memory");
            } else {
                //------------------------------------------getting ship data
                //set the coord array all to -1 for new ship
                for (int a = 0; a < MAX_SHIP_SIZE; a++) {
                    pNewShip->coordArray[a].x = -1;
                    pNewShip->coordArray[a].y = -1;
                }
                pNewShip->fullStatus = 'H';
                pNewShip->size = b + 1;
                pNewShip->pos = '?';
                pNewShip->owner = user;

                //adding to the end of list and setting the head on new ship we created
                pNewShip->pNextShip = *listHead;
                *listHead = pNewShip;
#if D
                setColor('G');
                printf("New Ship With size of %d and status of %c created and added to the list \n", b + 1,
                       pNewShip->fullStatus);
                fflush(stdout);
                setColor('n');
#endif

            }
        }
    }
}

void makeSeaReady(ship *pHead, int mapX, int mapY, char seaOrigin[mapX][mapY]) {
    ship* saveHead = pHead;
    char backupSea[mapX][mapY];
    // for reset
    char backupSeaScratch[mapX][mapY];
    arrCpr2D(mapX, mapY, backupSea, seaOrigin);
    arrCpr2D(mapX, mapY, backupSeaScratch, seaOrigin);
    ship *pCurr = pHead;
    coord firstInCoord;
    coord secondInCoord;

    printf("\n\nNow let's set our army positions. don't worry,\n"
           "just give me the points on the map and I settle everything.\n\n\n");
    setColor('y');
    printf("Commander %s, be aware that it is too risky to set our ships near\n"
           "each other, so be careful by what you order!\n"
           "these captains have family too sir ...\n\n ", pHead->owner->username);
    setColor('r');
    printf("\n\nYou can fall our ships back by Entering the emergency code => 911\n\n");
    setColor('n');

    //because the last node is not representing any ship, condition of while loop is like this to
    //avoid using the last node in the list
    while (pCurr->pNextShip != NULL) {

        if (pCurr->size == 1) {
            int t = makeRandomNumber(1, 10);
            setColor('y');
            if (t < 3) {
                printf("\nCommander! This boats may be small but they can sneak and hide pretty well.\n"
                       " They only take 1 part. give me the coordinates  \n");
            }
            if (t >= 3 && t < 6) {
                printf("War is on going sir! where should I hide this boats with size 1 ? \n");

            }
            if (t >= 6) {
                printf("I think we are good to go, Just need to set this boats."
                       "don't worry, they only take 1 block of our war map!\n");
            }

            while (1) {
                setColor('y');
                fflush(stdout);
                printf("Set the boat at :      ");
                fflush(stdout);
                scanf("%d %d", &firstInCoord.x, &firstInCoord.y);
                fflush(stdout);
                if( firstInCoord.x == 911) break;
                fflush(stdout);


                    pCurr->pos = '/';
                    secondInCoord.x = -1;
                    secondInCoord.y = -1;
                    // checking input length
                    //...
                    // giving the data to ship node
                    setCoordForShip(firstInCoord, secondInCoord, pCurr);

                    // backing up sea in case of an error
                    arrCpr2D(mapX, mapY, backupSea, seaOrigin);
                    //setting ship locations on map
                    int res1 = setShipOnSea(pCurr, mapX, mapY, seaOrigin);

#if D                 // printing the sea baning changes
                    for(int a = 0 ; a < mapX ; a++){
                        for ( int b = 0 ; b < mapY ; b++){
                            printf("seaOrigin[%d][%d] = %c\n", a,b,seaOrigin[a][b]);
                        }
                    }
#endif
                    // baning locations on map
                    int res2 = banOnSea(pCurr, mapX, mapY, seaOrigin);
                    //if a location for setting ship not be ' '  ||  if a location to ban is 's'  ---> return zero
                    if (res1 == 0 || res2 == 0) {
                        int v = makeRandomNumber(1, 10);
                        setColor('y');
                        if (v < 3) {
                            printf("\n I warned you Master, spread the army or we will fail at war!\n"
                                   "Try again ...\n");
                        }
                        if (v >= 3 && v <= 6) {
                            printf("\n NOT TO CLOSE ! this isn't a child game! sorry sir but I\n"
                                   "have to cancel this order...\n"
                                   "Try again ...\n");
                        }
                        if (v > 6 && v <= 9) {
                            printf("\n NO I WONT sent my men like cowards! please spread that army master !!!\n"
                                   "More , More \n"
                                   "again ...\n");
                        }
                        if (v > 8) {
                            printf("\n Sir, I'm not in the place to interference in your commands but\n"
                                   "isn't that too close ? please Try again ...\n");

                        }
                        //setting seaOrigin back
                        arrCpr2D(mapX, mapY, seaOrigin, backupSea);
                        continue;
                    }

                break;
                }
            //reset
            if(firstInCoord.x == 911) {
                pCurr = saveHead;
                arrCpr2D(mapX, mapY, seaOrigin, backupSeaScratch);

                setColor('r');
                printf("\n\n\n\n                  Falling troops back ...                   \n\n\n\n");
                setColor('y');
                Sleep(2000);
                system("clear");
                printf("Your humble servants are ready foe your orders Commander !!\n\n");
                continue;
            }
            drawCusMap(mapX, mapY, seaOrigin);

            pCurr = pCurr->pNextShip;
            continue;
        }// end if for one size



        int t = makeRandomNumber(1, 10);
        setColor('y');
        if (t < 3) {
            printf("\nCommander! give me the positions of the tail and the nose for \n"
                   "Battle ship by size of %d  \n", pCurr->size);
        }
        if (t >= 3 && t < 6) {
            printf("Hurry up! the war won't wait on us! \n"
                   "size is : %d \n", pCurr->size);
        }
        if (t >= 6) {
            printf("FAST FAST FAST !!!, give me the positions \n"
                   "What ? size ? \n"
                   "God damn it I've already told you the SIZE! it's %d\n", pCurr->size);
        }
        // infinite while for checking the inputs
        // this while gets the coord for nose and tail of one ship
        while (1) {
            setColor('y');
            fflush(stdout);
            printf("setting the nose at :      ");
            fflush(stdout);
            scanf("%d %d", &firstInCoord.x, &firstInCoord.y);
            fflush(stdout);
            //reset
            if( firstInCoord.x == 911) break;

            fflush(stdout);
            printf("\nsetting the tail at :      ");
            fflush(stdout);
            scanf("%d %d", &secondInCoord.x, &secondInCoord.y);
            fflush(stdout);
            //pos is V
            if (firstInCoord.x == secondInCoord.x) {
                pCurr->pos = 'V';

                // checking input length
                if (abs(secondInCoord.y - firstInCoord.y) + 1 != pCurr->size) {
                    int z = makeRandomNumber(1, 10);
                    setColor('y');
                    // choosing one
                    if (z < 3) {
                        printf("\n your orders seems to be shorter/longer than\n"
                               "the ships length. Try again ...\n");
                    }
                    if (z >= 3 && z <= 6) {
                        printf("\n don't underestimate our ships! we need a bigger location\n"
                               "to set that big boy sir!\n");
                    }
                    if (z > 6 && z <= 9) {
                        printf("\n Sir, something is wrong with the calculation of \n"
                               "what you've ordered. Try again ... \n");
                    }
                    if (z > 6) {
                        printf("\nSir, that ship takes more space!,I warned you it's not a good idea to take\n"
                               "LDS before the battle...\n"
                               "try AGAIN ...\n");
                    }
                    continue;
                }

                // giving the data to ship node
                setCoordForShip(firstInCoord, secondInCoord, pCurr);
                // backuping sea in case of an error
                arrCpr2D(mapX, mapY, backupSea, seaOrigin);
                //setting ship locations on map
                int res1 = setShipOnSea(pCurr, mapX, mapY, seaOrigin);
#if D
                for(int a = 0 ; a < mapX ; a++){
                    for ( int b = 0 ; b < mapY ; b++){
                        printf("seaOrigin[%d][%d] = %c\n", a,b,seaOrigin[a][b]);
                    }
                }
#endif
                // baning locations on map
                int res2 = banOnSea(pCurr, mapX, mapY, seaOrigin);
                //if a location for setting ship not be ' '  ||  if a location to ban is 's'  ---> return zero
                if (res1 == 0 || res2 == 0) {
                    int v = makeRandomNumber(1, 10);
                    setColor('y');
                    if (v < 3) {
                        printf("\n I warned you Master, spread the army or we will fail at war!\n"
                               "Try again ...\n");
                    }
                    if (v >= 3 && v <= 6) {
                        printf("\n NOT TO CLOSE ! this isn't a child game! sorry sir but I\n"
                               "have to cancel this order...\n"
                               "Try again ...\n");
                    }
                    if (v > 6 && v <= 9) {
                        printf("\n NO I WONT sent my men like cowards! please spread that army master !!!\n"
                               "More , More \n"
                               "again ...\n");
                    }
                    if (v > 8) {
                        printf("\n Sir, I'm not in the place to interference in your commands but\n"
                               "isn't that too close ? please Try again ...\n");

                    }
                    //setting seaOrigin back
                    arrCpr2D(mapX, mapY, seaOrigin, backupSea);
                    continue;
                }


            }
                // pos is H
            else if (firstInCoord.y == secondInCoord.y) {
                pCurr->pos = 'H';
                // checking input length
                if (abs(secondInCoord.x - firstInCoord.x) + 1 != pCurr->size) {
                    // choosing one
                    int t = makeRandomNumber(1, 9);
                    setColor('y');
                    if (t < 3) {
                        printf("\n your orders seems to be shorter/longer than\n"
                               "the ships length. Try again ...\n");
                    }
                    if ((t >= 3) && (t <= 6)) {
                        printf("\n don't underestimate our ships! we need a bigger location\n"
                               "to set that big boy sir!\n");
                    }
                    if ((t > 6) && (t <= 9)) {
                        printf("\n Sir, something is wrong with the calculation of \n"
                               "what you've ordered. Try again ... \n");
                    }
                    if (t > 3) {
                        printf("\nSir, that ship takes more space!,I warned you it's not a good idea to take\n"
                               "LDS before the battle...\n"
                               "try AGAIN ...\n");
                    }
                    continue;
                }
                // giving the data to ship node
                setCoordForShip(firstInCoord, secondInCoord, pCurr);
                // backuping sea in case of an error
                arrCpr2D(mapX, mapY, backupSea, seaOrigin);
                //setting ship locations on map
                int res1 = setShipOnSea(pCurr, mapX, mapY, seaOrigin);
#if D
                for(int a = 0 ; a < mapX ; a++){
                    for ( int b = 0 ; b < mapY ; b++){
                        printf("seaOrigin[%d][%d] = %c\n", a,b,seaOrigin[a][b]);
                    }
                }
#endif
                // baning locations on map
                int res2 = banOnSea(pCurr, mapX, mapY, seaOrigin);
                //if a location for setting ship not be ' '  ||  if a location to ban is 's'  ---> return zero
                if (res1 == 0 || res2 == 0) {
                    int s = makeRandomNumber(1, 10);
                    setColor('y');
                    if (s < 3) {
                        printf("\n I warned you Master, spread the army or we will fail at war!\n"
                               "Try again ...\n");
                    }
                    if (s >= 3 && s <= 6) {
                        printf("\n NOT TO CLOSE ! this isn't a child game! sorry sir but I\n"
                               "have to cancel this order...\n"
                               "Try again ...\n");
                    }
                    if (s > 6 && s <= 9) {
                        printf("\n NO I WONT sent my men like cowards! please spread that army master !!!\n"
                               "More , More \n"
                               "again ...\n");
                    }
                    if (s > 8) {
                        printf("\n Sir, I'm not in the place to interference in your commands but\n"
                               "isn't that too close ? please Try again ...\n");

                    }
                    //setting seaOrigin back
                    arrCpr2D(mapX, mapY, backupSea, seaOrigin);
                    continue;
                }


            }   // if inputs are not in one line :
            else {
                setColor('y');
                printf("\n Sorry sir, but our ship does not have an ability \n"
                       "to stretch themselves !\n"
                       "Try again...\n");
                continue;
            }

            break;
        }
        if(firstInCoord.x == 911){
            pCurr = saveHead;
            arrCpr2D(mapX,mapY,seaOrigin,backupSeaScratch);

            setColor('r');
            printf("\n\n\n\n                  Falling troops back ...                   \n\n\n\n");
            setColor('y');
            Sleep(2000);
            system("clear");
            printf("Your humble servants are ready foe your orders Commander !!\n\n");
            continue;
        }

        setColor('g');
        drawCusMap(mapX, mapY, seaOrigin);
        printf("\n\n\n");

        pCurr = pCurr->pNextShip;
    }//end while list move


}