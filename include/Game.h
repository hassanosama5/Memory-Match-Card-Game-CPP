#ifndef GAME_H
#define GAME_H
#include "Deck.h"
#include "Card.h"
#include "Player.h"

// Forward declaration of Player to break cyclic dependency
class Player;

class Game
{
    Player *p1, *p2;
    Deck* gameDeck;
    bool gameOver;
    public:
        Game();
        Player* getPlayer1();
        Player* getPlayer2();
        Deck* get_GameDeck();
        bool get_GameOver();
        void set_GameDeck(Card* c,int i); //Not sure of usage yet
        void initializeGame();
        void playTurn(Player* p, int turnI,int turnEx);
        void action(int i,int j,int x, int y, Player* p, int turnI,int turnEx);
        void gameDisplay();
        void flow();
        bool isOver();
        bool twoRemaining();
        int finale();
        virtual ~Game();
};

#endif // GAME_H
