#include "World.h"

/***************** CONSTRUCTOR *****************/

World::World(int w, int h) : width(w), height(h) {}


/***************** GET WIDTH ******************/

int World::getWidth() const
{
    return width;
}


/***************** GET HEIGHT *****************/

int World::getHeight() const 
{
    return height;
}


/******************* IS FREE ******************/

bool World::isFree(int x, int y) const 
{
    return (x >= 0 && x < width && y >= 0 && y < height);
}