#include "world.h"
#include "test_framework.h"

void testWorldDimensions()
{
    World world(10, 10);
    check(world.getWidth() == 10 && world.getHeight() == 10, "world dimensions");
}


void testWorldBoundaries()
{
    World world(10, 10);
    bool passed = (world.isFree(5, 5) &&
                  !world.isFree(-1, 0) &&
                  !world.isFree(0, -1) &&
                  !world.isFree(10, 0) &&
                  !world.isFree(0, 10));

    check(passed, "world boundaries");
}


void testWorldAddObstacle()
{
    World world(10, 10);
    State obstacle{ 3,3 };
    State out{ -1,0 };

    bool passed = true;
    passed &= world.addObstacle(obstacle);   // first add
    passed &= !world.addObstacle(obstacle);  // duplicate add fails
    passed &= !world.addObstacle(out);       // out-of-bounds fails
    passed &= !world.isFree(3, 3);           // cell is now blocked

    check(passed, "add obstacle");
}


void testWorldRemoveObstacle()
{
    World world(10, 10);
    State obstacle{ 3,3 };
    State missing{ 7,7 };

    world.addObstacle(obstacle);
    bool passed = true;
    passed &= world.removeObstacle(obstacle);   // remove exists
    passed &= world.isFree(3, 3);               // now free
    passed &= !world.removeObstacle(missing);   // remove non-existent fails

    check(passed, "remove obstacle");
}


void testWorldClearObstacles()
{
    World world(10, 10);
    State obs1{ 3,3 }, obs2{ 7,7 }, obs3{ 1,5 };
    int x = 0;
    int y = 0;

    world.addObstacle(obs1);
    world.addObstacle(obs2);
    world.addObstacle(obs3);
    world.clearObstacles();

    bool passed = true;
    for (y = 0; y < world.getHeight(); ++y)
    {
        for (x = 0; x < world.getWidth(); ++x)
        {
            if (!world.isFree(x, y))
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

    check(passed, "clear obstacles");
}


void runWorldTests()
{
    testHeader("WORLD TESTS");

    testWorldDimensions();
    testWorldBoundaries();
    testWorldAddObstacle();
    testWorldRemoveObstacle();
    testWorldClearObstacles();
}