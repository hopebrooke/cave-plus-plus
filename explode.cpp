#include "explode.h"
#include "thing.h"
#include "bomb.h"


void Explode::fire(Cave& c, string userCommand)
{
    //get location of tom:
    int x = c.getTom()->getX();
    int y = c.getTom()->getY();
    Location* loc = c.getMap()[x][y];

    //get location north of tom:
    Location * locn = c.getMap()[x][y-1];
    //get location south of tom:
    Location * locs = c.getMap()[x][y+1];
    //get location east of tom:
    Location * loce = c.getMap()[x+1][y];
    //get location west of tom:
    Location * locw = c.getMap()[x-1][y];


    if(isBomb(loc))
    {   //check if location contains a bomb
        //call the recurisive lookBomb function if bomb at location:
        lookBomb(c, x, y);
    } else
    {   //if bomb explodes at toms location, it will explode any in adjacent positions
        //it is only necessary to check for bombs in adjacent positions if there are no bombs in tom's position
        if(isBomb(locn))
        {   //check if location north of Tom contains a bomb
            //call the recursive lookBomb function if bomb at location:
            lookBomb(c, x, y-1);
        }
        if(isBomb(locs))
        {   //check if location south of Tom contains a bomb
            //call the recursive lookBomb function if bomb at location:
            lookBomb(c, x, y+1);
        }
        if(isBomb(loce))
        {   //check if location east of Tom contains a bomb
            //call the recursive lookBomb function if bomb at location:
            lookBomb(c, x+1, y);
        }
        if(isBomb(locw))
        {   //check if location west of Tom contains a bomb
            //call the recursive lookBomb function if bomb at location:
            lookBomb(c, x-1, y);
        }
    }


    //go through bombsVisited vector and delete all things (except tom) at each location:
    //for each location get list of things:
    for(Location * l : bombsVisited)
    {
        vector<Thing*>* lThings = l->getThings();

        //check for tom at location:
        int hasTom = 0;
        for(Thing *ht : *lThings)
        {
            if(ht->getName()=="tom")
                //if location contains tom, set hasTom to 1
                hasTom = 1;
        }
        //loop through deleting all things at location until the amount of things at location is 1 if tom is there, or 0 if not
        while ((int)lThings->size()!=hasTom)
        {
            for(Thing * t : *lThings)
            {   //check if thing is Tom or not:
                if(dynamic_cast<Tom*>(t) == NULL)
                    l->remove(t); //if thing isn't tom, remove from location:
            }
        }
    }
}

void Explode::lookBomb(Cave &c, int x, int y)
{
    //recursive function that takes a location containing a bomb

    //first get location x, y in cave c:
    Location * loc = c.getMap()[x][y];

    //checks if location is in the visited vector:
    if(count(bombsVisited.begin(), bombsVisited.end(), loc)==0)
    {
        //if not in the visited vector, add it:
        bombsVisited.push_back(loc);

        //get locations adjacent to this one:
        //north:
        Location * locn = c.getMap()[x][y-1];
        //south:
        Location * locs = c.getMap()[x][y+1];
        //east:
        Location * loce = c.getMap()[x+1][y];
        //west:
        Location * locw = c.getMap()[x-1][y];

        //look for bombs in each adjacent location:
        //recursively call this function if yes:
        //first check that location isn't on the edge of the map:
        if(y != 0) //check there is a north location
        {
            if(isBomb(locn)) //check if location north contains a bomb, call recursive function if yes
                lookBomb(c, x, y-1);
        }
        if(y != c.getHeight()-1) //check there is a south location
        {
            if(isBomb(locs)) //check if location south contains a bomb, call recursive function if yes
               lookBomb(c, x, y+1);
        }
        if(x != c.getWidth()-1) //check there is an east location
        {
            if(isBomb(loce)) //check if location east contains a bomb, call recursive function if yes
               lookBomb(c, x+1, y);
        }
        if(x != 0) //check there is a west location
        {
            if(isBomb(locw)) //check if location west contains a bomb, call recursive function if yes
               lookBomb(c, x-1, y);
        }
    }
}

bool Explode::isBomb(Location *l)
{   //function takes a location and returns whether there is a bomb at that location
    bool isBomb = false;
    //get things at location:
    vector<Thing*>* lThings = l->getThings();
    //go through things at location:
    for(Thing * t : *lThings)
    {
        if(dynamic_cast<Bomb*>(t) != NULL)
            //if thing is bomb, set isBomb to true:
            isBomb= true;
    }
    return isBomb;
}
