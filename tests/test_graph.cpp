#include "graph.h"
#include "world.h"
#include "state.h"
#include "test_framework.h"
#include <algorithm>
#include <string>
#include <cmath>


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

    std::vector<State> expected = { {0,0}, {0,2}, {1,2}, {2,0}, {2,2} };
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
    int cost = graph.getCost(from, toCard);
    check(cost == 3, "getCost cardinal move");

    // Diagonal move
    cost = graph.getCost(from, toDiag);
    int expectedDiag = int(graph.DIAGONAL_COST * world.getWeight(toDiag));
    check(cost == expectedDiag, "getCost diagonal move");

    // Blocked neighbor
    cost = graph.getCost(from, blocked);
    check(cost == World::BLOCK, "getCost blocked cell");

    // Non-neighbor
    cost = graph.getCost(from, nonNeighbor);
    check(cost == graph.NOT_NEIGHBOR, "getCost non-neighbor cell");

    // Out-of-bounds
    State outX{ 4,1 };
    State outY{ 1,4 };
    check(graph.getCost(from, outX) == -1, "getCost out-of-bounds X");
    check(graph.getCost(from, outY) == -1, "getCost out-of-bounds Y");
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


// --------------------
// GRAPH RUN TESTS
// --------------------
void runGraphTests()
{
    testHeader("GRAPH TESTS");

    testGraphNeighbors();
    testGraphWithObstacles();
    testGraphCost();
    testGraphIsGoal();
    testGraphIsValid();
}