#include <iostream>
#include "World.h"

/***************** CONSTRUCTOR *****************/

World::World(int w, int h) : width(w), height(h),grid(w, std::vector<int>(h, FREE)) {}


/****************** IS BOUNDS ******************/

bool World::inBounds(int x, int y) const
{
    return x >= 0 && x < width && y >= 0 && y < height;
}


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


/***************** GET WEIGHT *****************/

int World::getWeight(const State& s) const
{
    if (!inBounds(s.x, s.y))
    {
        return BLOCK;
    }

    return grid[s.y][s.x];
}


/***************** SET WEIGHT ****************/

bool World::setWeight(const State& s, int weight)
{
    if (!inBounds(s.x, s.y))
    {
        return false;
    }

    if (weight < 0)
    {
        weight = BLOCK;
    }

    grid[s.y][s.x] = weight;
    return true;
}


/******************* IS FREE ******************/

bool World::isFree(const State& s) const
{
    if (!inBounds(s.x, s.y))
    {
        return false;
    }

    return grid[s.y][s.x] != BLOCK;
}


/**************** CLEAR GRID *****************/

void World::clearGrid()
{
    for (auto& row : grid)
    {
        for (auto& cell : row)
        {
            cell = FREE;
        }
    }
}


/***************** PRINT GRID *****************/

void World::printGrid() const 
{
    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            if (grid[y][x] >= BLOCK)
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