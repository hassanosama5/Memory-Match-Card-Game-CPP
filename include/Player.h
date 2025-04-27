#ifndef PLAYER_H
#define PLAYER_H
#include "Game.h"

class Player
{
    int score;
    bool playerTurnI[20]; //[1,0,0,0,0,0,0,0]
    bool playerTurnEx[500]; //[1,1,1,1,1,1,1,1,1]
    string name;
    Game* myGame;
    public:
        Player();
        Player(string name);

        void set_Name(string n);
        string get_Name();
        int get_Score();
        void set_Score(int n);
        void set_Game(Game* game);
        bool get_playerTurnI(int i);
        bool get_playerTurnEx(int i);
        void addTurnAfterLastTurnI();

        void displayScore();
        void reveal(int i,int j);
        void hide(int i,int j);
        bool inTurnI(int i);
        void setTurnI(int i,bool b);
        bool inTurnEx(int i);
        void setTurnEx(int i,bool b);
        void resetPlayerTurnI();

        virtual ~Player();
};

#endif // PLAYER_H
