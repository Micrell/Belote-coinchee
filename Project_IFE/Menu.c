#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"

int startMenu(){

printf("\n");
printf("BBBBBBBBBBBBBBBBB                      lllllll                           tttt\n");
printf("B::::::::::::::::B                     l:::::l                        ttt:::t\n");
printf("B::::::BBBBBB:::::B                    l:::::l                        t:::::t\n");
printf("BB:::::B     B:::::B                   l:::::l                        t:::::t\n");
printf("  B::::B     B:::::B    eeeeeeeeeeee    l::::l    ooooooooooo   ttttttt:::::ttttttt        eeeeeeeeeeee\n");
printf("  B::::B     B:::::B  ee::::::::::::ee  l::::l  oo:::::::::::oo t:::::::::::::::::t      ee::::::::::::ee\n");
printf("  B::::BBBBBB:::::B  e::::::eeeee:::::eel::::l o:::::::::::::::ot:::::::::::::::::t     e::::::eeeee:::::ee\n");
printf("  B:::::::::::::BB  e::::::e     e:::::el::::l o:::::ooooo:::::otttttt:::::::tttttt    e::::::e     e:::::e\n");
printf("  B::::BBBBBB:::::B e:::::::eeeee::::::el::::l o::::o     o::::o      t:::::t          e:::::::eeeee::::::e\n");
printf("  B::::B     B:::::Be:::::::::::::::::e l::::l o::::o     o::::o      t:::::t          e:::::::::::::::::e\n");
printf("  B::::B     B:::::Be::::::eeeeeeeeeee  l::::l o::::o     o::::o      t:::::t          e::::::eeeeeeeeeee\n");
printf("  B::::B     B:::::Be:::::::e           l::::l o::::o     o::::o      t:::::t    tttttte:::::::e\n");
printf("BB:::::BBBBBB::::::Be::::::::e         l::::::lo:::::ooooo:::::o      t::::::tttt:::::te::::::::e\n");
printf("B:::::::::::::::::B  e::::::::eeeeeeee l::::::lo:::::::::::::::o      tt::::::::::::::t e::::::::eeeeeeee\n");
printf("B::::::::::::::::B    ee:::::::::::::e l::::::l oo:::::::::::oo         tt:::::::::::tt  ee:::::::::::::e\n");
printf("BBBBBBBBBBBBBBBBB       eeeeeeeeeeeeee llllllll   ooooooooooo             ttttttttttt      eeeeeeeeeeeeee\n");

printf("\n\n\n\n\n");
printf("Welcome ! We recommand you to play in full screen for a better experience\n\n");
printf("What do you want to do ? (press the number according to what you want to do)\n");
printf("\n");
printf("1: Start a new party\n");
printf("2: Show the best scores\n");
printf("3: Exit\n");


int choice;

do{
    printf("Choice :  ");
    scanf("%d", &choice);
}while(choice < 1 || choice > 3);


return choice;

}

void boardMenu(){

//system("cls"); //delete console




}
