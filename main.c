#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "BaseMethods.h"
#define MAX_SHIP_SIZE 10
int newUserCounter = 1 ;
char user1 [50];
char user2 [50];

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


void setPlayer(char user[50]){

    // Setting User 1
    FILE* playerData;
    char userName[50];
    char tmp[50];
    int counter = 1;
    int input, userCounts=0;


    printf("Choose     1) Play as Guest\n"
           "           2) Choose account\n"
           "           3) Create account\n");

    scanf("%d", &input);
    int accStatus = 1;
    while (accStatus) {
        if (input == 1) {
            printf("Enter Your Guest Username : ");
            scanf("%s", userName);
            strcpy(user, userName);
            accStatus = 0;
            break;

        }  if (input == 2) {
            //open player data
            playerData = fopen("C:\\FinalPro\\PlayerData.bin", "rb+");
            if (playerData == NULL) {
                printf("Can't open player data\n");
                return;
            }
            printf("please pick an account by its number : \n");
            //check for being empty
            fread(&userCounts, sizeof(int), 1, playerData);
//            printf("count of accounts is : %d", userCounts);
//            fflush(stdout);
            if (feof(playerData)) {
                printf("No player data exists! \n");
                input = 3;
                continue;
            }
            // going to start of strings
            fseek(playerData, 1 * sizeof(int), SEEK_SET);


            while (fread(userName, sizeof(userName), 1, playerData) >= 1) {
                printf("%d. %s\n", counter, userName);
                counter++;
            }
            int prof;
            scanf("%d", &prof);
            for (int a = 1; a <= prof; a++) {
                fread(userName, sizeof(userName), 1, playerData);
            }
            strcpy(user, userName);
            printf("Done!\n");
            break;

        }
        if (input == 3) {

            printf("Please Enter new username to create an account (MAX 50 characters) :    ");
            fflush(stdout);
            scanf("%s", userName);
            // going to end
            fclose(playerData);
            playerData = fopen("C:\\FinalPro\\PlayerData.bin", "rb+");
            rewind(playerData);
            fwrite(&newUserCounter,sizeof (int),1,playerData);
            newUserCounter++;
//            while (1) {
//                if (fread(userName, sizeof(userName), 1, playerData) < 1) break;
//            }
            fseek(playerData,0, SEEK_END);
            fwrite(userName,sizeof (userName),1,playerData);
            printf("New account created!\n");
            fflush(stdout);
            input = 2;
            fclose(playerData);
            continue;

        }
    }
    fclose(playerData);
}


void showMenu(){

//    welcomeText();

    // Base Menu :
    printf("1. Roast some friends !\n\n"
           "2. Play with an stupid Bot\n\n"
           "3. Load my last mess\n\n"
           "4. Load one of my saved messes\n\n"
           "5. Setting\n\n"
           "6. Show who is the Boss \n\n"
           "7. Exit :( \n\n");


    int input;
    scanf("%d",&input);
    system("clear");

    // 1v1
    if (input == 1){
        printf("                                   So He Has Chosen Death !\n");
        Sleep(1000);
        setPlayer(user1);
        setPlayer(user2);

    }

        // with bot
    else if (input == 2){

    }
        // load last game
    else if (input == 3){

    }
        // show saved games
    else if (input == 4){

    }
        // setting
    else if (input == 5){

    }
        // scoreboard
    else if (input == 6){

    }
        // Exit
    else if (input == 7){
        return;
    }

}

int main() {

    showMenu();

    printf("%s\n%s\n", user1,user2);
    getchar();
    return 0;
}