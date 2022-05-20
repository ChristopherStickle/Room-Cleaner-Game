#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int respect = 40;    //respect value for the player
int (*building)[6];  //pointer to a 2d array representing each row as a room and columns as ID,state,exit_N,exit_S,exit_E,exit_W
int (*creatures)[3]; //pointer to a 2d array representing each row as a creature and columns as ID,type,room
int *pc_pointer;

// establish the number of rooms to play with from user prompt
int GetRooms(){
    int nRooms=0;
    while(nRooms < 1 || nRooms > 100){
        printf("How many rooms would you like to play with (1-100): ");
        scanf("%d", &nRooms);
    }
    printf("You will play with %d rooms in your building. ", nRooms); //echo check
    return nRooms;
}

// create an array of and populate it with user input
void LoadBuilding(int nRooms){
    int i,j,k=0;
    printf("Please enter the room details: \n");
    for(j=0;j<nRooms;j++){
        building[j][0] = k;
        for(i=1;i<6;i++){
            scanf("%d",&building[j][i]);
        }
        k++;
    }
    //echo check
    for(j=0;j<nRooms;j++){
        printf("Room %d has values:", building[j][0]);
        for(i=1;i<6;i++){
            printf(" %d", building[j][i]);
        }
        printf("\n");
    }
    //end echo check
}

// establish the number of Creatures to play with from user prompt
int GetCreatures(){
    int nCreatures=0;
    while(nCreatures < 1 || nCreatures > 100){
        printf("How many creatures would you like to play with (1-100): ");
        scanf("%d", &nCreatures);
    }
    printf("You will play with %d creatures in your building. ", nCreatures); //echo check
    return nCreatures;
}

// create an array of and populate it with user input
void LoadCreatures(int nCreatures){
    int i,j,k=0;
    printf("Please enter the details for each creature: \n");
    for(j=0;j<nCreatures;j++){
        creatures[j][0] = k;
        for(i=1;i<3;i++){
            scanf("%d",&creatures[j][i]);
        }
        k++;
    }
    //echo check
    for(j=0;j<nCreatures;j++){
        printf("Creature %d has values:", creatures[j][0]);
        for(i=1;i<3;i++){
            printf(" %d", creatures[j][i]);
        }
        printf("\n");
    }
    //end echo check
}

//loop through creatures and sets pc_pointer
void GetPlayer(int nCreatures){
    for(int i = 0;i<nCreatures;i++){
        if(creatures[i][1]==0){
            pc_pointer = *(creatures+i);
        }
    }
}

//Describes the current room to the player in terms of: State, Exits, Creatures
void DisplayRoom(int nCreatures){
    int current_room = pc_pointer[2];
    printf("\nYou are in room %d. ", current_room);
    int state = building[current_room][1];
    switch (state)
    {
    case 0:
        printf("The room is CLEAN. ");
        break;
    case 1:
        printf("The room is HALF-DIRTY. ");
        break;
    case 2:
        printf("The room is DIRTY. ");
        break;
    default:
        break;
    }
    if (building[current_room][2] >= 0){printf("There is an exit to room %d, to the North. ",building[current_room][2]);}
    if (building[current_room][3] >= 0){printf("There is an exit to room %d, to the South. ",building[current_room][3]);}
    if (building[current_room][4] >= 0){printf("There is an exit to room %d, to the East. ",building[current_room][4]);}
    if (building[current_room][5] >= 0){printf("There is an exit to room %d, to the West. ",building[current_room][5]);}
    printf("\nThis room contains the following Creatures: \n");
    for(int i=0;i<nCreatures;i++){
        if(creatures[i][2]==current_room){
            switch (creatures[i][1])
            {
            case 0:
                printf("PC\n");
                break;
            case 1:
            printf("Animal %d \n",creatures[i][0]);
                break;
            case 2:
            printf("NPC %d \n",creatures[i][0]);
                break;
            default:
                break;
            }
        }
    }
}

//Creature reactions
void GrumbleGrowl(int ID, int degree){
    switch (degree)
    {
    case 1:
        if(creatures[ID][1]==1){respect--;printf("Animal %d growls. Your respect is now %d. \n",creatures[ID][0], respect);}
        if(creatures[ID][1]==2){respect--;printf("NPC %d grumbles. Your respect is now %d. \n",creatures[ID][0], respect);}
        break;
    case 3:
        if(creatures[ID][1]==1){respect -=3;printf("Animal %d growls a lot. Your respect is now %d. \n",creatures[ID][0], respect);}
        if(creatures[ID][1]==2){respect -=3;printf("NPC %d grumbles a lot. Your respect is now %d. \n",creatures[ID][0], respect);}
        break;
    default:
        break;
    }
}
void LickSmile(int ID, int degree){
    switch (degree)
    {
    case 1:
        if(creatures[ID][1]==1){respect++;printf("Animal %d licks your face. Your respect is now %d. \n",creatures[ID][0], respect);}
        if(creatures[ID][1]==2){respect++;printf("NPC %d smiles at you. Your respect is now %d. \n",creatures[ID][0], respect);}
        break;
    case 3:
        if(creatures[ID][1]==1){respect +=3;printf("Animal %d licks your face a lot. Your respect is now %d. \n",creatures[ID][0], respect);}
        if(creatures[ID][1]==2)respect +=3;{printf("NPC %d smiles at you a lot. Your respect is now %d. \n",creatures[ID][0], respect);}
        break;
    default:
        break;
    }
}

//Move command for PC and creatures
int Move(int ID, char direction,int nCreatures){
    int k=0; //for loop counter to check #of Creeatures in desired room
    int current_room = pc_pointer[2];
    if( creatures[ID][2] == current_room){ //Make sure Creature is in current room
        switch (direction)
        {
        case 'n':
            if (building[current_room][2] < 0 ){
                if(ID == *pc_pointer){printf("There is no exit to the North. \n");}//only print for player movement, not for creature
                else{printf("Creature %d tries to leave to the North, but there is no exit. \n",creatures[ID][0]);}
                return -1;break;
            }
            for(int i=0;i<nCreatures;i++){ //How many creatures are in desired room
                if(creatures[i][2]==building[current_room][2])k++;
            }
            if(k<10){
                creatures[ID][2]=building[current_room][2];
                if(ID == *pc_pointer){printf("You leave North to room %d. \n",building[current_room][2]);
                }else{
                    printf("Creature %d leaves North to room %d. \n",creatures[ID][0], building[current_room][2]);
                    if(creatures[ID][1]==1 && building[building[current_room][2]][1]==2){building[building[current_room][2]][1]--;}
                    if(creatures[ID][1]==2 && building[building[current_room][2]][1]==0){building[building[current_room][2]][1]++;}
                    }
            }else if(ID == *pc_pointer){printf("That room is to full to enter.\n");return -1;}//only print for player movement, not for creature
            else{printf("Creature %d tries to leave to the North, but hat room is to full to enter. \n",creatures[ID][0]);return -1;}
            return 0;break;

        case 's':
            if (building[current_room][3] < 0 ){
                if(ID == *pc_pointer){printf("There is no exit to the South. \n");}//only print for player movement, not for creature
                else{printf("Creature %d tries to leave to the South, but there is no exit. \n",creatures[ID][0]);}
                return -1;break;
            }
            for(int i=0;i<nCreatures;i++){ //How many creatures are in desired room
                if(creatures[i][2]==building[current_room][3])k++;
            }
            if(k<10){creatures[ID][2]=building[current_room][3];
                if(ID == *pc_pointer){printf("You leave South to room %d. \n",building[current_room][3]);
                }else{
                    printf("Creature %d leaves South to room %d. \n",creatures[ID][0], building[current_room][3]);
                    if(creatures[ID][1]==1 && building[building[current_room][3]][1]==2){building[building[current_room][3]][1]--;}
                    if(creatures[ID][1]==2 && building[building[current_room][3]][1]==0){building[building[current_room][3]][1]++;}
                    }
            }else if(ID == *pc_pointer){printf("That room is to full to enter.\n");return -1;}//only print for player movement, not for creature
            else{printf("Creature %d tries to leave to the South, but hat room is to full to enter. \n",creatures[ID][0]);return -1;}
            return 0;break;

        case 'e':
            if (building[current_room][4] < 0 ){
                if(ID == *pc_pointer){printf("There is no exit to the East. \n");}//only print for player movement, not for creature
                else{printf("Creature %d tries to leave to the East, but there is no exit. \n",creatures[ID][0]);}
                return -1;break;
            }
            for(int i=0;i<nCreatures;i++){ //How many creatures are in desired room
                if(creatures[i][2]==building[current_room][4])k++;
            }
            if(k<10){creatures[ID][2]=building[current_room][4];
                if(ID == *pc_pointer){printf("You leave East to room %d. \n",building[current_room][4]);
                }else{
                    printf("Creature %d leaves East to room %d. \n",creatures[ID][0], building[current_room][4]);
                    if(creatures[ID][1]==1 && building[building[current_room][4]][1]==2){building[building[current_room][4]][1]--;}
                    if(creatures[ID][1]==2 && building[building[current_room][4]][1]==0){building[building[current_room][4]][1]++;}
                    }
            }else if(ID == *pc_pointer){printf("That room is to full to enter.\n");return -1;}//only print for player movement, not for creature
            else{printf("Creature %d tries to leave to the east, but hat room is to full to enter. \n",creatures[ID][0]);return -1;}
            return 0;break;

        case 'w':
            if (building[current_room][5] < 0 ){
                if(ID == *pc_pointer){printf("There is no exit to the West. \n");}//only print for player movement, not for creature
                else{printf("Creature %d tries to leave to the West, but there is no exit. \n",creatures[ID][0]);}
                return -1;break;
            }
            for(int i=0;i<nCreatures;i++){ //How many creatures are in desired room
                if(creatures[i][2]==building[current_room][5])k++;
            }
            if(k<10){creatures[ID][2]=building[current_room][5];
                if(ID == *pc_pointer){printf("You leave West to room %d. \n",building[current_room][5]);
                }else{
                    printf("Creature %d leaves West to room %d. \n",creatures[ID][0], building[current_room][5]);
                    if(creatures[ID][1]==1 && building[building[current_room][5]][1]==2){building[building[current_room][5]][1]--;}
                    if(creatures[ID][1]==2 && building[building[current_room][5]][1]==0){building[building[current_room][5]][1]++;}
                    }
            }else if(ID == *pc_pointer){printf("That room is to full to enter.\n");return -1;}//only print for player movement, not for creature
            else{printf("Creature %d tries to leave to the West, but hat room is to full to enter. \n",creatures[ID][0]);return -1;}
            return 0;break;

        default:
            break;
        }
    }else if(ID!=*pc_pointer){printf("No such creature %d in current room. \n",ID);}
    return -1;//error flag, for debugging, no movment occured
}

//Call this if the creature moves becasue of a change of room state. This handles random movement and exiting the simulation.
void CreatureMove(int ID, int nCreatures){
    int current_room = pc_pointer[2];
    int rand_direction = rand() % 4+1; //random # 1-4 (kinda)
    int ret;
    printf("Creature %d is dismayed at the state this room has fallen to...\n",creatures[ID][0]);
    switch (rand_direction)
    {
    case 1:  //North, south, east, west
        ret = Move(ID,'n',nCreatures);
        if (ret==-1)
        {
            ret = Move(ID,'s',nCreatures);
        }if (ret==-1)
        {
            ret = Move(ID,'e',nCreatures);
        }if (ret==-1)
        {
            ret = Move(ID,'w',nCreatures);
        }if (ret==-1){
            printf("Creature %d, has nowhere to go. In its panic, it jumps and bursts through the roof! Never to be seen again...\n",creatures[ID][0]);
            creatures[ID][0]=(-1);creatures[ID][1]=(-1);creatures[ID][2]=(-1);
            for (int i = 0; i < nCreatures; i++){
                if (creatures[i][2]==current_room){GrumbleGrowl(i,1);}
            }
        }
        break;
    case 2: //south, east, west, north
        ret = Move(ID,'s',nCreatures);
        if (ret==-1)
        {
            ret = Move(ID,'e',nCreatures);
        }if (ret==-1)
        {
            ret = Move(ID,'w',nCreatures);
        }if (ret==-1)
        {
            ret = Move(ID,'n',nCreatures);
        }if (ret==-1){
            printf("Creature %d, has nowhere to go. In its panic it jumps and bursts through the roof! Never to be seen again...\n",creatures[ID][0]);
            creatures[ID][0]=(-1);creatures[ID][1]=(-1);creatures[ID][2]=(-1);
            for (int i = 0; i < nCreatures; i++){
                if (creatures[i][2]==current_room){GrumbleGrowl(i,1);}
            }
        }
        break;
    case 3: //east, west, north, south
        ret = Move(ID,'e',nCreatures);
        if (ret==-1)
        {
            ret = Move(ID,'w',nCreatures);
        }if (ret==-1)
        {
            ret = Move(ID,'n',nCreatures);
        }if (ret==-1)
        {
            ret = Move(ID,'s',nCreatures);
        }if (ret==-1){
            printf("Creature %d, has nowhere to go. In its panic it jumps and bursts through the roof! Never to be seen again...\n",creatures[ID][0]);
            creatures[ID][0]=(-1);creatures[ID][1]=(-1);creatures[ID][2]=(-1);
            for (int i = 0; i < nCreatures; i++){
                if (creatures[i][2]==current_room){GrumbleGrowl(i,1);}
            }
        }
        break;
    case 4: //west, north, south, east
        ret = Move(ID,'w',nCreatures);
        if (ret==-1)
        {
            ret = Move(ID,'n',nCreatures);
        }if (ret==-1)
        {
            ret = Move(ID,'s',nCreatures);
        }if (ret==-1)
        {
            ret = Move(ID,'e',nCreatures);
        }if (ret==-1){
            printf("Creature %d, has nowhere to go. In its panic it jumps and bursts through the roof! Never to be seen again...\n",creatures[ID][0]);
            creatures[ID][0]= (-1);creatures[ID][1]= (-1);creatures[ID][2]= (-1);
            for (int i = 0; i < nCreatures; i++){
                if (creatures[i][2]==current_room){GrumbleGrowl(i,1);}
            }
        }
        break;
    default:
        break;
    }
    // //echo check
    // int j,k;
    // for(j=0;j<nCreatures;j++){
    //     printf("Creature %d has values:", creatures[j][0]);
    //     for(k=1;k<3;k++){
    //         printf(" %d", creatures[j][k]);
    //     }
    //     printf("\n");
    // }
    // //end echo check
}

//clean or dirty room 0-clean 1-half 2-dirty
void ChangeState(int ID, char cmd, int nCreatures){
    int current_room = pc_pointer[2];
    int starting_state = building[current_room][1];
    if( creatures[ID][2] == current_room){
    switch (cmd)
    {
    case 'c':
        if(building[current_room][1]==0){printf("This room is already sqeaky clean! \n");}
        else{
            building[current_room][1] -= 1;
            //---------------display state after change---------------------------------//
            int state = building[current_room][1];
            switch (state)
            {
            case 0:
                printf("The room is now CLEAN. \n");
                break;
            case 1:
                printf("The room is now HALF-DIRTY. \n");
                break;
            case 2:
                printf("The room is now DIRTY. \n");
                break;
            default:
                break;
            }
            for (int i = 0; i < nCreatures; i++)
            {
                if (creatures[i][2]==current_room && creatures[i][1]==1){ //Animal reactions
                    if(ID==creatures[i][0]){
                        LickSmile(ID,3);
                    }else{
                    LickSmile(creatures[i][0],1);
                    }
                }
                if (creatures[i][2]==current_room && creatures[i][1]==2){ //NPC reactions
                    if(ID==creatures[i][0]){
                        GrumbleGrowl(ID,3);
                    }else{
                    GrumbleGrowl(creatures[i][0],1);
                    }
                    if(building[current_room][1]==0){ //NPC leaves
                        CreatureMove(creatures[i][0],nCreatures);
                    }
                }
            }
        }
        break;
    case 'd':
        if(building[current_room][1]==2){printf("This room is so dirty it can't get any worse.... \n");}
        else{
            building[current_room][1] += 1;
            //---------------display state after change---------------------------------//
            int state = building[current_room][1];
            switch (state)
            {
            case 0:
                printf("The room is now CLEAN. \n");
                break;
            case 1:
                printf("The room is now HALF-DIRTY. \n");
                break;
            case 2:
                printf("The room is now DIRTY. \n");
                break;
            default:
                break;
            }
            for (int i = 0; i < nCreatures; i++)
            {
                if (creatures[i][2]==current_room && creatures[i][1]==2){ //NPC reactions
                    if(ID==creatures[i][0]){
                        LickSmile(ID,3);
                    }else{
                        LickSmile(creatures[i][0],1);
                    }
                }
                if (creatures[i][2]==current_room && creatures[i][1]==1){ //Animal reactions
                    if(ID==creatures[i][0]){
                        GrumbleGrowl(ID,3);
                    }else{
                        GrumbleGrowl(creatures[i][0],1);
                    }
                    if(building[current_room][1]==2){ //Animal leaves
                        CreatureMove(creatures[i][0],nCreatures);
                    }
                }
            }
        }
        break;
    default:
        break;
    }
    }else if(ID!=*pc_pointer){printf("No such creature %d in current room. \n",ID);}
}

//Clear Heap
void ClearHeap(){
    free(building);
    free(creatures);
}

int main()
{
    printf("\n\n\n"
            "██████████████████████████████████████████████████████████████████████████████████████████\n"
            "█▄─█▀▀▀█─▄█▄─▄▄─█▄─▄███─▄▄▄─█─▄▄─█▄─▀█▀─▄█▄─▄▄─███─▄─▄─█─▄▄─███─▄▄▄─█─█─██▀▄─██─▄▄─█─▄▄▄▄█\n"
            "██─█─█─█─███─▄█▀██─██▀█─███▀█─██─██─█▄█─███─▄█▀█████─███─██─███─███▀█─▄─██─▀─██─██─█▄▄▄▄─█\n"
            "▀▀▄▄▄▀▄▄▄▀▀▄▄▄▄▄▀▄▄▄▄▄▀▄▄▄▄▄▀▄▄▄▄▀▄▄▄▀▄▄▄▀▄▄▄▄▄▀▀▀▀▄▄▄▀▀▄▄▄▄▀▀▀▄▄▄▄▄▀▄▀▄▀▄▄▀▄▄▀▄▄▄▄▀▄▄▄▄▄▀\n"
            "                   █████████████████████████████████████████████\n"
            "                   █─▄▄▄─█▄─▄███▄─▄▄─██▀▄─██▄─▀█▄─▄█▄─▄▄─█▄─▄▄▀█\n"
            "                   █─███▀██─██▀██─▄█▀██─▀─███─█▄▀─███─▄█▀██─▄─▄█\n"
            "                   ▀▄▄▄▄▄▀▄▄▄▄▄▀▄▄▄▄▄▀▄▄▀▄▄▀▄▄▄▀▀▄▄▀▄▄▄▄▄▀▄▄▀▄▄▀\n\n\n");
    int nRooms = GetRooms();
    building = malloc(sizeof(int[nRooms][6]));
    LoadBuilding(nRooms);

    int nCreatures = GetCreatures();
    creatures = malloc(sizeof(int[nCreatures][3]));
    LoadCreatures(nCreatures);
    GetPlayer(nCreatures);

    //printf("The PC is creature %d, type %d, and in room %d. \n\n", *pc_pointer,*(pc_pointer+1),*(pc_pointer+2));

    char command[20];
    while(!(respect<=0) && !(respect>=80)){
        printf("\nWhat would you like to do? type 'help' to list accepted commands.\n");
        scanf("%s",command);
        if (strcmp(command, "exit") == 0){ //"exit" quit game
            printf("Thanks for playing! Your end score is %d.\n", respect);
            break;
        }
        else if (strcmp(command, "score") == 0){ //"score" Display current score.
            printf("Your score is %d.\n", respect);
        }
        else if (strcmp(command, "look") == 0){ //"look" Discribe current room
            DisplayRoom(nCreatures);
        }
        else if (strcmp(command, "clean") == 0 || strcmp(command, "dirty") == 0){ //"clean/dirty" clean/dirty current room by 1 degree
            ChangeState(pc_pointer[0],command[0],nCreatures);
        }
        else if (strcmp(command, "north") == 0 || strcmp(command, "south") == 0
                ||strcmp(command, "east") == 0 || strcmp(command, "west") == 0 ){ //"north" move north
            int ret = Move(pc_pointer[0],command[0], nCreatures);
        }
        else if (strstr(command,":") != NULL){ //"creatureID:direction/clean/dirty" creature to, move direction/clean/dirty
            char *direction;
            long ID;
            ID = strtol(command, &direction, 10);
            if (strcmp((direction+1), "north")==0||strcmp((direction+1), "south")==0||strcmp((direction+1), "east")==0||strcmp((direction+1), "west")==0){
                int ret = Move(ID, *(direction+1), nCreatures);
                if(ret==1){GrumbleGrowl(ID,1);}
            }else if (strcmp((direction+1), "clean")==0||strcmp((direction+1), "dirty")==0){
                ChangeState(ID,*(direction+1),nCreatures);
            }else{printf("Invalid command. Type 'help' to list accepted commands.\n");}
        }
        else if (strcmp(command, "help") == 0){ //"help" list commands
            printf("Valid commands are: look, score, clean, creature:clean, north, south, east, west, exit \n");
        }else{
            printf("Invalid command. Type 'help' to list accepted commands.\n");
        }

        if(respect <= 0){printf("You Lose!");}
        else if(respect >= 80) {printf("You Win!");}
    }
    ClearHeap();
}