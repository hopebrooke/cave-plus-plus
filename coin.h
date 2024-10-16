#ifndef COIN_H
#define COIN_H

#include "thing.h"

// a small coin that can be picked up.
class Coin : public Thing
{
    string getName()
    {
        return "coin";
    }
    Thing* clone()
    {
        //return copy of Thing:
        return new Coin();
    }
};

#endif // COIN_H
