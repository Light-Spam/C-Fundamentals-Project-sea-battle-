#define D 0

int searchInMoves(int mapX, int mapY, coord moves[mapX * mapY], coord shoot) { //same shot = 0
    // new shot = 1

    for (int a = 0; a < (mapX * mapY); a++) {
        if (shoot.x == moves[a].x && shoot.y == moves[a].y) return 0;

    };
    return 1;
}
int shootBOT(int mapX, int mapY, char sea[mapX][mapY]) {
    // 1 = player has prise
    // 2 = already shot
    // 3 = shot water
    coord target;
    coord doneMoves[mapX * mapY];
    // not to make same moves

    while(1) {
        target.x = makeRandomNumber(0, mapY);
        target.y = makeRandomNumber(0,mapY) ;
        if (searchInMoves(mapX,mapY,doneMoves, target) == 1) break;

    }

    char indicator;

    indicator = sea[target.x][target.y];

    if (indicator == '`' || indicator == ' ') {
        sea[target.x][target.y] = 'W';
        return 3;
    }
    // if  target was a number
    if (indicator <= '9' && indicator >= '1') {
        sea[target.x][target.y] = 'X';
        return 1;
    }
    //already shot
    if (indicator == 'X' || indicator == 'W' || indicator == '#') {
        return 2;
    }

}

int checkFullTerminationBOT(int mapX, int mapY, ship *pHead, char sea[mapX][mapY]) { //terminated = 1
    //nothing terminated =0
    //full = 7
    char indicator;
    ship *pCurr = pHead;
    int countDamagedParts;
    // 1 before last
    while (pCurr->pNextShip != NULL) {
        countDamagedParts = 0;
        //counting damaged parts
        for (int a = 0; a < pCurr->size; a++) {

            if (sea[pCurr->coordArray[a].x][pCurr->coordArray[a].y] == 'X') {
                countDamagedParts++;
            }
        }
        if (countDamagedParts == pCurr->size) {
            //setting all parts to X
            for (int b = 0; b < pCurr->size; b++) {
                sea[pCurr->coordArray[b].x][pCurr->coordArray[b].y] = '#';
            }
            //adding coins to user
            //showing the area around it
            showAroundOfTerminatedShip(pCurr, mapX, mapY, sea);
            //deleting from list
            pCurr->fullStatus = 'D';
            return delShip(&pHead);
        }

        pCurr = pCurr->pNextShip;
    }


    return 0; //nothing terminated
}


void autoShipSetBOT(int mapX, int mapY, char seaOrigin[mapX][mapY], ship *pHead) {
    char seaOrgBackup[mapX][mapY];
    arrCpr2D(mapX, mapY, seaOrgBackup, seaOrigin);
    ship *pCurr = pHead;
    coord firstInCoord;
    coord secondInCoord;
    coord2 res;
    while (pCurr->pNextShip != NULL) {
        res = findSpace(mapX, mapY, seaOrigin, pCurr->size);
        firstInCoord.x = res.xS;
        firstInCoord.y = res.yS;
        secondInCoord.x = res.xE;
        secondInCoord.y = res.yE;

        if (firstInCoord.x == secondInCoord.x) {
            pCurr->pos = 'V';

            setCoordForShip(firstInCoord, secondInCoord, pCurr);

            setShipOnSea(pCurr, mapX, mapY, seaOrigin);

            banOnSea(pCurr, mapX, mapY, seaOrigin);
        }
        if (firstInCoord.y == secondInCoord.y) {
            pCurr->pos = 'H';

            setCoordForShip(firstInCoord, secondInCoord, pCurr);

            setShipOnSea(pCurr, mapX, mapY, seaOrigin);

            banOnSea(pCurr, mapX, mapY, seaOrigin);

        }

        fflush(stdout);

        pCurr = pCurr->pNextShip;
    }
}

void battleBaseBOT(int mapX, int mapY, char user1sea[mapX][mapY], char user2sea[mapX][mapY],
                   ship *pHeadUser1, ship *pHeadUser2, acc *user1) {
    int end = 0, res = 999, rol = 999;
    int u1Coin = 0;



    coord inTarget;
    //backing up seas
    char u1orgBackup[mapY][mapX];
    arrCpr2D(mapX, mapY, u1orgBackup, user1sea);
    char u2orgBackup[mapX][mapY];
    arrCpr2D(mapX, mapY, u2orgBackup, user2sea);
    rol = 1;
    while (1) { //ends when a list reaches end
        //115 longer
        Sleep(3200); // to see the res of attack
        system("clear");
        setColor('y');

        //showing rol and opponent map
        if (rol == 1) {
            printf("\n\n\n\n\n                   Commander 1 : %s\n\n", user1->username);

            drawBattleMap(mapX, mapY, user2sea);
            fflush(stdout);
        } else {
            printf("\n\n\n\n\n                    An Stupid BOT :\n\n");

            drawBattleMap(mapX, mapY, user1sea);
            fflush(stdout);
        }

        //shoot
        if( rol == 1) {
        printf("\n\nOur canons are waiting for the coordinates, Where To shoot ?\n\n");
        fflush(stdout);
        scanf("%d", &inTarget.x);
        fflush(stdout);
        scanf("%d", &inTarget.y);
        fflush(stdout);
            res = shoot(mapX, mapY, user2sea, inTarget);}


        else res = shootBOT(mapX, mapY, user1sea);


        if (res == 1) { //prise

            //adding coin
            if (rol == 1) {
                setColor('y');
                printf("\n\nGood Hit!!!\n\n");
                u1Coin++;
            }

            setColor('n');
            fflush(stdout);
            if (rol == 1) drawBattleMap(mapX, mapY, user2sea);
            else drawBattleMap(mapX, mapY, user1sea);
            // check list
            if (rol == 1) end = checkFullTermination(mapX, mapY, pHeadUser2, user2sea, &u1Coin);
            else end = checkFullTerminationBOT(mapX, mapY, pHeadUser1, user1sea);
            //giving coins
            if (end == 7) break;
            // rol doesn't changes
            continue;
        }
        if (res == 2) { //same coord
            printf("Sir, You once shot that part of sea\n");
            printf("\nAmo does NOT grow on trees master, remember we are in WAR !\n\n");
            // check list
            if (rol == 1) end = checkFullTermination(mapX, mapY, pHeadUser2, user2sea, &u1Coin);
            else end = checkFullTerminationBOT(mapX, mapY, pHeadUser1, user1sea);
            if (end == 7) break;
            //change roll
            if (rol == 1) rol = 2;
            else rol = 1;

        }
        if (res == 3) { //water or banned
            printf("\n\n\nWhat a waste...\n\n\n");

            if (rol == 1) drawBattleMap(mapY, mapY, user2sea);
            else drawBattleMap(mapY, mapY, user1sea);
            // check list
            if (rol == 1) end = checkFullTermination(mapX, mapY, pHeadUser2, user2sea, &u1Coin);
            else end = checkFullTerminationBOT(mapX, mapY, pHeadUser1, user1sea);
            if (end == 7) break;
            //change rol
            if (rol == 1) rol = 2;
            else rol = 1;
        }

    }
    // print winner
    if (pHeadUser1->pNextShip == NULL) {
        printf("\n****** Commander %s Wins ! ******\n\n", user1->username);
        user1->coin += u1Coin;
        saveScoresInFile(*user1);

    } else if (pHeadUser2->pNextShip == NULL) {
        printf("\n BOT won ... stupid little dumb ..\n\n");
        user1->coin += u1Coin / 2;
        saveScoresInFile(*user1);
    } else {
        printf("\nWinner error\n");
    }
    fflush(stdout);


}// end battleBase









