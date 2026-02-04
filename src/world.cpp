#include "World.h"


World::World(int w, int h) : width(w), height(h) 
{
    
}


int World::getWidth() const 
{
    return width;
}


int World::getHeight() const 
{
    return height;
}


bool World::isFree(int x, int y) const 
{
    return true;
}