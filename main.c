
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "BaseMethods.h"
#include "ShipMethods.h"
#include <time.h>
#define D 0
#include "BattleMethods.h"

// This func is here to avoid using pointer to pointer and keeping code more simple
acc  setPlayer(){



    acc profile;
    acc tmp;
    acc res;
    int lastAccNum;
    FILE* playerData=NULL;
    char userName[50];


    int input;


    printf("Choose     \n"
           "           1) Choose account\n"
           "           2) Create account\n");

    scanf("%d", &input);
    int accStatus = 1;
    while (accStatus) {
 if (input == 1) {
            //open player data

            playerData = fopen("GameData\\PlayerData.bin", "rb+");
            if (playerData == NULL) {
                printf("Can't open player data\n");

            }
            printf("please pick an account by its number : \n");
            fflush(stdout);

            //check for being empty
            fseek(playerData,0,SEEK_END);
            if (ftell(playerData) == 0) {
                printf("No player data exists! \n");
                profile.num = 1;
                input = 2;
                continue;
            }
            rewind(playerData);

            while (fread(&profile, sizeof(profile), 1, playerData) >= 1) {
                printf("%d. %s\n", profile.num, profile.username);
                setColor('g');
                printf("Score : %d\n\n", profile.coin);
                setColor('n');
                fflush(stdout);
            }
            rewind(playerData);
            int prof;
            scanf("%d", &prof);
            for (int a = 1; a <= prof; a++) {
                fread(&profile, sizeof(profile), 1, playerData);
            }

            printf("Done!\n");
            res = profile;
            return res;

        }
        if (input == 2) {
            // making new prof
            printf("Please Enter new username to create an account (MAX 50 characters) :    ");
            fflush(stdout);
            scanf("%s", profile.username);


            if (playerData != NULL){
                fclose(playerData);}
            playerData = fopen("GameData\\PlayerData.bin", "rb+");
            //check to be valid :
            while (fread(&tmp, sizeof(tmp), 1, playerData) >= 1) {
                if ( strcmp(tmp.username, profile.username) == 0) {
                    setColor('r');
                    printf("\n\n\nSorry but this name is already taken.\n"
                           "don't worry, I've change it for you to : \n");
                    setColor('n');
                    time_t t = time(NULL);
                    srand(t);
                    int ran = (rand() % (50 - 1)) + 0;
                    char ranStr[2];
                    sprintf(ranStr, "%d", ran);
                    strcat(profile.username, ranStr);
                    printf("\n\n%s\n\n\n", profile.username);
                    Sleep(7000);
                    system("clear");
                    break;
                }
            }


            // going to end
            //getting last account num :
            fseek(playerData,0,SEEK_END);
            if (ftell(playerData) == 0) {
                profile.num = 1;
            }else {
                fseek(playerData,-1 * sizeof(profile), SEEK_END);
                fread(&tmp, sizeof (tmp), 1, playerData);
                profile.num = tmp.num + 1;}

            fseek(playerData,0, SEEK_END); // every account data should be written here before
            // saving to file.
            profile.coin = 0;
            fwrite(&profile,sizeof (profile),1,playerData);
            printf("New account created!\n");
            fflush(stdout);
            input = 2;
            fclose(playerData);
            input = 1;
            continue;

        } else{
            printf("Wrong Input !");
        }
    }
    fclose(playerData);
    return res;
}




int main() {


    //getting map data's from file
    FILE* fp;
    int mapX=1,mapY=1;
    int defShipSize[10];
    fp = fopen("GameData\\mapSize.bin", "rb");
    if ( fp == NULL){
        printf("can't open mapSize.bin");
        fflush(stdout);
    }
    fread(&mapX, sizeof (int),1,fp);
    fread(&mapY, sizeof (int),1,fp);
    fclose(fp);
#if D
    setColor('G');
    printf("READ from mapSize.bin : mapX is %d\n",mapX);
    printf("READ from mapSize.bin : mapY is %d\n",mapY);
    setColor('n');
#endif

    //getting ship size
    FILE* fpp = fopen("GameData\\ShipSize.bin", "rb");
    if ( fpp == NULL){
        printf("can't open ShipSize.bin\n");
    }
    //check for being empty
    fseek(fpp, 0 , SEEK_END);
    setColor('r');
    if( ftell(fpp) == 0) printf("ERROR : ShipSize.bin is empty !\n");
    rewind(fpp);


    for ( int a = 0 ; a < 10 ; a++){
        fread(&defShipSize[a], sizeof (int), 1 , fpp);
#if D
        setColor('G');
        printf("READ from shipSize.bin : size of 1 by %d ships is %d\n",a+1,defShipSize[a]);
#endif
    }
    setColor('n');
    fclose(fp);

    //User default Data's :

    acc user1;
    acc user2;


    ship headShipUser1;
    headShipUser1.pNextShip = NULL;
    headShipUser1.fullStatus = 'H';
    ship headShipUser2;
    headShipUser2.pNextShip = NULL;
    headShipUser2.fullStatus = 'H';
    for( int a = 0 ; a < MAX_SHIP_SIZE ; a++){
        headShipUser1.coordArray[a].x = -1;
        headShipUser2.coordArray[a].x = -1;
        headShipUser1.coordArray[a].y = -1;
        headShipUser2.coordArray[a].y = -1;
    }

    ship* pHeadShipUser1 = &headShipUser1;
    ship* pHeadShipUser2 = &headShipUser2;

    char user1sea[mapX][mapY];
    makeDefaultSeaArray(mapX,mapY,user1sea);
    char user2sea[mapX][mapY];
    makeDefaultSeaArray(mapX,mapY,user2sea);

//=====================================================================  MENU STARTS

    while (1) {
        //115
//   welcomeText();
        if ( warning == 1){
            setColor('r');
            printf("                        WARNING : some major setting has been changed\n"
                   "                                  you should restart the game instantly\n");
            setColor('n');
        }
        // Base Menu
        printf("1. Roast some friends !\n\n"
               "2. Play with an stupid Bot\n\n"
               "3. Load my last mess\n\n"
               "4. Load one of my saved messes\n\n"
               "5. Setting\n\n"
               "6. Show who is the Boss \n\n"
               "7. Exit :( \n\n");


        int input;
        scanf("%d", &input);
        system("clear");

        // 1v1
        if (input == 1) {


            user1 = setPlayer();
            system("clear");
            setColor('y');
            printf("\n\nNow pass the PC to your mate !\n\n\n\n");
            while (1){
                user2 = setPlayer();
                if (user1.num == user2.num){
                    setColor('r');
                    printf("\n\n\nSame account is chosen try again\n");
                    setColor('n');
                    continue;
                }
                break;
            }
#if D
            onePlayerStatusPrint(&user1);
            onePlayerStatusPrint(&user2);
            getchar();
#endif

            system("clear");
            //user 1 stuff
            printf("\n\nLet's set our BattleShips!\n"
                   "\n1. Manual\n\n"
                   "2. Auto\n");
            // getting input
            int n;
            scanf("%d", &n);

            // manually setting ships for :
            if (n == 1) {

                //-----------------------------------------------USER 1

                // showing map
                printShipDataForUser(&user1,mapX,mapY,user1sea,defShipSize);
                //making linked list of ships for user 1
                makeShipsList(&pHeadShipUser1,&user1,defShipSize);
#if D
                listPrint(pHeadShipUser1);
#endif
                makeSeaReady(pHeadShipUser1,mapX,mapY,user1sea);
                system("clear");
                printf("\n\n\n                           Commander %s's Base \n\n\n", user1.username);
                drawOrgMap(mapY,mapY,user1sea);
                //115 change to longer time
                Sleep(2000);
                system("clear");
                setColor('n');
                printf("\n\n\nYOU ARE ALL SET. now pass the computer to your buddy \n\n\n\n");
                Sleep(2000);
                //----------------------------------------------USER 2
                // showing map
                printShipDataForUser(&user2,mapX,mapY,user2sea,defShipSize);
                //making linked list of ships for user 1
                makeShipsList(&pHeadShipUser2,&user2,defShipSize);
#if D
                listPrint(pHeadShipUser2);
#endif
                makeSeaReady(pHeadShipUser2,mapX,mapY,user2sea);
                system("clear");
                printf("\n\n\n                           Commander %s's Base\n\n\n ", user2.username);
                drawOrgMap(mapY,mapY,user2sea);
                Sleep(2000);
                system("clear");
                //-------------------------------------------------------------USERS = DONE | BATLLE BEGINS

                battleBase(mapX, mapY, user1sea, user2sea, pHeadShipUser1,pHeadShipUser2, &user1,&user2);

                break;
                printf("\n\n\n@@@@@@@@@@@@@@@@ END @@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n");

            }

            if (n == 2) {

            } else {
                printf("Wrong Input !");
            }
            //user 2 stuff
        }

            // with bot
        else if (input == 2) {

        }
            // load last game
        else if (input == 3) {

        }
            // show saved games
        else if (input == 4) {

        }
            // setting
        else if (input == 5) {

            system("clear");
            printf("\n\n1. Change map Size\n"
                   "\n2. Customize Army !\n\n");
            int n;
            scanf("%d",&n);
            if ( n ==1 ){
                changeMapSize();
                continue;
            }
            if ( n == 2){

                changeShipSize();


            }


        }
            // scoreboard
        else if (input == 6) {
printScoreBoard();
fflush(stdout);
        }
            // Exit
        else if (input == 7) {
            return 0;
        }
    }



    fflush(stdout);
    getchar();
    return 0;
}