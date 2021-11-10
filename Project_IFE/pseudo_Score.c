#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"
#define MAX_SIZE 1000

int fclose(FILE*);

//structure of a line in the .txt

typedef struct Player Player;
struct Player
{
    char pseudoP[100];
    int scoreP;
    int rankP;
};


//Use this function to print the scoreboard

int printScoreboard()
{
  printf("In scorboeard\n");
    char chain[MAX_SIZE] = "";

    //system("cls"); //clear the cmd

    printf("\n                                                                                               bbbbbbbb                                                                              dddddddd");
    printf("\n   SSSSSSSSSSSSSSS                                                                             b::::::b                                                                              d::::::d");
    printf("\n SS:::::::::::::::S                                                                            b::::::b                                                                              d::::::d");
    printf("\nS:::::SSSSSS::::::S                                                                            b::::::b                                                                              d::::::d");
    printf("\nS:::::S     SSSSSSS                                                                             b:::::b                                                                              d:::::d");
    printf("\nS:::::S                cccccccccccccccc   ooooooooooo   rrrrr   rrrrrrrrr       eeeeeeeeeeee    b:::::bbbbbbbbb       ooooooooooo     aaaaaaaaaaaaa  rrrrr   rrrrrrrrr       ddddddddd:::::d");
    printf("\nS:::::S              cc:::::::::::::::c oo:::::::::::oo r::::rrr:::::::::r    ee::::::::::::ee  b::::::::::::::bb   oo:::::::::::oo   a::::::::::::a r::::rrr:::::::::r    dd::::::::::::::d");
    printf("\n S::::SSSS          c:::::::::::::::::co:::::::::::::::or:::::::::::::::::r  e::::::eeeee:::::eeb::::::::::::::::b o:::::::::::::::o  aaaaaaaaa:::::ar:::::::::::::::::r  d::::::::::::::::d");
    printf("\n  SS::::::SSSSS    c:::::::cccccc:::::co:::::ooooo:::::orr::::::rrrrr::::::re::::::e     e:::::eb:::::bbbbb:::::::bo:::::ooooo:::::o           a::::arr::::::rrrrr::::::rd:::::::ddddd:::::d");
    printf("\n    SSS::::::::SS  c::::::c     ccccccco::::o     o::::o r:::::r     r:::::re:::::::eeeee::::::eb:::::b    b::::::bo::::o     o::::o    aaaaaaa:::::a r:::::r     r:::::rd::::::d    d:::::d");
    printf("\n       SSSSSS::::S c:::::c             o::::o     o::::o r:::::r     rrrrrrre:::::::::::::::::e b:::::b     b:::::bo::::o     o::::o  aa::::::::::::a r:::::r     rrrrrrrd:::::d     d:::::d");
    printf("\n            S:::::Sc:::::c             o::::o     o::::o r:::::r            e::::::eeeeeeeeeee  b:::::b     b:::::bo::::o     o::::o a::::aaaa::::::a r:::::r            d:::::d     d:::::d");
    printf("\n            S:::::Sc::::::c     ccccccco::::o     o::::o r:::::r            e:::::::e           b:::::b     b:::::bo::::o     o::::oa::::a    a:::::a r:::::r            d:::::d     d:::::d");
    printf("\nSSSSSSS     S:::::Sc:::::::cccccc:::::co:::::ooooo:::::o r:::::r            e::::::::e          b:::::bbbbbb::::::bo:::::ooooo:::::oa::::a    a:::::a r:::::r            d::::::ddddd::::::dd");
    printf("\nS::::::SSSSSS:::::S c:::::::::::::::::co:::::::::::::::o r:::::r             e::::::::eeeeeeee  b::::::::::::::::b o:::::::::::::::oa:::::aaaa::::::a r:::::r             d:::::::::::::::::d");
    printf("\nS:::::::::::::::SS   cc:::::::::::::::c oo:::::::::::oo  r:::::r              ee:::::::::::::e  b:::::::::::::::b   oo:::::::::::oo  a::::::::::aa:::ar:::::r              d:::::::::ddd::::d");
    printf("\n SSSSSSSSSSSSSSS       cccccccccccccccc   ooooooooooo    rrrrrrr                eeeeeeeeeeeeee  bbbbbbbbbbbbbbbb      ooooooooooo     aaaaaaaaaa  aaaarrrrrrr               ddddddddd   ddddd");

    printf("\n\n\n\nTOP 10 BEST SCORES\n\n");


    FILE* file = NULL;

    file = fopen("ScoreBoard.txt", "r");

    if (file != NULL)
    {
        //Read the ScoreBoard.txt

        while(fgets(chain, MAX_SIZE, file) != NULL)
        {
            printf("%s", chain); //print the scoreboard register in the .txt
        }

        //End of reading and writing
        fclose(file);
    }
    else
    {
     printf("Failed while opening the file ScoreBoard.txt");
     fclose(file);
    }

return 0;
}








//Use this function to put the pseudo and his score in the .txt

int writeEndScoreP(int score, char pseudo[])
{

    Player player;
    int i, lastRP, newRP;

    FILE* file = NULL;

    file = fopen("ScoreBoard.txt", "r+");

    if (file != NULL)
    {
        //Read the ScoreBoard.txt

        for(i=0;i<100;i++)
        {
            fscanf(file, "%d %s %d", &player.rankP, player.pseudoP, &player.scoreP);
        }
        lastRP = player.rankP;
        newRP = lastRP + 1;

        //Upload the score of the player in the scoreboard

        fprintf(file, "\n%d %s %d", newRP, pseudo, score);

        //End of reading and writing
        fclose(file);
    }
    else
    {
     printf("Failed while opening ScoreBoard.txt");
     fclose(file);
    }
return 0;
}

void update(Player list_player[], int n)
{
    int i;

    FILE* file = NULL;
    file = fopen("ScoreBoard.txt", "w+");

    if(file != NULL)
    {
        for(i=0; i<n ;i++)
        {
            list_player[i].rankP = i+1;
            fprintf(file, "%d %s %d\n", list_player[i].rankP, list_player[i].pseudoP, list_player[i].scoreP);

        }



        fclose(file);
    }
    else
    {
        printf("Failed while opening ScoreBoard.txt");
        fclose(file);
    }


}

void sort(Player list_player[], int n)
{

    int i, j;
    Player temp;

    for(i=n; i>=0; i--)
    {
        for(j=0; j<=i-1; j++)
        {
            if(list_player[j].scoreP < list_player[j+1].scoreP)
            {

                temp = list_player[j];
                list_player[j] = list_player[j+1];
                list_player[j+1] = temp;

            }
        }
    }
}

void howManyLine()
{
  printf("in howManyLine\n");
    int n;
    Player list_player[100];

    FILE* file = NULL;
    file = fopen("ScoreBoard.txt", "r");

    if(file != NULL)
    {
      printf("File != NULL \n");
        while(fscanf(file, "%d %s %d", &list_player[n].rankP, list_player[n].pseudoP, &list_player[n].scoreP) != EOF)
        {
          printf("n: %d \n", n);
            n++;
        }

        fclose(file);
    }
    else
    {
        printf("Failed while opening ScoreBoard.txt");
        fclose(file);
    }
    printf("\nscore_9= %d", list_player[9].scoreP);


    sort(list_player, n);
    update(list_player, n);
}
