#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"
#include <windows.h>


//Start of round
int Round(int dealer, int *pack, int *score){
  int roundResult[32];
  int contract[4]={70,0,-1,1};
  int Roundscore[4]={0,0,0,0};
  int speaker = ((dealer+1)%4);
  int ch =0;
  int t =0;
  system("cls");
  printf("Score : %d - %d\n", *score, *(score+1));
  showCards(pack);

    if (dealer == 3){

      printf("You are the first to speak, do you want to set a contract ? \n");
      printf("1: yes\n");
      printf("2: no\n");
      while (ch != '1' && ch != '2') {
        ch = getchar();
        //printf("choice : %d\n", ch);
        if (ch == '1'){
          clearBuffer();
          setContract(contract);
        }else if (ch == '2'){
          clearBuffer();
          speaker++;
          t++;
        }else {
          printf("Please enter 1 or 2 \n");
        }
      }


    } if(*contract == 70){
      while (speaker != *(contract+2) && t <4) {
        printf("Player code : %d \n",speaker);
        int *botCards = pack + 8 * speaker;
        int result[4]={0};
        ColorScore(botCards,result);
        //printf("Color score : %d / %d / %d / %d \n", result[0], result[1], result[2], result[3]);
        if(BotContract(result,contract) == 1){
          *(contract+2)=speaker;
          printf("The player %d set a contract of %d on the color ",speaker, *contract);
          numberToColor(*(contract+1));
          printf("\n\n");
        }else {
          printf("The player %d pass \n\n",speaker);
        }
        speaker++;
        if(speaker==4){
          speaker =0;
          if(*contract ==70){
            printf("There is no contract, do you want to take ?\n");
            printf("1: yes\n");
            printf("2: no\n");
          }else if(*contract <252){
            printf("The value of the contract is %d, do you want to raise or coinche? \n", *contract);
            printf("1: raise\n");
            printf("2: pass\n");
            if(*(contract+2) != 2){
              printf("3: coinche\n");
            }

          }

          while (ch != '1' && ch != '2' && (ch!='3' || contract ==70 || *(contract+2) == 2)) {
            ch = getchar();
            //printf("choice : %d\n", ch);
            if (ch == '1'){
              clearBuffer();
              setContract(contract);
            }else if (ch == '2'){
              clearBuffer();
            }else if(ch == '3' && *contract!=70){
              clearBuffer();
              *(contract+3)= 2;
            }else {
              printf("Please enter 1 or 2 \n");
            }
          }
        }
        t++;
      }
      if(*(contract+2) == -1){
        printf("Everybody passed, New round\n\n");
        return 0;
      }




    }
    int winner = trick(contract,(dealer+1)%4,pack, *(contract +1), Roundscore);
    int k;
    for ( k = 0; k < 6; k++) {
      printf("Next Trick ! (%d/8)\n", k+2);
      //winner = trickScore(); ( a faire)
       //en attendant le joueur commence
      winner = trick(contract,winner,pack, *(contract +1), Roundscore);

    }
    winner = trick(contract,winner,pack, *(contract +1), Roundscore);

    if(*(Roundscore+((winner+1)%4)) == 0 && *(Roundscore+((winner+3)%4)) == 0){
      *(Roundscore+winner) = *(Roundscore+winner) + 100;
    }else {
      *(Roundscore+winner) = *(Roundscore+winner) + 10;
    }


    endOfRound(Roundscore,contract,score);
    printf("Score : %d - %d \n", *score, *(score+1));
}

//show the hand of the player
void showCards(int *cards){
  int i;
  printf("Your hand : \n");
  for(i = 0; i<8;i++){
    numberToCard(*(cards+i));
  }
  printf("\n");
}

//allow the player to set the contract
int setContract(int *contract){
  int k = 1;
  int j = 1;
  printf("You have the following options : \n");
  while (*contract + 10 * j <= 160) {
    printf("%d: raise to %d\n",k, (*contract + 10 *j));
    k++;
    j++;
  }
  printf("%d: capot\n",k);
  printf("%d: General\n",k+1 );
  int a =0;
  char b[3];
  while (a<1 || a>k+1){
    read(b,3);
    //printf("b string : %s\n", b);
    //printf("b: %c / %c \n",b[0], b[1] );
    if(b[1] != '\n' && b[1] != '\0'){
      a = 10 * (b[0]-'0')+(b[1]-'0');
    }else {
      a = (b[0]-'0');
    }
    //printf("a: %d\n",a);
    if(a<k && a>0){
      *contract = *contract + 10 * a;
    }else if(a == k){
      *contract = 250;
    }else if(a == k +1) {
      *contract = 500;
    } else {
      printf("Please enter an integer between 1 and %d \n", k+1);
    }
  }
  printf("The contract value is : %d\n", *contract);

  printf("Wich color for the trump ? \n");
  printf("1: Club\n");
  printf("2: Spades\n");
  printf("3: Hearts\n");
  printf("4: Diamonds\n");
  printf("5: All trump\n");
  printf("6: No trump\n");

  char d[3];
  int e =0;
  while (e>6 || e<1) {
    read(d,3);
    //printf("d: %c / %c \n", d[0],d[1]);
    e = (d[0] - '0');
    //printf("e : %d\n",e);
  }
  switch(e)
  {
  case 1:
      *(contract+1) = 1;
      break;
  case 2:
      *(contract+1) = 2;
      break;
  case 3:
      *(contract+1) = 3;
      break;
  case 4:
      *(contract+1) = 4;
      break;
  case 5:
      *(contract+1) = 5;
      break;
  case 6:
      *(contract+1) = 6;
      break;

  }
  *(contract+2) = 0;
  //printf("contract : %d / %d / %d \n", *contract, *(contract +1), *(contract +2) );

  return;
}

//Give a potential score for eache color in order to help the bot to set the contract
void ColorScore(int *cards,int *result){
  int i;
  for (i = 0; i < 8; i++) {
    int c = *(cards +i);
    if(c%10 == 1){
      if(c>110 && c<120){
        *result = *result + 50;
      }else if(c>90 && c<100){
        *result = *result +30;
      }else if (c>10 && c<20){
        *result = *result +10;
      }else {
        *result = *result + 1;
      }
    }else if (c%10 ==2){
      if(c>110 && c<120){
        *(result+1) = *(result+1) + 50;
      }else if(c>90 && c<100){
        *(result+1) = *(result+1) +30;
      }else if (c>10 && c<20){
        *(result+1) = *(result+1) +10;
      }else {
        *(result+1) = *(result+1) + 1;
      }

    }else if (c%10 == 3){
      if(c>110 && c<120){
        *(result+2) = *(result+2) + 50;
      }else if(c>90 && c<100){
        *(result+2) = *(result+2) +30;
      }else if (c>10 && c<20){
        *(result+2) = *(result+2) +10;
      }else {
        *(result+2) = *(result+2) + 1;
      }

    }else if (c%10 == 4){
      if(c>110 && c<120){
        *(result+3) = *(result+3) + 50;
      }else if(c>90 && c<100){
        *(result+3) = *(result+3) +30;
      }else if (c>10 && c<20){
        *(result+3) = *(result+3) +10;
      }else {
        *(result+3) = *(result+3) + 1;
      }

    }
  }
}

//allow a bot to set a contract
int BotContract(int *result, int *contract){
  int a,b,i;
  a=0;
  for(i = 0; i < 4; i++){
    //printf("i: %d /res : %d \n",i,*(result+i));
    if (a < (*(result+i))) {
      a = *(result+i);
      b = i+1;
    }
  }
    //printf("End if a : %d / b : %d \n", a,b);
    if(a<62){
      return 0;
    }else if (a<70){
      if (*contract <80) {
        *contract = 80;
      }else {
        return 0;
      }

      //80
    }else if (a<81){
      if (*contract <90) {
        *contract = 90;
      }else {
        return 0;
      }
      //90
    }else if(a<83){
      if (*contract <100) {
        *contract = 100;
      }else {
        return 0;
      }
      //100
    }else if (a<86){
      if (*contract <120) {
        *contract = 120;
      }else {
        return 0;
      }
      //120
    }else if(a<91){
      if (*contract <100) {
        *contract = 100;
      }else {
        return 0;
      }
      //100
    }else if (a<93){
      if (*contract <130) {
        *contract = 130;
      }else {
        return 0;
      }
      //130
    }else if(a<95){
      if (*contract <140) {
        *contract = 140;
      }else {
        return 0;
      }
      //140
    }else if(a==95){
      if (*contract <500) {
        *contract = 500;
      }else {
        return 0;
      }
      //general
    }
    *(contract+1) = b;
    return 1;

}

//Start of trick
int trick(int *contract, int player, int *cards, int trump,int *Roundscore){
  int i;
  int firstPlayer = player;

  int PlayedCards[4] ={0};
    for ( i = 0; i < 4; i++) {
      prompt(cards,PlayedCards,contract,firstPlayer,Roundscore);
      if (player == 0) {
        playCard(cards,PlayedCards,trump,i);
      }else {
        botPlayCard((&cards[0]+player*8), PlayedCards, trump,i);
      }
      player=(player+1)%4;
      prompt(cards,PlayedCards,contract,firstPlayer,Roundscore);
      Sleep(2500);

    }
    int winner = trickWinner(PlayedCards, firstPlayer, trump);
    //printf("The player %d win the trick \n", winner);

    *(Roundscore+winner) = *(Roundscore+winner) + trickScore(PlayedCards,trump);
    //printf("trick score : %d / %d / %d / %d \n", *(Roundscore),*(Roundscore+1),*(Roundscore+2),*(Roundscore+3));

    return winner;

}

//allow the player to play one card
int playCard(int *cards, int *PlayedCards, int trump,int alreadyPlayed){
  showCards(cards);
  printf("1   2   3   4   5   6   7   8\n");
    printf("Wich one do you want to play ? (enter a number between 1 and 8) \n");
    int a = 0;
    int b =0; //check if the card is played
    char g;
    while (b !=1) {
      g = getchar();
      a = g - '0';
      if(a >= 1 && a <= 8){
        int test = isThisCardAllowed(PlayedCards,cards,trump,*(cards+(a-1)));
        if(test == 1){
          *(PlayedCards+alreadyPlayed) = *(cards+(a-1));
          *(cards+(a-1)) = 0;
          //printf("The south played ");
          numberToCard(*(PlayedCards+alreadyPlayed));
          printf("\n");
          b =1;
        }else if(test == 0){
          printf("You can't play this card !\n");
        }
      }else if(g != '\n'){
        printf("Please enter a number between 1 and 8 to play a card\n");
      }
    }
    return 1;

}

//allow a bot to play one card
int botPlayCard(int *cards, int *PlayedCards, int trump,int alreadyPlayed){


  if(alreadyPlayed == 0){
    int i =0;
    int a =0;
    for (i = 1; i < 8; i++) {
      if(wichOneIsBetter(*(cards+a),*(cards+i),trump) == 1){
        a = i;
      }
    }
    *(PlayedCards+alreadyPlayed) = *(cards+a);
    *(cards+a) = 0;
  //  printf("card : %d\n",*(PlayedCards+alreadyPlayed));
    //printf("The bot Played ");
    //numberToCard(*(PlayedCards+alreadyPlayed));
    //printf("\n");
  }else {
    int k;
    int b = -1;
    for ( k = 0; k < 8; k++) {
      b = isThisCardAllowed(PlayedCards,cards,trump,*(cards+k));
      if(b == 1){
        *(PlayedCards+alreadyPlayed) = *(cards+k);
        *(cards+k) = 0;
        //printf("card : %d\n",*(PlayedCards+alreadyPlayed));
        //printf("The bot Played ");
        //numberToCard(*(PlayedCards+alreadyPlayed));
        //printf("\n");
        return 1;
      }
    }
  }

}

//check if a card can be played
int isThisCardAllowed(int *Played,int *hand, int trump,int card){
  if(card == 0){
    return 0;
  }

  int color,a,n,i;
  a=-1;
 do {
   a++;
   n = *(Played+a);
 } while(n!=0);

  if(a == 0){
    return 1;
  }else
  { //We are no the first to play
    color = *(Played)%10; // first card of the trick
    if(color == card%10)//is the card of the asked color ?
    {
      return 1;//yes
    }else
    { //no
      for ( i = 0; i < 8; i++) { //did the player has others cards of the asked color ?
        if (*(hand+i)%10 == color) {
          return 0;//yes he has to play it
        }
      }
        //no
        if (card%10 == trump) { //his the card a trump ?
          return 1;
        }else {
          if(a == 2){ //if the player is third to play
            if(wichOneIsBetter(*(Played+(a-2)),*(Played+(a-1)),trump) == 0){// is the friend the master ?
              return 1;//yes
            }
          }else if(a == 3){//if the player is last to play
            if((wichOneIsBetter(*(Played+(a-2)),*(Played+(a-1)),trump) == 0) && (wichOneIsBetter(*(Played+(a-2)),*(Played+(a-3)),trump)))//same
            {
              return 1;//yes
            }
          } //the friend is not the master
            int k=0;
            for ( k = 0; k < 8; k++) { //did the player has a trump in his hand?
              if (*(hand+k)%10 == trump) {
                return 0;//yes, he has to play it
              }
            }
            return 1;//no, the player can play whatever he want

        }

    }
  }
}

//check if the first or the second card is better
int wichOneIsBetter(int card1, int card2,int trump){//return 0 if the first is better, 1 else
  //if cards are equal, the first put is the master

  if(card2==0){
    return 0;
  }




  if(trump == 5){
    if(card1>110 && card1<120){
      return 0;
    }else if(card2>110 && card2<120){
      return 1;
    }else if (card1>90 && card1<100){
      return 0;
    }else if(card2>90 && card2<100){
      return 1;
    }else if (card1>10 && card1<20){
      return 0;
    }else if(card2>10 && card2<20){
      return 1;
    }else if (card1>100 && card1<110){
      return 0;
    }else if(card2>100 && card2<110){
      return 1;
    }else if (card1>130 && card1<140){
      return 0;
    }else if(card2>130 && card2<140){
      return 1;
    }else if (card1>120 && card1<130){
      return 0;
    }else if(card2>120 && card2<130){
      return 1;
    }else if (card1>80 && card1<90){
      return 0;
    }else if(card2>80 && card2<90){
      return 1;
    }else if (card1>70 && card1<80){
      return 0;
    }else if(card2>70 && card2<80){
      return 1;
    }else {
      printf("Wich One Is Better Error 1\n");
      return -1;
    }

  }else if(trump ==6){
    if(card1>10 && card1<20){
      return 0;
    }else if(card2>10 && card2<20){
      return 1;
    }else if (card1>100 && card1<110){
      return 0;
    }else if(card2>100 && card2<110){
      return 1;
    }else if (card1>130 && card1<140){
      return 0;
    }else if(card2>130 && card2<140){
      return 1;
    }else if (card1>120 && card1<130){
      return 0;
    }else if(card2>120 && card2<130){
      return 1;
    }else if (card1>110 && card1<120){
      return 0;
    }else if(card2>110 && card2<120){
      return 1;
    }else if (card1>90 && card1<100){
      return 0;
    }else if(card2>90 && card2<100){
      return 1;
    }else if (card1>80 && card1<90){
      return 0;
    }else if(card2>80 && card2<90){
      return 1;
    }else if (card1>70 && card1<80){
      return 0;
    }else if(card2>70 && card2<80){
      return 1;
    }else {
      printf("Wich One Is Better Error 2\n");
      return -1;
    }

  }else if(card1%10 == trump){
      if(card2%10 != trump){
        return 0;
      }else {//atout
        if(card1>110 && card1<120){
          return 0;
        }else if(card2>110 && card2<120){
          return 1;
        }else if (card1>90 && card1<100){
          return 0;
        }else if(card2>90 && card2<100){
          return 1;
        }else if (card1>10 && card1<20){
          return 0;
        }else if(card2>10 && card2<20){
          return 1;
        }else if (card1>100 && card1<110){
          return 0;
        }else if(card2>100 && card2<110){
          return 1;
        }else if (card1>130 && card1<140){
          return 0;
        }else if(card2>130 && card2<140){
          return 1;
        }else if (card1>120 && card1<130){
          return 0;
        }else if(card2>120 && card2<130){
          return 1;
        }else if (card1>80 && card1<90){
          return 0;
        }else if(card2>80 && card2<90){
          return 1;
        }else if (card1>70 && card1<80){
          return 0;
        }else if(card2>70 && card2<80){
          return 1;
        }else {
          printf("Wich One Is Better Error 3\n");
          return -1;
        }
      }
    }else {
      if (card2%10 == trump) {
        return 1;
      }else {//non-atout
        if(card1>10 && card1<20){
          return 0;
        }else if(card2>10 && card2<20){
          return 1;
        }else if (card1>100 && card1<110){
          return 0;
        }else if(card2>100 && card2<110){
          return 1;
        }else if (card1>130 && card1<140){
          return 0;
        }else if(card2>130 && card2<140){
          return 1;
        }else if (card1>120 && card1<130){
          return 0;
        }else if(card2>120 && card2<130){
          return 1;
        }else if (card1>110 && card1<120){
          return 0;
        }else if(card2>110 && card2<120){
          return 1;
        }else if (card1>90 && card1<100){
          return 0;
        }else if(card2>90 && card2<100){
          return 1;
        }else if (card1>80 && card1<90){
          return 0;
        }else if(card2>80 && card2<90){
          return 1;
        }else if (card1>70 && card1<80){
          return 0;
        }else if(card2>70 && card2<80){
          return 1;
        }else {
          printf("Wich One Is Better Error 4\n");
          return -1;
        }
      }
    }

printf("Error 4\n");
return -1;

}

//return the # of the winner of the last trick
int trickWinner(int *cards, int firstPlayer, int trump){
  int a = 0;
  int i,test;
  for ( i = 1; i < 4; i++) {
    test = wichOneIsBetter(*(cards+a),*(cards+i),trump);
    if(test == 1){
      a = i;
    }
  }
  return ((firstPlayer+a)%4);
}

//return the score of the played cards in the trick
int trickScore(int *playedCards, int trump){
  int i;
  int result = 0;
  for ( i = 0; i < 4; i++) {
    int c = *(playedCards+i);
    if(trump == 5){
      if(c>110 && c<120){
        result = result + 14;
      }else if (c>90 && c<100){
        result = result + 9;
      }else if (c>10 && c<20){
        result = result + 6;
      }else if(c>100 && c<110){
        result = result + 5;
      }else if(c>130 && c<140){
        result = result + 3;
      }else if (c>120 && c<130){
        result = result + 1;
      }else if(c>70 && c<90){

      }else {
        printf("error 6\n");
      }

    }else if(trump == 6){
      if(c>110 && c<120){
        result = result + 2;
      }else if (c>90 && c<100){

      }else if (c>10 && c<20){
        result = result + 19;
      }else if(c>100 && c<110){
        result = result + 10;
      }else if(c>130 && c<140){
        result = result + 4;
      }else if (c>120 && c<130){
        result = result + 3;
      }else if(c>70 && c<90){

      }else {
        printf("error 7\n");
      }

    }else if(c%10 == trump){
      if(c>110 && c<120){
        result = result + 20;
      }else if (c>90 && c<100){
        result = result +14;
      }else if (c>10 && c<20){
        result = result + 11;
      }else if(c>100 && c<110){
        result = result + 10;
      }else if(c>130 && c<140){
        result = result + 4;
      }else if (c>120 && c<130){
        result = result + 3;
      }else if(c>70 && c<90){

      }else {
        printf("error 8\n");
      }
    }else {
      if(c>110 && c<120){
        result = result + 2;
      }else if (c>90 && c<100){

      }else if (c>10 && c<20){
        result = result + 11;
      }else if(c>100 && c<110){
        result = result + 10;
      }else if(c>130 && c<140){
        result = result + 4;
      }else if (c>120 && c<130){
        result = result + 3;
      }else if(c>70 && c<90){

      }else {
        printf("error 7\n");
      }
    }
  }
  //printf("trick result : %d\n",result);
  return result;

}

//compute the points of the round
int endOfRound(int *Roundscore, int *contract, int *score){
  int taker = *(contract+2);
  if(taker==0 || taker==2){
    if(*contract==500){
      if(*(Roundscore+taker) == 252){
        *score = *score + 500 + 252;
      }else {
        printf("The Team one is in !\n");
        *(score+1) = *(score+1) + 500 + 162;
      }
    }else if(*contract == 250){
      if((*(Roundscore+taker)+*(Roundscore+((taker+2)%4))) == 252){
        *score = *score + 250 + 252;
      }else {
        printf("The Team one is in !\n");
        *(score+1) = *(score+1) + 250 + 162;
      }
    }else {
      if((*(Roundscore+taker)+*(Roundscore+((taker+2)%4))) >= *contract){
        *score = *score + *contract + (*(Roundscore+taker)+*(Roundscore+((taker+2)%4)));
        *(score+1) = *(score+1) + (*(Roundscore+((taker+1)%4)))+*(Roundscore+((taker+3)%4));
      }else {
        printf("The Team one is in !\n");
        *(score+1) = *contract + 162;
      }
    }
  }else {
    if(*contract==500){
      if(*(Roundscore+taker) == 252){
        *(score+1) = *(score+1) + (500 + 252) * *(contract+3);//*2 si coinche
      }else {
        printf("The Team two is in !\n");
        *score = *score + (500 + 162) * *(contract+3);
      }
    }else {
        if((*(Roundscore+taker)+*(Roundscore+((taker+2)%4))) >= *contract){
          *(score+1) = *(score+1) + (*contract + (*(Roundscore+taker)+*(Roundscore+((taker+2)%4))))* *(contract+3);
          if(*(contract+3)!=2){
            *score = *score + (*(Roundscore+((taker+1)%4)))+*(Roundscore+((taker+3)%4));
          }

        }else {
          printf("The Team two is in !\n");
          *score = *contract + 162 * *(contract+3);
        }
      }

  }
}

//prompt the table with all informations player need
int prompt(int *cards, int *PlayedCards, int *contract, int firstPlayer, int *trickScore){
    int playerPlayedCard, WestPlayedCard, NorthPlayedCard, EastPlayerCard;
    int contractValue, trumpColor, taker;

    switch(firstPlayer)
    {
      case 0:
          playerPlayedCard = *PlayedCards;
          WestPlayedCard = *(PlayedCards + 1);
          NorthPlayedCard = *(PlayedCards + 2);
          EastPlayerCard = *(PlayedCards + 3);
          break;
      case 1:
          playerPlayedCard = *(PlayedCards + 3);
          WestPlayedCard = *PlayedCards;
          NorthPlayedCard = *(PlayedCards + 1);
          EastPlayerCard = *(PlayedCards + 2);
          break;
      case 2:
          playerPlayedCard = *(PlayedCards + 2);
          WestPlayedCard = *(PlayedCards + 3);
          NorthPlayedCard = *PlayedCards;
          EastPlayerCard = *(PlayedCards + 1);
          break;
      case 3:
          playerPlayedCard = *(PlayedCards + 1);
          WestPlayedCard = *(PlayedCards + 2);
          NorthPlayedCard = *(PlayedCards + 3);
          EastPlayerCard = *PlayedCards;
          break;
    }

    contractValue = *contract;
    trumpColor = *(contract + 1);
    taker = *(contract + 2);
     system("cls");
    printf("\n");
    printf("                 ########  ######## ##        #######  ######## ######## \n");
    printf("                 ##     ## ##       ##       ##     ##    ##    ##       \n");
    printf("                 ##     ## ##       ##       ##     ##    ##    ##       \n");
    printf("                 ########  ######   ##       ##     ##    ##    ######   \n");
    printf("                 ##     ## ##       ##       ##     ##    ##    ##       \n");
    printf("                 ##     ## ##       ##       ##     ##    ##    ##       \n");
    printf("                 ########  ######## ########  #######     ##    ######## \n\n\n");

    printf("Trump : ");
    numberToColor(trumpColor);
    printf("\n");
    printf("Contract : %d\n", contractValue);
    printf("Taker : ");
    numberToPlayer(taker);
    printf("\nCoinche : ");
    if(*(contract+3)==2){
      printf("Yes \n");
    }else {
      printf("No \n");
    }







    printf("\n\n\n                                         NORTH\n");
    printf("                                         (%d) \n", *(trickScore+2));
    printf("                   -----------------------------------------------\n");
    printf("                   |                      ");
    numberToCard(NorthPlayedCard);
    printf("                   |\n");
    printf("                   |                                             |\n");
    printf("                   |                                             |\n");
    printf("        WEST (%d)     ",*(trickScore+1));
    numberToCard(WestPlayedCard);
    printf("                                   ");
    numberToCard(EastPlayerCard);
    printf("   (%d)  EAST\n", *(trickScore+3));
    printf("                   |                                             |\n");
    printf("                   |                                             |\n");
    printf("                   |                      ");
    numberToCard(playerPlayedCard);
    printf("                   |\n");
    printf("                   -----------------------------------------------");
    printf("\n\n                                         (%d)", *trickScore);
    printf("\n                                        PLAYER\n\n\n");

return 0;
}
