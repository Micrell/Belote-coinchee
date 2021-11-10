#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#endif // FONCTIONS_H_INCLUDED
int DistributeCards(int card_package[]);
void numberToCard(int card);
int startMenu();
void boardMenu();
int pseudoInitial();
int printScoreboard();
int writeEndScoreP();
char pseudo();
int stringToInt(int *string);
void printSB();

void howManyLine();


void clearBuffer();
int read(int *array, int length);


int Round(int dealer, int *pack, int *score);
void showCards(int *cards);
int setContract(int *contract);
void ColorScore(int *cards,int *result);
int BotContract(int *result, int *contract);
int trick(int *contract, int player, int *cards, int trump,int *Roundscore);
int playCard(int *cards, int *PlayedCards, int trump,int alreadyPlayed);
int botPlayCard(int *cards, int *PlayedCards, int trump,int alreadyPlayed);
int isThisCardAllowed(int *Played,int *hand, int trump,int card);
int wichOneIsBetter(int card1, int card2,int trump);
int trickScore(int *playedCards, int trump);
int endOfRound(int *Roundscore, int *contract, int *score);

int prompt(int *cards, int *PlayedCards, int *contract, int firstPlayer, int *trickScore);
void numberToPlayer(int number);
void numberToColor(int number);
