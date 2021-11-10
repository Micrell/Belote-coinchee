#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "fonctions.h"


//exchange 2 values
void changeValues (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//shuffle the deck
void shuffleRandon ( int arr1[], int n )
{
    srand(time(NULL));
    int i;
    for (i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        changeValues(&arr1[i], &arr1[j]);
    }
}

//clear the stdin buffer
void clearBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

//allow us to have a secure imput (without risks of bufferoverflow)
int read(int *array, int length)
{

    int *enterPos = NULL;

    //printf("bf fgets\n");
    if (fgets(array, length, stdin) != NULL)
    {
      //printf("af fgets\n");
        enterPos = strchr(array, '\n');
        if (enterPos != NULL)
        {
            *enterPos = '\0';
        }
        else
        {
            clearBuffer();
        }
        return 1;
    }
    else
    {
        clearBuffer();
        return 0;
    }
}

int main()
{
    int startChoice;

    startChoice = startMenu();
    printf("start choice : %d\n", startChoice);




    switch(startChoice)
    {
    case 1:
        playGame();
        break;
    case 2:
        printSB();
        break;
    case 3:

        break;
    }




return 0;
}

//start the game
int playGame()
{
    //system("cls");
    int ref[32] = {71,72,73,74,81,82,83,84,91,92,93,94,101,102,103,104,111,112,113,114,121,122,123,124,131,132,133,134,11,12,13,14};
    int arr1[32] = {71,72,73,74,81,82,83,84,91,92,93,94,101,102,103,104,111,112,113,114,
                          121,122,123,124,131,132,133,134,11,12,13,14};
    int score[2]={0,0};

    char getPseudo[100];
    clearBuffer();
    printf("What is your pseudo ? ");
    //scanf("%s", getPseudo);
    read(getPseudo, 100);

    int *pack = "NULL";
    shuffleRandon (arr1, 32);
    pack = DistributeCards(arr1);
    //int dealer = rand() % 4;1
    int dealer = 0;
    switch(dealer)
    {
    case 0:
        printf("South is dealer\n");
        break;
    case 1:
        printf("West is dealer\n");
        break;
    case 2:
        printf("North is dealer\n");
        break;
    case 3:
        printf("East is dealer\n");
        break;
    }

    //boardMenu();
    while (*score < 701 && *(score+1)<701) {
      Round(dealer, pack,score);
      dealer++;
      int k;
      for(k=0;k<32;k++){
        arr1[k]=ref[k];
      }

      shuffleRandon (arr1, 32);
      pack = DistributeCards(arr1);
    }
    if(*score > *(score+1)){
      printf("The team one won !!!\n");
    }else {
      printf("The team two won !!!\n");
    }


    writeEndScoreP(*score, getPseudo);

return 0;
}

void printSB()
{

    printScoreboard();
}
