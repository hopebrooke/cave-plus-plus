#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include <string>

#include "cave.h"
#include "rock.h"
#include "thing.h"
#include "location.h"
#include "move.h"
#include "place.h"
#include "throw.h"
#include "explode.h"

using namespace std;

Cave::Cave(int w, int h) : width(w), height(h) // width and height of the cave
{

    if ( width < 5 || height < 5)
        throw new logic_error("cave too small for tom.");

    map = new Location**[width]; //create a map

    for (int x = 0; x < width; x++)
    {
        Location** column = new Location*[height];
        map[x] = column;
        for (int y = 0; y < height; y++)
            column[y] = new Location();
    }

    // create some rocks
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            if ( x == 0 || y == 0 || x == width-1 || y == height-1 )
                 map[x][y] -> add( new Rock() );

    //create new Tom
    tom = new Tom();

    // add tom to the middle of the map
    tom -> setLocation( this, width/2,height/2);
}

Cave::Cave(Cave &c)
{
    //copy constructor for cave

    //first copy width and height variables:
    width = c.width;
    height = c.height;

    //then deep copy tom:
    tom = new Tom();
    *tom = *(c.tom);

    //make a new map:
    map = new Location**[width];

    //go through map creating new locations
    for (int x = 0; x < width; x++)
    {
        Location** column = new Location*[height];
        map[x] = column;
        for (int y = 0; y < height; y++)
        {
            //set Location l to the same location on the original map
            Location l = *c.map[x][y];

            //set column[y] equal to a copy of the original location
            //Location class has a copy constructor which deals with the deep copying of things
            column[y] = new Location(l);
        }
    }
}

Cave& Cave::operator=(const Cave& c)
{
    //assignment operator for cave:

    if(this != &c){ //make sure this and c are not the same

        //Delete orginal map:
        //location destructor deletes all things at each location
        //so all we need to do is delete the map the same way we made it
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y ++)
                delete map[x][y]; // delete each individual location

            delete map[x]; //delete array of locations
        }
        delete map; // delete array of arrays

        //change width and height:
        width = c.width;
        height = c.height;

        //make a new map:
        map = new Location**[width];
        for (int x = 0; x < width; x++)
        {
            Location** column = new Location*[height];
            map[x] = column;
            for (int y = 0; y < height; y++){
                //set Location l to the same location on the original map
                Location l = *c.map[x][y];
                //set column[y] equal to a copy of the original location
                //Location class has a copy constructor which deals with the deep copying of things
                column[y] = new Location(l);
            }
        }

        //make new tom:
        tom = new Tom();
        //redefine original tom to the copied tom:
        *tom = *(c.tom);
    }
    return *this; //return copied cave
}

Cave::~Cave()
{
    //location destructor deletes all things at each location
    //so all we need to do is delete the map the same way we made it
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y ++){
            delete map[x][y]; // delete each individual location
        }
        delete map[x]; //delete array of locations
    }
    delete map; // delete array of arrays
}

void Cave::command (string userCommand)
{
    if (Move().triggersOn(userCommand))
        Move().fire(*this, userCommand);
    else if (Place().triggersOn(userCommand))
        Place().fire(*this, userCommand);
    else if (Throw().triggersOn(userCommand))
        Throw().fire(*this, userCommand);
    else if (Explode().triggersOn(userCommand))
        Explode().fire(*this, userCommand);
    else
        cerr << "tom doesn't know how to "+userCommand << endl;;
}

void Cave::show()
{
    vector<Thing*>* thingsWithTom = map[tom -> getX()][tom -> getY()] -> getThings();

    for (int y = 0; y < height; y++)
    { // for all rows
        for (int x = 0; x < width; x++) // for all columns
            cout << map[x][y] -> show(); // output whatever we find there

        cout << "  "; // list the things at this location
        if (y <  (int) thingsWithTom -> size())
            cout << (*thingsWithTom)[y] -> getName();

        cout << endl;
    }

    cout << endl;
}
