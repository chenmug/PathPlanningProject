#include "graph.h"
#include "world.h"
#include "state.h"
#include "test_framework.h"
#include <algorithm>
#include <string>

#define DIAGONAL_COST 1.4142


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


void testGraphNeighbors()
{
    World world(3, 3);
    Graph graph(&world);

    State center{ 1,1 };
    auto neighbors = graph.getNeighbors(center);

    // All 8 neighbors should exist in an empty grid
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
}


void testGraphWithObstacles()
{
    World world(3, 3);
    Graph graph(&world);
    State s1{ 0, 1 }, s2{ 1, 0 }, s3{ 2, 1 };

    // Add obstacles around center
    world.setWeight(s1, World::INF);
    world.setWeight(s2, World::INF);
    world.setWeight(s3, World::INF);

    State center{ 1,1 };
    auto neighbors = graph.getNeighbors(center);

    // Only unblocked neighbors remain
    std::vector<State> expected = { {0,0}, {0,2}, {1,2}, {2,0}, {2,2} };
    checkNeighbors(neighbors, expected, "neighbors with obstacles");
}


void testGraphCost()
{
    World world(3, 3);
    Graph graph(&world);
    State s1{ 1, 1 }, s2{ 1, 2 };

    // Set weights
    world.setWeight(s1, 2);  // center
    world.setWeight(s2, 3);  // neighbor

    State from{ 1,1 };
    State to{ 1,2 }; // cardinal move
    int cost = graph.getCost(from, to);
    check(cost == 3, "getCost cardinal move");

    State diag{ 2,2 };
    cost = graph.getCost(from, diag);
    int expectedDiag = int(DIAGONAL_COST * world.getWeight(diag));
    check(cost == expectedDiag, "getCost diagonal move");

    State blocked{ 0,1 };
    world.setWeight(blocked, World::INF);
    cost = graph.getCost(from, blocked);
    check(cost == World::INF, "getCost blocked cell");
}


void testGraphIsGoal()
{
    Graph g(nullptr); // world not needed
    State s1{ 1,1 }, s2{ 1,1 }, s3{ 2,2 };

    check(g.isGoal(s1, s2), "isGoal true");
    check(!g.isGoal(s1, s3), "isGoal false");
}


void runGraphTests()
{
    testHeader("GRAPH TESTS");

    testGraphNeighbors();
    testGraphWithObstacles();
    testGraphCost();
    testGraphIsGoal();
}