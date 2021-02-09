#define MAX_SHIP_SIZE 10
#define D 845
//                    HERE ADD ALL NODES
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


    int x[MAX_SHIP_SIZE];
    int y[MAX_SHIP_SIZE];


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
    if (chosenColor == 'n' || chosenColor == 'N') {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);

    }
    if (chosenColor == 'g' || chosenColor == 'G') {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                FOREGROUND_GREEN );

    }

}
#if D
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
    while(currShip != NULL){
        printf("============================\n"
               "Ship %d in the list\n"
               "Size : %d\n"
               " coords : \n",currShip->size,index);

        for ( int a = 0 ; a < currShip->size ; a++){
            printf("x[%d] = %d   ",a,currShip->x[a]);
            printf("y[%d] = %d\n",a,currShip->y[a]);
        }
        printf("TotalStatus = %c\n"
               "Position = %c\n",currShip->fullStatus, currShip->pos);


        currShip = currShip->pNextShip;
        index++;
    }
    setColor('n');
}
#endif
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
        printf("                         Data size[%d] = %d\n", a, size[a] );
        fflush(stdout);
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
