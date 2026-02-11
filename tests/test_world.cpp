#include "world.h"
#include "state.h"
#include "test_framework.h"


void testWorldDimensions()
{
    World world(10, 10);
    check(world.getWidth() == 10 && world.getHeight() == 10, "world dimensions");
}


void testWorldBoundaries()
{
    World world(10, 10);
    State inside{ 5, 5 };
    State negX{ -1, 0 };
    State negY{ 0, -1 };
    State outX{ 10, 0 };
    State outY{ 0, 10 };

    bool passed = world.isFree(inside) &&
        !world.isFree(negX) &&
        !world.isFree(negY) &&
        !world.isFree(outX) &&
        !world.isFree(outY);

    check(passed, "world boundaries");
}


void testWorldSetAndGetWeight()
{
    World world(5, 5);
    State s{ 2, 2 };
    State out{ -1, 0 };
    bool passed = true;

    passed &= world.getWeight(s) == World::FREE;
    passed &= world.setWeight(s, 10);
    passed &= world.getWeight(s) == 10;
    passed &= !world.setWeight(out, 5); // out-of-bounds fails

    check(passed, "set and get weight");
}


void testWorldIsFree()
{
    World world(5, 5);
    State s{ 1, 1 };
    State blocked{ 2, 2 };

    world.setWeight(blocked, World::INF);

    bool passed = world.isFree(s) && !world.isFree(blocked);
    check(passed, "isFree with weights and blocked cells");
}


void testWorldClearGrid()
{
    World world(5, 5);
    State s1{ 0, 0 }, s2{ 4, 4 };
    int x = 0;
    int y = 0;
    bool passed = true;

    world.setWeight(s1, World::INF);
    world.setWeight(s2, 50);
    world.clearGrid();

    for (x = 0; x < world.getWidth(); ++x) 
    {
        for (y = 0; y < world.getHeight(); ++y) 
        {
            if (!world.isFree(State{ x, y }) || world.getWeight(State{ x, y }) != World::FREE) 
            {
                passed = false;
                break;
            }
        }

        if (!passed)
        {
            break;
        }
    }

    check(passed, "clearGrid resets all weights to FREE");
}


void runWorldTests()
{
    testHeader("WORLD TESTS");

    testWorldDimensions();
    testWorldBoundaries();
    testWorldSetAndGetWeight();
    testWorldIsFree();
    testWorldClearGrid();
}