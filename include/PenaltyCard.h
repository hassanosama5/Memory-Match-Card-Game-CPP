#ifndef PENALTYCARD_H
#define PENALTYCARD_H
#include "Card.h"

class PenaltyCard:public Card
{
    int penalty;
    public:
        PenaltyCard();
        PenaltyCard(bool fu,int p);
        int get_Penalty();
        void set_Penalty(int n);
        void display();
        bool operator==(const Card& other) const;
        virtual ~PenaltyCard();
};

#endif // PENALTYCARD_H
