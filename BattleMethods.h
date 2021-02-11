#define D 845

int delShip (ship** pHead){ //full = 7
                            // else = 1
    ship * holdToDel;
    ship * pCurr = *pHead;
    ship* pCurrNext;
    ship* pCurrPrevious = NULL;




    while(pCurr->pNextShip != NULL){

        pCurrNext = pCurr->pNextShip;
        // if found a node fully destroyed
        if( pCurr->fullStatus == 'D'){

            // if it was first node ( last one is null)
            if( pCurrPrevious == NULL){
                holdToDel = pCurr;
                pCurr = pCurr->pNextShip;
                **pHead = *pCurr;
                continue;
            }
            holdToDel = pCurr;
            pCurr = pCurrPrevious;
            pCurr->pNextShip = pCurrNext;
            free(holdToDel);
        }
        pCurrPrevious = pCurr;
        pCurr = pCurr->pNextShip;
    }
    if ((*pHead)->pNextShip == NULL) return 7;
    return 1;
}

int checkFullTermination(int mapX, int mapY, ship* pHead,char sea[mapX][mapY],int * uCoin){ //terminated = 1
                                                                                //nothing terminated =0
                                                                                //full = 7
    char indicator;
    ship* pCurr = pHead;
    int countDamagedParts;
    // 1 before last
    while(pCurr->pNextShip != NULL){
        countDamagedParts = 0;
        //counting damaged parts
        for (int a = 0 ; a < pCurr->size ; a++){

            if (sea[pCurr->coordArray[a].x][pCurr->coordArray[a].y] == 'X' ){
                countDamagedParts++;
            }
        }
        if(countDamagedParts == pCurr->size){
                //setting all parts to X
            for (int b = 0 ; b < pCurr->size ; b++){
                sea[pCurr->coordArray[b].x][pCurr->coordArray[b].y] = '#';
            }
            //adding coins to user
            *uCoin += coinCalc(pCurr->size);
            //showing the area around it
            showAroundOfTerminatedShip(pCurr,mapX,mapY,sea);
            //deleting from list
            pCurr->fullStatus = 'D';
            return delShip(&pHead);
        }

        pCurr = pCurr->pNextShip;
    }


    return 0; //nothing terminated
}


int shoot(int mapX, int mapY, char sea[mapX][mapY], coord target) {
    // 1 = player has prise
    // 2 = already shot
    // 3 = shot water

    char indicator;

    indicator = sea[target.x][target.y];

    if (indicator == '`' || indicator == ' ') {
        sea[target.x][target.y] = 'W';
        return 3;
    }
    // if  target was a number
    if (indicator <= '9' && indicator >= '1') {
        sea[target.x][target.y] = 'X' ;
        return 1;
    }
    //already shot
    if ( indicator =='X' || indicator == 'W' || indicator == '#' ) {
        return 2;
    }

}

void battleBase(int mapX, int mapY, char user1sea[mapX][mapY], char user2sea[mapX][mapY],
                ship *pHeadUser1, ship *pHeadUser2, acc *user1, acc *user2) {
    int end = 0, res=999, rol=999;
    int u1Coin = 0;
    int u2Coin = 0;


    coord inTarget;
    //backing up seas
    char u1orgBackup[mapY][mapX];
    arrCpr2D(mapX, mapY, u1orgBackup, user1sea);
    char u2orgBackup[mapX][mapY];
    arrCpr2D(mapX, mapY, u2orgBackup, user2sea);
    rol = 1;
    while (1) { //ends when a list reaches end
        //115 longer
      Sleep(2000); // to see the res of attack
        system("clear");
        setColor('y');

        //showing rol and opponent map
        if (rol ==1 ){
            printf("\n\n\n\n\n                   Commander 1 : %s\n\n", user1->username);

            drawBattleMap(mapX,mapY,user2sea);
            fflush(stdout);
        }
        else{
            printf("\n\n\n\n\n                   Commander 2 : %s\n\n",user2->username);

                drawBattleMap(mapX,mapY,user1sea);
                fflush(stdout);
        }


        printf("\n\nOur canons are waiting for the coordinates, Where To shoot ?\n\n");
        fflush(stdout);
        scanf("%d", &inTarget.x);
fflush(stdout);
        scanf("%d", &inTarget.y);
        fflush(stdout);

        //shoot
        if(rol ==1) res = shoot(mapX, mapY, user2sea, inTarget);
        else res=shoot(mapX, mapY, user1sea, inTarget);


        if (res == 1) { //prise
            setColor('y');
            printf("\n\nGood Hit!!!\n\n");
            //adding coin
            if(rol == 1){
                u1Coin++;
            }else{
                u2Coin++;
            }
            setColor('n');
            fflush(stdout);
            if (rol == 1) drawBattleMap(mapX,mapY,user2sea);
            else drawBattleMap(mapX,mapY,user1sea);
            // check list
            if(rol == 1) end =checkFullTermination(mapX,mapY,pHeadUser2,user2sea,&u1Coin);
            else end = checkFullTermination(mapX,mapY,pHeadUser1,user1sea,&u2Coin);
            //giving coins
            if (end == 7) break;
            // rol doesn't changes
            continue;
        }
        if (res == 2) { //same coord
            printf("Sir, You once shot that part of sea\n");
            printf("\nAmo does NOT grow on trees master, remember we are in WAR !\n\n");
            // check list
            if(rol == 1) end =checkFullTermination(mapX,mapY,pHeadUser2,user2sea,&u1Coin);
            else end = checkFullTermination(mapX,mapY,pHeadUser1,user1sea,&u2Coin);
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
            if(rol == 1) end =checkFullTermination(mapX,mapY,pHeadUser2,user2sea, &u2Coin);
            else end = checkFullTermination(mapX,mapY,pHeadUser1,user1sea, &u1Coin);
            if (end == 7) break;
            //change rol
            if (rol==1) rol =2;
            else rol = 1;
        }

    }
    // print winner
    if(pHeadUser1->pNextShip == NULL){
        printf("\n****** Commander %s Wins ! ******\n\n", user1->username);
        user1->coin += u1Coin;
        user2->coin += u2Coin/2;
        saveScoresInFile(*user1);
        saveScoresInFile(*user2);
    }
    else if(pHeadUser2->pNextShip == NULL){
        printf("\n****** Commander %s Wins ! ******\n\n", user2->username);
        user2->coin += u2Coin;
        user1->coin += u1Coin/2;
        saveScoresInFile(*user1);
        saveScoresInFile(*user2);
    }
    else{
        printf("\nWinner error\n");
    }
    fflush(stdout);


}// end battleBase