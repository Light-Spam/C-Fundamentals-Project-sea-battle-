#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "BaseMethods.h"
#include "SaveGames.h"
#include "ShipMethods.h"
#include "BattleMethods.h"
#define D 0
#include "Bot+AutoAssembley.h"

// This func is here to avoid using pointer to pointer and keeping code more simple
acc setPlayer() {
    setColor('y');

    acc profile;
    acc tmp;
    acc res;

    FILE *playerData = NULL;


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
            fseek(playerData, 0, SEEK_END);
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
                printf("            Score : %d\n\n", profile.coin);
                setColor('y');
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


            if (playerData != NULL) {
                fclose(playerData);
            }
            playerData = fopen("GameData\\PlayerData.bin", "rb+");
            //check to be valid :
            while (fread(&tmp, sizeof(tmp), 1, playerData) >= 1) {
                if (strcmp(tmp.username, profile.username) == 0) {
                    setColor('r');
                    printf("\n\n\nSorry but this name is already taken.\n"
                           "don't worry, I've change it for you to : \n");
                    setColor('y');
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
            fseek(playerData, 0, SEEK_END);
            if (ftell(playerData) == 0) {
                profile.num = 1;
            } else {
                fseek(playerData, -1 * sizeof(profile), SEEK_END);
                fread(&tmp, sizeof(tmp), 1, playerData);
                profile.num = tmp.num + 1;
            }

            fseek(playerData, 0, SEEK_END); // every account data should be written here before
            // saving to file.
            profile.coin = 0;
            fwrite(&profile, sizeof(profile), 1, playerData);
            printf("New account created!\n");
            fflush(stdout);
            input = 2;
            fclose(playerData);
            input = 1;
            continue;

        } else {
            printf("Wrong Input !");
        }
    }
    fclose(playerData);
    return res;
}


int main() {
    welcomeText();



    //getting map data's from file
    FILE *fp;
    int mapX = 1, mapY = 1;
    int defShipSize[10];
    fp = fopen("GameData\\mapSize.bin", "rb");
    if (fp == NULL) {
        printf("can't open mapSize.bin");
        fflush(stdout);
    }
    fread(&mapX, sizeof(int), 1, fp);
    fread(&mapY, sizeof(int), 1, fp);
    fclose(fp);
#if D
    setColor('G');
    printf("READ from mapSize.bin : mapX is %d\n", mapX);
    printf("READ from mapSize.bin : mapY is %d\n", mapY);
    setColor('n');
#endif

    //getting ship size
    FILE *fpp = fopen("GameData\\ShipSize.bin", "rb");
    if (fpp == NULL) {
        printf("can't open ShipSize.bin\n");
    }
    //check for being empty
    fseek(fpp, 0, SEEK_END);
    setColor('r');
    if (ftell(fpp) == 0) printf("ERROR : ShipSize.bin is empty !\n");
    rewind(fpp);


    for (int a = 0; a < 10; a++) {
        fread(&defShipSize[a], sizeof(int), 1, fpp);
#if D
        setColor('G');
        printf("READ from shipSize.bin : size of 1 by %d ships is %d\n", a + 1, defShipSize[a]);
#endif
    }
    setColor('n');
    fclose(fp);

    //User default Data's :

    acc user1;
    acc user2;


    ship headShipUser1;
    headShipUser1.pNextShip = NULL;
    headShipUser1.fullStatus = ')';
    headShipUser1.pos = ')';
    ship headShipUser2;
    headShipUser2.pNextShip = NULL;
    headShipUser2.fullStatus = ')';
    headShipUser2.pos = ')';
    for (int a = 0; a < MAX_SHIP_SIZE; a++) {
        headShipUser1.coordArray[a].x = -1;
        headShipUser2.coordArray[a].x = -1;
        headShipUser1.coordArray[a].y = -1;
        headShipUser2.coordArray[a].y = -1;
    }

    ship *pHeadShipUser1 = &headShipUser1;
    ship *pHeadShipUser2 = &headShipUser2;

    char user1sea[mapX][mapY];
    char user1seaBackup[mapX][mapY];
    makeDefaultSeaArray(mapX, mapY, user1sea);
    arrCpr2D(mapX,mapY,user1seaBackup,user1sea);


    char user2sea[mapX][mapY];
    makeDefaultSeaArray(mapX, mapY, user2sea);
    char user2seaBackup[mapX][mapY];
    arrCpr2D(mapX,mapY,user2seaBackup,user2sea);

    //-----------------------------------------------



//=====================================================================  MENU STARTS

    while (1) { // menu loop
        //115

        if (warning == 1) {
            setColor('r');
            printf("                        WARNING : some major setting has been changed\n"
                   "                                  you should restart the game instantly\n");
            setColor('n');
            saveScreen();
            return 0;
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

            setColor('y');
            user1 = setPlayer();
            system("clear");
            setColor('y');
            printf("\n\nNow pass the PC to your mate !\n\n\n\n");
            while (1) {
                user2 = setPlayer();
                if (user1.num == user2.num) {
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
            printf("\n\n Commander 1: Head Captain %s,\n Let's set our BattleShips!\n"
                   "\n1. Manual\n\n"
                   "2. Auto\n", user1.username);
            // getting input
            int n;
            scanf("%d", &n);

            // manually setting ships for :
            if (n == 1) {

                //-----------------------------------------------USER 1

                // showing map
                printShipDataForUser(&user1, mapX, mapY, user1sea, defShipSize);
                //making linked list of ships for user 1
                makeShipsList(&pHeadShipUser1, &user1, defShipSize);
#if D
                listPrint(pHeadShipUser1);
#endif
                makeSeaReady(pHeadShipUser1, mapX, mapY, user1sea);
                system("clear");
                printf("\n\n\n                           Commander %s's Base \n\n\n", user1.username);
                drawOrgMap(mapY, mapY, user1sea);
                saveScreen();
                system("clear");
                setColor('n');
                printf("\n\n\nYOU ARE ALL SET. now pass the computer to your buddy \n\n\n\n");
                saveScreen();


            }

            if (n == 2) {
                printShipDataForUser(&user1, mapX, mapY, user1sea, defShipSize);
                saveScreen();
                makeShipsList(&pHeadShipUser1, &user1, defShipSize);
#if D
                listPrint(pHeadShipUser1);
#endif
                int h = 0;
                while (h!= -1){
                    arrCpr2D(mapX,mapY,user1sea,user1seaBackup);
                    autoShipSet(mapX, mapY, user1sea, pHeadShipUser1);
                    system("clear");
                    drawOrgMap(mapY, mapY, user1sea);
                    printf("\n\n Enter -1 to use this setup\n"
                           "Enter any number to try again\n\n");
                    fflush(stdout);
                    scanf("%d", &h);
                }

                system("clear");
                printf("\n\n\n                           Commander %s's Base \n\n\n", user1.username);
                drawOrgMap(mapY, mapY, user1sea);

                saveScreen();
                system("clear");
                setColor('n');
                printf("\n\n\nYOU ARE ALL SET. now pass the computer to your buddy \n\n\n\n");


            }
            //-----------------------------------------------------------------user 2
            saveScreen();
            system("clear");
            printf("\n\n Commander 2 : Head Captain %s,\n Let's set our BattleShips!\n"
                   "\n1. Manual\n\n"
                   "2. Auto\n", user2.username);

            scanf("%d", &n);
            if (n == 1) {

                // showing map
                printShipDataForUser(&user2, mapX, mapY, user2sea, defShipSize);
                //making linked list of ships for user 1
                makeShipsList(&pHeadShipUser2, &user2, defShipSize);
#if D
                listPrint(pHeadShipUser2);
#endif
                makeSeaReady(pHeadShipUser2, mapX, mapY, user2sea);
                system("clear");
                printf("\n\n\n                           Commander %s's Base\n\n\n ", user2.username);
                drawOrgMap(mapY, mapY, user2sea);
                Sleep(2000);
                system("clear");

                //-------------------------------------------------------------USERS = DONE | BATLLE BEGINS


            }

            if( n == 2){
                printShipDataForUser(&user2, mapX, mapY, user1sea, defShipSize);

                makeShipsList(&pHeadShipUser2, &user2, defShipSize);
#if D
                listPrint(pHeadShipUser2);
#endif
                int h = 0;
                while (h!= -1){
                    arrCpr2D(mapX,mapY,user2sea,user2seaBackup);
                    autoShipSet(mapX, mapY, user2sea, pHeadShipUser2);
                    system("clear");
                    drawOrgMap(mapY, mapY, user2sea);
                    printf("\n\n Enter -1 to use this setup\n"
                           "Enter any number to try again\n\n");
                    fflush(stdout);
                    scanf("%d", &h);
                }


                system("clear");
                printf("\n\n\n                           Commander %s's Base \n\n\n", user2.username);
                drawOrgMap(mapY, mapY, user2sea);
                //115 change to longer time
                saveScreen();
                system("clear");
                setColor('n');
                setColor('r');
                printf("\n\n\n                Get Ready For The Battle !  \n\n\n\n");
                setColor('r');
            }

            else {
                printf("Wrong Input !");
            }
            battleBase(mapX, mapY, user1sea, user2sea, pHeadShipUser1, pHeadShipUser2, &user1, &user2,1);
            return 0;
            break;
        }

            // with bot
        else if (input == 2) {

            //user setup
            setColor('y');
            user1 = setPlayer();
            system("clear");
            setColor('y');

            printf("\n\n Commander 1: Head Captain %s,\n Let's set our BattleShips!\n"
                   "\n1. Manual\n\n"
                   "2. Auto\n", user1.username);
            // getting input
            int n;
            scanf("%d", &n);


            if (n == 1) {

                //-----------------------------------------------USER 1

                // showing map
                printShipDataForUser(&user1, mapX, mapY, user1sea, defShipSize);
                //making linked list of ships for user 1
                makeShipsList(&pHeadShipUser1, &user1, defShipSize);
#if D
                listPrint(pHeadShipUser1);
#endif
                makeSeaReady(pHeadShipUser1, mapX, mapY, user1sea);
                system("clear");
                printf("\n\n\n                           Commander %s's Base \n\n\n", user1.username);
                drawOrgMap(mapY, mapY, user1sea);
                saveScreen();
                system("clear");
                setColor('n');
                printf("\n\n\nWait for the BOT . . . \n\n\n\n");



            }

            if (n == 2) {
                printShipDataForUser(&user1, mapX, mapY, user1sea, defShipSize);
                saveScreen();
                makeShipsList(&pHeadShipUser1, &user1, defShipSize);
#if D
                listPrint(pHeadShipUser1);
#endif
                int h;
                while( h != -1) {
                    arrCpr2D(mapX,mapY,user1sea,user1seaBackup);
                    autoShipSet(mapX, mapY, user1sea, pHeadShipUser1);
                    system("clear");
                    drawOrgMap(mapY, mapY, user1sea);
                    printf("\n\n Enter -1 to use this setup\n"
                           "Enter any number to try again\n\n");
                    fflush(stdout);
                    scanf("%d", &h);
                }

                system("clear");
                printf("\n\n\n                           Commander %s's Base \n\n\n", user1.username);
                drawOrgMap(mapY, mapY, user1sea);
                //115 change to longer time
                saveScreen();
                system("clear");
                setColor('n');
                printf("\n\n\nWait for the BOT . . . \n\n\n\n");


            }
            //setup Bot

            makeShipsList(&pHeadShipUser2, &user2, defShipSize);
            autoShipSetBOT(mapX, mapY, user2sea, pHeadShipUser2);
            battleBaseBOT(mapX,mapY,user1sea,user2sea,pHeadShipUser1,pHeadShipUser2,&user1);


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
            scanf("%d", &n);
            if (n == 1) {
                changeMapSize();
                continue;
            }
            if (n == 2) {
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


saveScreen();
    return 0;
}