#define D 0


void saveBattle(char name[50], int mapX, int mapY, char user1sea[mapX][mapY], char user2sea[mapX][mapY],
                ship *pHeadUser1, ship *pHeadUser2, acc *user1, acc *user2, int rol) {
    char directory[50] = "GameSaves\\";
    char bin[] = ".bin";
    strcat(name, bin);



    //getting data's from addresses
    acc user1toSave = *user1;
    acc user2toSave = *user2;
    char sea1[mapX][mapY];
    char sea2[mapX][mapY];
    arrCpr2D(mapX, mapY, sea1, user1sea);
    arrCpr2D(mapX, mapY, sea2, user2sea);

//marking the list


    ship listArray[50];
    ship llistArray[50];
//order of saving:
//1. map size
//2. user 1 sea
//3. user 2 sea
// user 1 list
// user 2 list
// user 1 acc
//user 2 acc
//rol

    strcat(directory, name);

    FILE *t = fopen("GameSaves\\saveFileNames.bin", "ab");

    fwrite(directory, sizeof(char), 50, t);
    fclose(t);


    FILE *fp = fopen(directory, "wb+");
    if (fp == NULL) {
        printf("\nError in creating save file");
    }
    //map size
    fwrite(&mapX, sizeof(int), 1, fp);
    fwrite(&mapY, sizeof(int), 1, fp);

    //user 1


    for (int b = 0; b < mapY; b++) {

        fwrite(&sea1[b], sizeof(char), mapX, fp);
    }


    for (int a = 0; a < mapX; a++) {
        for (int b = 0; b < mapY; b++) {

            fwrite(&sea2[a][b], sizeof(char), 1, fp);
        }
    }

    //linked list to array

    //finding list count
    ship *pCounter = pHeadUser1;
    int counter1 = 0, counter2 = 0;
    while (pCounter != NULL) {
        counter1++;
        pCounter = pCounter->pNextShip;
    }
    int u1 = counter1;

    pCounter = pHeadUser2;
    while (pCounter != NULL) {
        counter2++;
        pCounter = pCounter->pNextShip;
    }
    int u2 = counter2;

    int a = 0;
    ship *curr = pHeadUser1;
    while (curr != NULL) {

        listArray[a].pNextShip = curr->pNextShip;
        listArray[a].pos = curr->pos;
        listArray[a].size = curr->size;
        listArray[a].fullStatus = curr->fullStatus;
        listArray[a].coordArray->x = curr->coordArray->x;
        listArray[a].coordArray->y = curr->coordArray->y;
        llistArray[a].mark = u1;
        curr = curr->pNextShip;
        a++;
    }

    a = 0;
    curr = pHeadUser2;
    while (curr != NULL) {

        llistArray[a].pNextShip = curr->pNextShip;
        llistArray[a].pos = curr->pos;
        llistArray[a].size = curr->size;
        llistArray[a].fullStatus = curr->fullStatus;
        llistArray[a].coordArray->x = curr->coordArray->x;
        llistArray[a].coordArray->y = curr->coordArray->y;
        llistArray[a].mark = u2;

        curr = curr->pNextShip;
        a++;
    }

    // array saving backwars
    for (int s = counter1; s > 0; s--) {

        fwrite(&listArray[s], sizeof(ship), 1, fp);
    }

    for (int s = counter2; s > 0; s--) {

        fwrite(&llistArray[s], sizeof(ship), 1, fp);
    }


    fwrite(&user1toSave, sizeof(acc), 1, fp);
    fwrite(&user2toSave, sizeof(acc), 1, fp);

    fwrite(&rol, sizeof(int), 1, fp);
}


void loadBattle(int *mapX, int *mapY, char user1sea[*mapX][*mapY], char user2sea[*mapX][*mapY],
                ship *pHeadUser1, ship *pHeadUser2, acc *user1, acc *user2, int *rol) {
    ship listArray[50];
    ship llistArray[50];
    char t1[*mapX][*mapY];
    char t2[*mapX][*mapY];
    char fName[20][50];
    char namee[50];
    char str[100] = "GameSaves\\";
    FILE *nameFp = fopen("GameSaves\\saveFileNames.bin", "rb");
    int a = 0;
    while (fread(fName[a], sizeof(char), 50, nameFp) >= 50) {

        printf("%d. %s\n", a + 1, fName[a]);
        fflush(stdout);


        a++;
    }
    int n;
    printf("\n\nEnter Save number\n\n");
    scanf("%d", &n);
    rewind(nameFp);
    for (int s = 1; s <= n; s++) {
        fread(namee, sizeof(char), 50, nameFp);
    }
    fclose(nameFp);
//loading file

    FILE *save = fopen(namee, "rb");

    fread(mapX, sizeof(int), 1, save);
    fread(mapY, sizeof(int), 1, save);


    for (int f = 0; f < *mapX; f++) {
        for (int g = 0; g < *mapY; g++) {
            char x;
            fread(&x, sizeof(char), 1, save);
            t2[f][g] = x;
        }
    }
    arrCpr2D(*mapX, *mapY, user1sea, t1);

    for (int f = 0; f < *mapX; f++) {
        for (int g = 0; g < *mapY; g++) {

            fread(&t2[f][g], sizeof(char), 1, save);
        }
    }
    arrCpr2D(*mapX, *mapY, user2sea, t2);

    int s = 0;
    int counter1 = 0, counter2 = 0;
    while (1) {

        fread(&listArray[s], sizeof(ship), 1, save);

        if (s == listArray->mark) break;
        s++;
    }

    counter1 = listArray[0].mark;
    while (1) {

        fread(&llistArray[s], sizeof(ship), 1, save);

        if (s == llistArray->mark) break;
        s++;
    }
    counter2 = listArray[0].mark;
//setting array back to list

    pHeadUser1 = NULL;
    ship *curr = pHeadUser1;
    for (int q = 0; q < counter1; q++) {
        curr = (ship *) malloc(sizeof(ship));

        curr->pNextShip = listArray[q].pNextShip;
        curr->pos = listArray[q].pos;
        curr->size = listArray[q].size;
        curr->fullStatus = listArray[q].fullStatus;
        curr->coordArray->x = listArray[q].coordArray->x ;
        curr->coordArray->y = listArray[q].coordArray->y ;


        curr->pNextShip = pHeadUser1;
        pHeadUser1 = curr;
    }
    pHeadUser2 = NULL;
    curr = pHeadUser2;
    for (int q = 0; q < counter2; q++) {
        curr = (ship *) malloc(sizeof(ship));

        curr->pNextShip = llistArray[q].pNextShip;
        curr->pos = llistArray[q].pos;
        curr->size = llistArray[q].size;
        curr->fullStatus = llistArray[q].fullStatus;
        curr->coordArray->x = llistArray[q].coordArray->x ;
        curr->coordArray->y = llistArray[q].coordArray->y ;


        curr->pNextShip = pHeadUser1;
        pHeadUser2 = curr;
    }


    fread(user1, sizeof(acc), 1, save);
    fread(user2, sizeof(acc), 1, save);

    fread(rol, sizeof(int), 1, save);


}




















