#define MAX_SHIP_SIZE 10
#define D 0
#include <time.h>
//                    HERE ADD ALL NODES
typedef struct coordNode {
    int x;
    int y;
}coord;
typedef struct playerProfileNode{
    int num;
    char username [50];
    int coin;

}acc ;
typedef struct shipNode {
    // H = healthy    D = damaged    E = exploded
    char fullStatus;

    // size of ship = 1*size
    int size;

    // H = Horizontal   V = Vertical
    char pos;

    // address of User who owns this list
    acc * owner;
    // array of coords
    coord coordArray[MAX_SHIP_SIZE];

    // Pointer to next ship structure
    struct shipNode *pNextShip;
} ship;
//-------------------------------------------------------------------------------------------
int warning = 0;
// just changes font color.
void setColor(char chosenColor) {
    if (chosenColor == 'b' || chosenColor == 'B') {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_GREEN |
                                FOREGROUND_BLUE);
        fflush(stdout);
    }
    if (chosenColor == 'r' || chosenColor == 'R') {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_RED);
        fflush(stdout);
    }
    if (chosenColor == 'y' || chosenColor == 'Y') {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_RED | FOREGROUND_GREEN);
        fflush(stdout);
    }
    if (chosenColor == 'p' || chosenColor == 'P') {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_RED | FOREGROUND_BLUE);
        fflush(stdout);

    }
    if (chosenColor == 'n' || chosenColor == 'N') {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
        fflush(stdout);

    }
    if (chosenColor == 'g' || chosenColor == 'G') {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_GREEN );
        fflush(stdout);

    }

}

// player status
void allPlayerStatusPrint (){
    setColor('g');
    acc playerProfile;
    FILE* pData;
    pData = fopen("GameData\\PlayerData.bin","rb");
    rewind(pData);

    while ( fread(&playerProfile, sizeof (playerProfile),1,pData) >= 1){

        setColor('n');
        fflush(stdout);
    }


}
void onePlayerStatusPrint (acc* user){
    setColor('g');
    printf("Player name : %d. %s\n"
           "Player coins : %d  \n"
           "\n\n",
           user->num, user->username,user->coin);
    fflush(stdout);
    setColor('n');
}
void listPrint(ship* head){
    setColor('G');
    ship* currShip = head;
    int index = 1;
    printf("\n\n\n\n     #### LIST OWNER : %s\n\n", currShip->owner->username);

    while(currShip != NULL){
        printf("____________________________________\n"
               "Ship %d in the list\n"
               "Size : %d\n"
               " coords : \n",index, currShip->size);

        for ( int a = 0 ; a < currShip->size ; a++){
            printf("( %d , %d )\n" ,currShip->coordArray[a].x,currShip->coordArray[a].y);
        }
        printf("TotalStatus = %c\n"
               "Position = %c\n",currShip->fullStatus, currShip->pos);


        currShip = currShip->pNextShip;
        index++;
    }
    setColor('n');
}

void welcomeText() {
    setColor('y');
    printf("\n\n\n\n\n\n\n");
    printf("                                      ");
    char wel[] = {"Welcome to the Game that makes No sense at all !\n"};
    for (int i = 0; i < strlen(wel); i++) {
        putchar(wel[i]);
        fflush(stdout);

        Sleep(60);
    }
    printf("\n\n");
    printf("                                      ");
    printf("Programed By : Light-Spam \n");
    printf("                                      ");

    printf("Winter 2020");
    fflush(stdout);
    Sleep(3000);
    system("clear");
    setColor('n');
}

void changeMapSize(){
    int x, y;
    printf("\nEnter your map width :    ");
    scanf("%d", &x);
    printf("\n");
    printf("Enter your map length :    ");
    scanf("%d", &y);
    FILE* pMapSize = fopen("GameData\\mapSize.bin","wb");
    if(pMapSize == NULL){
        printf("\ncan't open mapSize.bin\n");
    }
    fwrite(&x,sizeof (int),1,pMapSize);
    fwrite(&y,sizeof (int),1,pMapSize);
    fclose(pMapSize);
    printf("\n\nplease restart the Game to apply changes\n");
    Sleep(4500);
    warning = 1;
    system("clear");
}
void changeShipSize(){

    int size[10];

    for ( int a = 0 ; a < 10 ; a++){
        printf(" Enter count of 1 by %d ships :   \n", a+1);
        scanf("%d", &size[a]);
#if D
        setColor('g');
        printf("                         Data size[%d] = %d\n", a, size[a] );
        fflush(stdout);
        setColor('n');
#endif
    }

    //==========================================================
    FILE* t = fopen("GameData\\ShipSize.bin", "wb");
    if ( t == NULL){
        printf("can't open shipSize.bin\n");
    }
    for ( int a = 0 ; a < 10 ; a++){
        int z = size[a];
        fwrite(&z,sizeof(int),1,t);
    }
    fclose(t);
    //====================================================

    printf("\n\nship sizes has been successfully changed.\n"
           "Restart the Game to apply changes\n\n\n");
    fflush(stdout);
    warning = 1;
    Sleep(7000);
    system("clear");

};

int makeRandomNumber( int en, int st){
    time_t t = time(NULL);
    srand(t);
    int res = (rand()%(st - en +1 )) + en;
    return res;
}


void setCoordForShip(coord firstIn, coord secIn, ship* pShip){
    // setting nose and tail
    // should be in order to work

    // for boats
if( pShip->size == 1){
    pShip->coordArray[0].x = firstIn.x;
    pShip->coordArray[0].y = firstIn.y;
    return;
}



if ( pShip->pos == 'H') {

    pShip->coordArray[0].y = firstIn.y; //sabet
    pShip->coordArray[pShip->size-1].y = firstIn.y;

            if(firstIn.x < secIn.x){
                pShip->coordArray[0].x = firstIn.x;
                pShip->coordArray[pShip->size-1].x = secIn.x;
            }else{
                pShip->coordArray[0].x = secIn.x;
                pShip->coordArray[pShip->size-1].x =firstIn.x;
            }
}
if(pShip->pos == 'V') {

    pShip->coordArray[0].x = firstIn.x; //sabet
    pShip->coordArray[pShip->size-1].x = firstIn.x; //sabet

    if(firstIn.y < secIn.y){
        pShip->coordArray[0].y = firstIn.y;
        pShip->coordArray[pShip->size-1].y = secIn.y;
    }else{
        pShip->coordArray[0].y = secIn.y;
        pShip->coordArray[pShip->size-1].y =firstIn.y;
    }
}
    // end the function if size of ship is 2
    if ( pShip->size == 2) return;

    if(pShip->pos == 'H') {
        for (int a = 1; a < pShip->size - 1; a++) {
            pShip->coordArray[a].x = pShip->coordArray[0].x + a;
            pShip->coordArray[a].y = pShip->coordArray[0].y;
        }
        return;
    }
    if (pShip->pos == 'V'){

            for ( int a = 1 ; a < pShip->size-1 ; a++){
                pShip->coordArray[a].y = pShip->coordArray[0].y + a;
                pShip->coordArray[a].x = pShip->coordArray[0].x;
    }
        return;

    }

}




void arrCpr2D(int x, int y, char dst_arr[x][y], char src_arr[x][y]){
    for ( int a = 0 ; a <  x ; a++){
        for ( int b = 0 ; b < y ; b++){
            dst_arr[a][b] = src_arr[a][b];
        }
    }
}


int coinCalc( int desSize){
    int shipSizeArr[MAX_SHIP_SIZE];
    int max=0;
    FILE* fShipSize;
    fShipSize = fopen("GameData\\ShipSize.bin","rb");
    if ( fShipSize == NULL){
        printf("Can't Open ShipSize.bin\n");
    }
    for ( int a = 0 ; a < MAX_SHIP_SIZE ; a++){
        int z;
        fread(&z,sizeof(int),1,fShipSize);
        shipSizeArr[a] = z;
    }
    fclose(fShipSize);
    for ( int b = 0 ; b < MAX_SHIP_SIZE ; b++){
      if(shipSizeArr[b] > max){
          max = shipSizeArr[b];
      }
    }
    int res = (5 * max) / desSize;
    return res;
}

void saveScoresInFile(acc user){
FILE* fp;
acc curr;
fp = fopen("GameData\\PlayerData.bin", "rb+");

    while (fread(&curr, sizeof (acc), 1 , fp) >= 1){
    if( curr.num == user.num){
        fseek(fp, -1 * sizeof (acc), SEEK_CUR);
        fwrite(&user, sizeof (acc),1,fp);
    }
}


}


void printScoreBoard(){

    FILE* fp;
    acc prof;
    //getting last saved profile num
    fp = fopen("GameData\\PlayerData.bin", "rb");
    fseek(fp,-1*(sizeof(acc)),SEEK_END);
    fread(&prof, sizeof(acc),1,fp);
    //making the array
    acc profArr[prof.num];
    rewind(fp);
    for(int a = 0 ; a < prof.num ; a++){
        fread(&profArr[a], sizeof(acc), 1 , fp);
    }
    //now we got the array of all accounts
    acc tmp;
    for( int a = 0 ; a < prof.num ; a++){
        for ( int b = 0 ; b < prof.num ; b++){
            if( profArr[a].coin > profArr[b].coin){
                tmp = profArr[a];
                profArr[a] =profArr[b];
                profArr[b] = tmp;

            }


        }
    }
    setColor('y');
    printf("\n\n\n%s is the Boss with score of %d\n\n\n", profArr[0].username,profArr[0].coin);
    setColor('n');
for ( int a = 0 ; a < prof.num ; a++){

    printf("%d.%s  ..............................  %d\n\n", a+1, profArr[a].username, profArr[a].coin);
}
    printf("Press any key to continue . . . \n\n");
fflush(stdout);
int t;
scanf("%d", &t);
system("clear");
}


