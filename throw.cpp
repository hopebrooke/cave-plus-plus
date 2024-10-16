#include "throw.h"
#include "thing.h"

void Throw::fire(Cave& c, string userCommand)
{
    string s = tail(userCommand);
    string thing, dir;
    //find first word : thing
    int index = s.find(' ');
    if (index > 0)
    {
        thing = s.substr(0, s.find(' '));
        //find second word : direction
        dir = tail(s);
    }

    //set location for placement based on direction:
    Location *loc;
    if(dir == "north")
        loc = c.getMap()[c.getTom()->getX()][c.getTom()->getY()-1];
    else if (dir == "south")
        loc = c.getMap()[c.getTom()->getX()][c.getTom()->getY()+1];
    else if (dir == "west")
         loc = c.getMap()[c.getTom()->getX()-1][c.getTom()->getY()];
    else if (dir == "east")
        loc = c.getMap()[c.getTom()->getX()+1][c.getTom()->getY()];
    else
        loc = NULL;

    //ensure location is not null, and location is not blocked:
    if(loc != NULL && loc->isBlocking() == 0)
    {
        //check what thing is to be thrown:
        if (thing.compare("coin")==0)
            loc ->add(new Coin());
        else if (thing.compare("mushroom")==0)
            loc ->add(new Mushroom());
        else
            cerr << "I don't know how to throw a " << thing << endl;
    }
}
