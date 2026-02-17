#include "world.h"
#include "state.h"
#include "test_framework.h"

// --------------------
// WORLD DIMENSIONS
// --------------------
void testWorldDimensions()
{
    World world(10, 15);
    check(world.getWidth() == 10 && world.getHeight() == 15, "world dimensions");
}


// --------------------
// WORLD BOUNDARIES
// --------------------
void testWorldBoundaries()
{
    World world(5, 5);
    State inside{ 0, 0 };
    State inside2{ 4, 4 };

    // out boundaries
    State negX{ -1, 0 };
    State negY{ 0, -1 };
    State outX{ 5, 0 };
    State outY{ 0, 5 };

    bool passed = world.isFree(inside) &&
        world.isFree(inside2) &&
        !world.isFree(negX) &&
        !world.isFree(negY) &&
        !world.isFree(outX) &&
        !world.isFree(outY);

    check(passed, "world boundaries including corners");
}


// --------------------
// WORLD SET/GET
// --------------------
void testWorldSetAndGetWeight()
{
    World world(5, 5);
    State s{ 2, 2 };
    State out{ -1, 0 };
    bool passed = true;

    passed &= world.getWeight(s) == World::FREE;
    passed &= world.setWeight(s, 10);
    passed &= world.getWeight(s) == 10;

    // change weight - out of boundary cell
    passed &= !world.setWeight(out, 5);
    passed &= world.getWeight(out) == World::BLOCK;

    // change weight to 0
    passed &= world.setWeight(s, 0);
    passed &= world.getWeight(s) == 0;

    // change weight to BLOCK
    passed &= world.setWeight(s, World::BLOCK);
    passed &= world.getWeight(s) == World::BLOCK;

    check(passed, "set and get weight including BLOCK, 0 and out of boundary cells");
}


// ---------------------
// MULTIPLE BLOCK CELLS
// ---------------------
void testWorldMultipleBlockedCells()
{
    World world(3, 3);
    State s1{ 0,0 }, s2{ 1,1 }, s3{ 2,2 };

    world.setWeight(s1, World::BLOCK);
    world.setWeight(s2, World::BLOCK);

    bool passed = !world.isFree(s1) && !world.isFree(s2) && world.isFree(s3);
    check(passed, "multiple blocked cells");
}


// --------------------
// CLEAR GRID
// --------------------
void testWorldClearGrid()
{
    World world(4, 4);
    State s1{ 0,0 }, s2{ 3,3 }, s3{ -1,-1 };
    bool passed = true;

    world.setWeight(s1, World::BLOCK);
    world.setWeight(s2, 50);
    world.clearGrid();

    for (int y = 0; y < world.getHeight(); ++y)
    {
        for (int x = 0; x < world.getWidth(); ++x)
        {
            s3.x = x;
            s3.y = y;

            if (!world.isFree(s3) || world.getWeight(s3) != World::FREE)
            {
                passed = false;
                break;
            }
        }
        if (!passed) break;
    }

    check(passed, "clearGrid resets all cells to FREE");
}


// --------------------
// NEGATIVE WEIGHT
// --------------------
void testWorldNegativeWeightProtection()
{
    World world(3, 3);
    State s{ 1,1 };
    bool passed = true;

    world.setWeight(s, -5);
    passed = world.getWeight(s) == World::BLOCK; 
    check(passed, "negative weights automatically treated as BLOCK");
}


// --------------------
// RUN WORLD TESTS
// --------------------
void runWorldTests()
{
    testHeader("WORLD TESTS");

    testWorldDimensions();
    testWorldBoundaries();
    testWorldSetAndGetWeight();
    testWorldMultipleBlockedCells();
    testWorldClearGrid();
    testWorldNegativeWeightProtection();
}