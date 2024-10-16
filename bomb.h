#ifndef BOMB_H
#define BOMB_H

#include "thing.h"

class Bomb : public Thing
{

    string getName()
    {
        return "bomb";
    }
    Thing* clone()
    {
        //return copy of Thing:
        return new Bomb();
    }
};

#endif // BOMB_H
