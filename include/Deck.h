#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include "StandardCard.h"
#include "BonusCard.h"
#include "PenaltyCard.h"

class Deck
{
    Card** cards;
    public:
        Deck();
        Card** getCards();
        void setCards(Card* c,int i);
        void shuffle();
        void displayGrid();
        void faceUpAll();
        void removeCard(int cor);
        virtual ~Deck();
};

#endif // DECK_H
