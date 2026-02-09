#include <iostream>
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
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        return false;
    }

    return obstacles.find(State{ x, y }) == obstacles.end();
}


/**************** ADD OBSTACLE ****************/

bool World::addObstacle(const State& obstacle)
{
    return obstacles.insert(obstacle).second;
}


/*************** REMOVE OBSTACLE **************/

bool World::removeObstacle(const State& obstacle)
{
    return obstacles.erase(obstacle) > 0;
}


/*************** CLEAR OBSTACLE ***************/

void World::clearObstacles()
{
    obstacles.clear();
}


/***************** PRINT WORLD ****************/

void World::printWorld() const
{
    int x = 0;
    int y = 0;

    for (y = 0; y < height; ++y)
    {
        for (x = 0; x < width; ++x)
        {
            if (obstacles.find(State{ x, y }) != obstacles.end())
            {
                std::cout << "# ";
            }
            else
            {
                std::cout << ". ";
            }
        }

        std::cout << '\n';
    }
}