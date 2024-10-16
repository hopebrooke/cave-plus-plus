#ifndef EXPLODE_H
#define EXPLODE_H

#include "coin.h"
#include "command.h"
#include "mushroom.h"
#include "bomb.h"
#include "rock.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Explode : public Command
{
public:
    Explode() : Command("explode") {};
    void fire(Cave& c, string userCommand);
    vector<Location*> bombsVisited; //locations visited containing a bomb
    void lookBomb(Cave &c, int x, int y); //recursive function for checking surrounding locations
    bool isBomb(Location* l); //function to check if a location contains a bomb
};
#endif // EXPLODE_H
