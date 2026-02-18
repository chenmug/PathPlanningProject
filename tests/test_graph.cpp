#include "graph.h"
#include "world.h"
#include "state.h"
#include "test_framework.h"
#include <algorithm>
#include <cmath>
#include <vector>


// -------------------------
// DOUBLE COMPARISON HELPER
// -------------------------
void checkDouble(double actual, double expected, const char* testName)
{
    check(std::abs(actual - expected) < 1e-6, testName);
}


// -------------------------
// PATH COST - HELPER
// -------------------------
double computePathCost(const Graph& graph, const std::vector<State>& path)
{
    double total = 0.0;
    size_t i = 0;

    for (i = 1; i < path.size(); ++i)
    {
        total += graph.getCost(path[i - 1], path[i]);
    }

    return total;
}


// -------------------------
// CHECK NEIGHBORS - HELPER
// -------------------------
void checkNeighbors(const std::vector<State>& neighbors, const std::vector<State>& expected, const char* testName)
{
    bool pass = (neighbors.size() == expected.size());

    if (pass)
    {
        for (const auto& s : expected)
        {
            if (std::find(neighbors.begin(), neighbors.end(), s) == neighbors.end())
            {
                pass = false;
                break;
            }
        }
    }

    check(pass, testName);
}


// --------------------
// GRAPH NEIGHBORS
// --------------------
void testGraphNeighbors()
{
    World world(3, 3);
    Graph graph(&world);

    // Center cell
    State center{ 1,1 };
    auto neighbors = graph.getNeighbors(center);

    std::vector<State> expected =
    {
        {0,0},{0,1},{0,2},
        {1,0},      {1,2},
        {2,0},{2,1},{2,2}
    };

    checkNeighbors(neighbors, expected, "neighbors for center cell");

    // Corner cell
    State corner{ 0,0 };
    neighbors = graph.getNeighbors(corner);
    expected = { {0,1}, {1,0}, {1,1} };

    checkNeighbors(neighbors, expected, "neighbors for corner cell");

    // Edge cell
    State edge{ 0,1 };
    neighbors = graph.getNeighbors(edge);
    expected = { {0,0}, {0,2}, {1,0}, {1,1}, {1,2} };

    checkNeighbors(neighbors, expected, "neighbors for edge cell");
}


// ----------------------
// GRAPH WITH OBSTACLES
// ----------------------
void testGraphWithObstacles()
{
    World world(3, 3);
    Graph graph(&world);

    State s1{ 0,1 }, s2{ 1,0 }, s3{ 2,1 };

    world.setWeight(s1, World::BLOCK);
    world.setWeight(s2, World::BLOCK);
    world.setWeight(s3, World::BLOCK);

    State center{ 1,1 };
    auto neighbors = graph.getNeighbors(center);

    std::vector<State> expected = {{0,0}, {0,2}, {1,2}, {2,0}, {2,2}};

    checkNeighbors(neighbors, expected, "neighbors with obstacles");
}


// --------------------
// GRAPH COST
// --------------------
void testGraphCost()
{
    World world(4, 4);
    Graph graph(&world);

    State from{ 1,1 };
    State toCard{ 1,2 };
    State toDiag{ 2,2 };
    State blocked{ 0,1 };
    State nonNeighbor{ 3,0 };

    world.setWeight(from, 2);
    world.setWeight(toCard, 3);
    world.setWeight(toDiag, 4);
    world.setWeight(blocked, World::BLOCK);

    // Cardinal move
    double cost = graph.getCost(from, toCard);
    checkDouble(cost, 3.0, "getCost cardinal move");

    // Diagonal move
    cost = graph.getCost(from, toDiag);
    double expectedDiag = Graph::DIAGONAL_COST * world.getWeight(toDiag);
    checkDouble(cost, expectedDiag, "getCost diagonal move");

    // Blocked neighbor
    cost = graph.getCost(from, blocked);
    check(cost == World::BLOCK, "getCost blocked cell");

    // Non-neighbor
    cost = graph.getCost(from, nonNeighbor);
    check(cost == Graph::NOT_NEIGHBOR, "getCost non-neighbor cell");

    // Out-of-bounds
    State outX{ 4,1 };
    State outY{ 1,4 };

    check(graph.getCost(from, outX) == World::BLOCK, "getCost out-of-bounds X");
    check(graph.getCost(from, outY) == World::BLOCK, "getCost out-of-bounds Y");
}


// --------------------
// GRAPH PATH COST
// --------------------
void testGraphPathCost()
{
    World world(4, 4);
    Graph graph(&world);

    State s1{ 0,0 };
    State s2{ 1,0 };   // cardinal
    State s3{ 2,1 };   // diagonal from s2
    State s4{ 2,2 };   // cardinal

    std::vector<State> path = { s1, s2, s3, s4 };

    world.setWeight(s2, 2.0);
    world.setWeight(s3, 3.0);
    world.setWeight(s4, 4.0);

    double cost = computePathCost(graph, path);
    double expected = 2.0 + Graph::DIAGONAL_COST * 3.0 + 4.0;  

    checkDouble(cost, expected, "total path cost calculation");
}


// -------------------------
// GRAPH COST - BLOCK PATH
// -------------------------
void testGraphCostWithBlockPath()
{
    World world(2, 2);
    Graph graph(&world);

    State from{ 0,0 };
    State to{ 1,1 };
    State blocked1{ 1,1 }, blocked2{ 1,0 }, blocked3{ 0,1 };

    world.setWeight(from, 1.0);
    world.setWeight(to, 5.0);
    world.setWeight(blocked1, World::BLOCK);
    world.setWeight(blocked2, World::BLOCK);
    world.setWeight(blocked3, World::BLOCK);

    // Ensure movement is not possible due to blocked cells
    double cost = graph.getCost(from, to);
    check(cost == World::BLOCK, "getCost with block path");
}


// --------------------
// GRAPH IS GOAL
// --------------------
void testGraphIsGoal()
{
    Graph g(nullptr); // world not needed
    State s1{ 1,1 }, s2{ 1,1 }, s3{ 2,2 };

    check(g.isGoal(s1, s2), "isGoal true");
    check(!g.isGoal(s1, s3), "isGoal false");
}


// --------------------
// GRAPH IS VALID
// --------------------
void testGraphIsValid()
{
    World world(3, 3);
    Graph graph(&world);

    State freeCell{ 0,0 };
    State blocked{ 1,1 };
    State outX{ 3,0 };
    State outY{ 0,3 };

    world.setWeight(blocked, World::BLOCK);

    check(graph.isValid(freeCell), "isValid free cell");
    check(!graph.isValid(blocked), "isValid blocked cell");
    check(!graph.isValid(outX), "isValid out-of-bounds X");
    check(!graph.isValid(outY), "isValid out-of-bounds Y");
}


// ---------------------------
// DIAGONAL MOVEMENT TEST
// ---------------------------
void testGraphWithObstaclesDiagonal()
{
    World world(5, 5);
    Graph graph(&world);
    State s1{ 0,0 }, s2{ 1,1 };

    world.setWeight(s2, World::BLOCK);

    double cost = graph.getCost(s1, s2);
    check(cost == World::BLOCK, "Diagonal move blocked by obstacles");
}


// ---------------------------
// SMALL GRAPH TEST
// ---------------------------
void testSmallGraph()
{
    World world(1, 1);
    Graph graph(&world);
    State s{ 0, 0 };

    world.setWeight(s, World::BLOCK);

    check(graph.getNeighbors(s).empty(), "non neighbors in 1x1 graph");
    check(graph.getCost(s, s) == World::BLOCK, "cost in 1x1 graph is equal to block");
    check(!graph.isValid(s), "validity check for 1x1 - block");
}


// --------------------
// GRAPH RUN TESTS
// --------------------
void runGraphTests()
{
    testHeader("GRAPH TESTS");

    testGraphNeighbors();
    testGraphWithObstacles();
    testGraphCost();
    testGraphPathCost();
    testGraphCostWithBlockPath();
    testGraphIsGoal();
    testGraphIsValid();
    testGraphWithObstaclesDiagonal();
    testSmallGraph();
}