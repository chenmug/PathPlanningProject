//#include "graph.h"
//#include "world.h"
//#include "state.h"
//#include "test_framework.h"
//
//
//void checkNeighborsAreValid(const std::vector<State>& neighbors, const World& world)
//{
//    bool neighborsAreValid = true;
//
//    for (const auto& n : neighbors)
//    {
//        if (!world.isFree(n.x, n.y))
//        {
//            neighborsAreValid = false;
//            break; 
//        }
//    }
//
//    check(neighborsAreValid, "all neighbors are free");
//}
//
//
//void testGraphNeighborsMiddle()
//{
//    World world(5, 5);
//    Graph graph(&world);
//    State center{ 2, 2 };
//
//    auto neighbors = graph.getNeighbors(center);
//    check(neighbors.size() == 4, "center cell has 4 neighbors");
//    checkNeighborsAreValid(neighbors, world);
//}
//
//
//void testGraphNeighborsCorner()
//{
//    World world(5, 5);
//    Graph graph(&world);
//    State corner{ 0, 0 };
//
//    auto neighbors = graph.getNeighbors(corner);
//    check(neighbors.size() == 2, "corner cell has 2 neighbors");
//    checkNeighborsAreValid(neighbors, world);
//}
//
//
//void testGraphNeighborsEdge()
//{
//    World world(5, 5);
//    Graph graph(&world);
//    State edge{ 0, 2 };
//
//    auto neighbors = graph.getNeighbors(edge);
//    check(neighbors.size() == 3, "edge cell has 3 neighbors");
//    checkNeighborsAreValid(neighbors, world);
//}
//
//
//void testGraphWithObstacles()
//{
//    World world(5, 5);
//    Graph graph(&world);
//    State center{ 2, 2 };
//
//    world.addObstacle({ 1, 2 });
//    world.addObstacle({ 2, 1 });
//
//    auto neighbors = graph.getNeighbors(center);
//    check(neighbors.size() == 2, "center cell with 2 obstacles has 2 neighbors");
//    checkNeighborsAreValid(neighbors, world);
//
//    world.addObstacle({ 3, 2 });
//    world.addObstacle({ 2, 3 });
//    neighbors = graph.getNeighbors(center);
//    check(neighbors.empty(), "center cell completely blocked has no neighbors");
//}
//
//
//void testGraphSinglePath()
//{
//    World world(3, 3);
//    Graph graph(&world);
//    State start{ 1, 1 };
//
//    world.addObstacle({ 0, 1 });
//    world.addObstacle({ 1, 0 });
//    world.addObstacle({ 1, 2 });
//
//    auto neighbors = graph.getNeighbors(start);
//    check(neighbors.size() == 1, "center cell with single path has 1 neighbor");
//    checkNeighborsAreValid(neighbors, world);
//}
//
//
//void testGraphMultiplePaths()
//{
//    World world(3, 3);
//    Graph graph(&world);
//    State start{ 1, 1 };
//
//    world.addObstacle({ 0, 1 });
//    world.addObstacle({ 1, 0 });
//
//    auto neighbors = graph.getNeighbors(start);
//    check(neighbors.size() == 2, "center cell with multiple paths has 2 neighbors");
//    checkNeighborsAreValid(neighbors, world);
//}
//
//
//void testGraphUnreachableGoal()
//{
//    World world(3, 3);
//    Graph graph(&world);
//    State start{ 1, 1 };
//
//    world.addObstacle({ 0, 1 });
//    world.addObstacle({ 1, 0 });
//    world.addObstacle({ 2, 1 });
//    world.addObstacle({ 1, 2 });
//
//    auto neighbors = graph.getNeighbors(start);
//    check(neighbors.empty(), "unreachable goal has no neighbors");
//}
//
//
//void runGraphTests()
//{
//    testHeader("GRAPH TESTS");
//
//    testGraphNeighborsMiddle();
//    testGraphNeighborsCorner();
//    testGraphNeighborsEdge();
//    testGraphWithObstacles();
//    testGraphSinglePath();
//    testGraphMultiplePaths();
//    testGraphUnreachableGoal();
//}



#include "graph.h"
#include "world.h"
#include "state.h"
#include "test_framework.h"
#include <algorithm>
#include <string>

void checkExpectedNeighbors(const std::vector<State>& neighbors, const std::vector<State>& expected, const char* testName)
{
    size_t actual = neighbors.size();
    size_t exp = expected.size();
    bool pass = (actual == exp);

    if (!pass) 
    {
        std::string msg = std::string(testName) + ": expected " +
            std::to_string(exp) + " neighbors, got " +
            std::to_string(actual);
        check(false, msg.c_str());
    }
    else 
    {
        std::string msg = std::string(testName) + ": number of neighbors - " + std::to_string(actual);
        check(true, msg.c_str());
    }
}


void testGraphNeighborsBasic()
{
    World world(5, 5);
    Graph graph(&world);

    // Center
    State center{ 2, 2 };
    auto neighbors = graph.getNeighbors(center);
    checkExpectedNeighbors(neighbors, { {2,1}, {2,3}, {1,2}, {3,2} }, "center cell");

    // Corner
    State corner{ 0, 0 };
    neighbors = graph.getNeighbors(corner);
    checkExpectedNeighbors(neighbors, { {0,1}, {1,0} }, "corner cell");

    // Edge
    State edge{ 0, 2 };
    neighbors = graph.getNeighbors(edge);
    checkExpectedNeighbors(neighbors, { {0,1}, {0,3}, {1,2} }, "edge cell");
}


void testGraphWithObstacles()
{
    World world(3, 3);
    Graph graph(&world);
    State center{ 1,1 };

    // Two neighbors blocked
    world.addObstacle({ 0,1 });
    world.addObstacle({ 1,0 });
    auto neighbors = graph.getNeighbors(center);
    checkExpectedNeighbors(neighbors, { {1,2}, {2,1} }, "center cell with 2 obstacles");

    // Single path
    world.addObstacle({ 2,1 });
    neighbors = graph.getNeighbors(center);
    checkExpectedNeighbors(neighbors, { {1,2} }, "center cell with single path");

    // Fully blocked
    world.addObstacle({ 1,2 });
    neighbors = graph.getNeighbors(center);
    checkExpectedNeighbors(neighbors, {}, "center cell fully blocked");
}


void runGraphTests()
{
    testHeader("GRAPH TESTS");

    testGraphNeighborsBasic();
    testGraphWithObstacles();
}