#include "world.h"
#include "test_framework.h"

void runWorldTests()
{
    testHeader("WORLD TESTS");

    World world(10, 10);

    // Size checks
    check(world.getWidth() == 10, "width is 10");
    check(world.getHeight() == 10, "height is 10");

    // Valid cell
    check(world.isFree(5, 5), "cell (5,5) is free");

    // Boundary checks
    check(!world.isFree(-1, 0), "cell (-1,0) is out of bounds");
    check(!world.isFree(0, -1), "cell (0,-1) is out of bounds");
    check(!world.isFree(10, 0), "cell (10,0) is out of bounds");
    check(!world.isFree(0, 10), "cell (0,10) is out of bounds");
}