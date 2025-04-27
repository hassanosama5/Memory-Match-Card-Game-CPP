#ifndef STANDARDCARD_H
#define STANDARDCARD_H
#include "Card.h"

class StandardCard:public Card
{
    public:
        StandardCard();
        StandardCard(bool fu,int n);
        virtual ~StandardCard();


};

#endif // STANDARDCARD_H
