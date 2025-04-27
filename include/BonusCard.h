#ifndef BONUSCARD_H
#define BONUSCARD_H
#include "Card.h"

class BonusCard:public Card
{
    int bonus;
    public:
        BonusCard();
        BonusCard(bool fu,int b);
        int getBonus();
        void setBonus(int n);
        void display();
        bool operator==(const Card& other) const;
        virtual ~BonusCard();
};

#endif // BONUSCARD_H
