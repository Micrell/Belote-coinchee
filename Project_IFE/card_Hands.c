#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"

int DistributeCards(int card_package[]){

int north[8], south[8], east[8], west[8];
int i;


for(i=0 ; i<8 ; i++){

    south[i] = card_package[i];
    west[i]  = card_package[i+8];
    north[i] = card_package[i+16];
    east[i]  = card_package[i+24];

}
//Uncomment to cheat
/*
printf("\nNorth :");
    for(i=0 ; i<8 ; i++){
        numberToCard(north[i]);
    }

printf("\nSouth :");
    for(i=0 ; i<8 ; i++){
        numberToCard(south[i]);
    }

printf("\nEast :");
    for(i=0 ; i<8 ; i++){
        numberToCard(east[i]);
    }

printf("\nWest :");
    for(i=0 ; i<8 ; i++){
        numberToCard(west[i]);
    }
    */
    int *pack = card_package;
    return pack;
}


void numberToCard(int card){

    switch(card){
        case 71:
            printf("7C  ");
            break;
        case 72:
            printf("7S  ");
            break;
        case 73:
            printf("7H  ");
            break;
        case 74:
            printf("7D  ");
            break;
        case 81:
            printf("8C  ");
            break;
        case 82:
            printf("8S  ");
            break;
        case 83:
            printf("8H  ");
            break;
        case 84:
            printf("8D  ");
            break;
        case 91:
            printf("9C  ");
            break;
        case 92:
            printf("9S  ");
            break;
        case 93:
            printf("9H  ");
            break;
        case 94:
            printf("9D  ");
            break;
        case 101:
            printf("10C ");
            break;
        case 102:
            printf("10S ");
            break;
        case 103:
            printf("10H ");
            break;
        case 104:
            printf("10D ");
            break;
        case 111:
            printf("JC  ");
            break;
        case 112:
            printf("JS  ");
            break;
        case 113:
            printf("JH  ");
            break;
        case 114:
            printf("JD  ");
            break;
        case 121:
            printf("QC  ");
            break;
        case 122:
            printf("QS  ");
            break;
        case 123:
            printf("QH  ");
            break;
        case 124:
            printf("QD  ");
            break;
        case 131:
            printf("RC  ");
            break;
        case 132:
            printf("KS  ");
            break;
        case 133:
            printf("KH  ");
            break;
        case 134:
            printf("KD  ");
            break;
        case 11:
            printf("AC  ");
            break;
        case 12:
            printf("AS  ");
            break;
        case 13:
            printf("AH  ");
            break;
        case 14:
            printf("AD  ");
            break;
        case 0:
            printf("0   ");
            break;

    }

}

void numberToColor(int number)
{
    switch(number)
    {
    case 1:
        printf("Club");
        break;
    case 2:
        printf("Spade");
        break;
    case 3:
        printf("Heart");
        break;
    case 4:
        printf("Diamond");
        break;
    case 5:
        printf("All trump");
        break;
    case 6:
        printf("No trump");
        break;
    }
}

void numberToPlayer(int number)
{
    switch(number)
    {
    case 0:
        printf("Player");
        break;
    case 1:
        printf("WEST");
        break;
    case 2:
        printf("NORTH");
        break;
    case 3:
        printf("EAST");
        break;
    }
}
