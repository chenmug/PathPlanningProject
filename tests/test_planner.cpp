#include "planner.h"
#include "graph.h"
#include "world.h"
#include "state.h"
#include "test_framework.h"
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>


// -------------------------
// IS VALID PATH - HELPER
// -------------------------
bool isValidPath(const std::vector<State>& path, const Graph& graph)
{
    if (path.empty())
    {
        return true;
    }

    for (size_t i = 1; i < path.size(); ++i)
    {
        const auto& neighbors = graph.getNeighbors(path[i - 1]);
        bool found = false;

        for (const auto& n : neighbors)
        {
            if (n == path[i])
            {
                found = true;
                break;
            }
        }

        if (!found) return false;
    }

    return true;
}


// ------------------------------------
// PLANNER BASIC PATH (DEFAULT - BFS)
// ------------------------------------
void testPlannerBasicPath()
{
    World world(5, 5);
    Graph graph(&world);
    Planner planner(graph);
    State start{ 0, 0 }, goal{ 4, 4 };
    auto result = planner.plan(start, goal);

    check(result.success, "basic path: success == true");
    check(!result.path.empty(), "basic path: path not empty");
    check(result.path.front() == start, "basic path: starts at start");
    check(result.path.back() == goal, "basic path: ends at goal");
    check(isValidPath(result.path, graph), "basic path: valid neighbors");
    check(result.totalCost > 0, "basic path: cost positive");
    check(result.executionTime >= 0.0, "basic path: execution time non-negative");
    check(result.nodesExpanded > 0, "basic path: nodes expanded greater than 0");
}


// ------------------------
// PLANNER WITH OBSTACLES 
// ------------------------
void testPlannerWithObstacles()
{
    World world(5, 5);
    Graph graph(&world);
    Planner planner(graph);
    State start{ 0, 0 }, goal{ 4, 4 };

    world.setWeight({ 1, 0 }, World::BLOCK);
    world.setWeight({ 1, 1 }, World::BLOCK);
    world.setWeight({ 2, 1 }, World::BLOCK);
    world.setWeight({ 3, 2 }, World::BLOCK);

    auto result = planner.plan(start, goal);

    check(result.success, "with obstacles: success == true");
    check(result.path.front() == start, "with obstacles: starts correctly");
    check(result.path.back() == goal, "with obstacles: ends correctly");
    check(isValidPath(result.path, graph), "with obstacles: valid neighbors");
    check(result.totalCost > 0, "with obstacles: cost positive");
}


// ----------------------------
// PLANNER SINGLE FORCED PATH 
// ----------------------------
void testPlannerSinglePath()
{
    World world(3, 3);
    Graph graph(&world);
    Planner planner(graph);
    State start{ 1, 1 }, goal{ 2, 2 };

    world.setWeight({ 0, 1 }, World::BLOCK);
    world.setWeight({ 1, 0 }, World::BLOCK);
    world.setWeight({ 1, 2 }, World::BLOCK);
    world.setWeight({ 0, 0 }, World::BLOCK);
    world.setWeight({ 0, 2 }, World::BLOCK);

    auto result = planner.plan(start, goal);

    check(result.success, "single path: success == true");
    check(!result.path.empty(), "single path: path not empty");
    check(result.path.front() == start, "single path: starts correctly");
    check(result.path.back() == goal, "single path: ends correctly");
    check(isValidPath(result.path, graph), "single path: valid neighbors");
}


// --------------------------
// PLANNER UNREACHABLE GOAL 
// --------------------------
void testPlannerUnreachableGoal()
{
    World world(3, 3);
    Graph graph(&world);
    Planner planner(graph);
    State start{ 1, 1 }, goal{ 2, 2 };

    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            if (!(dx == 0 && dy == 0))
            {
                world.setWeight({ start.x + dx, start.y + dy }, World::BLOCK);
            }
        }
    }
    auto result = planner.plan(start, goal);

    check(!result.success, "unreachable: success == false");
    check(result.path.empty(), "unreachable: path is empty");
}


// ----------------------
// PLANNER START == GOAL
// ----------------------
void testPlannerStartEqualsGoal()
{
    World world(3, 3);
    Graph graph(&world);
    Planner planner(graph);
    State start{ 1, 1 };

    auto result = planner.plan(start, start);

    check(result.success, "start==goal: success == true");
    check(result.path.size() == 1, "start==goal: path size 1");
    checkDouble(result.totalCost, 0.0, "start==goal: cost == 0");
}


// ----------------------------------
// DIJKSTRA EQUAL A* - WEIGHTS = 1.0
// ----------------------------------
void testDijkstraEqualsAStarWithFixedWeights()
{
    World world(6, 6);
    Graph graph(&world);
    Planner planner(graph);
    State start{ 0, 0 }, goal{ 5, 5 };

    auto dijkstra = planner.plan(start, goal, SearchType::Dijkstra);
    auto astar = planner.plan(start, goal, SearchType::AStar);

    check(dijkstra.success && astar.success, "Dijkstra vs A* with fixed weights: both succeed");
    checkDouble(dijkstra.totalCost, astar.totalCost, "Dijkstra vs A* with fixed weights: same optimal cost");
}


// ----------------------------------------
// DIJKSTRA EQUAL A* - VARIABLE WEIGHTS
// ----------------------------------------
void testDijkstraEqualsAStarWithVariableWeights()
{
    World world(5, 5);
    Graph graph(&world);
    Planner planner(graph);
    State start{ 0,0 }, goal{ 4,4 };

    world.setWeight({ 1,1 }, 2.5);
    world.setWeight({ 2,2 }, 3.8);
    world.setWeight({ 3,3 }, 4.7);

    auto dijkstra = planner.plan(start, goal, SearchType::Dijkstra);
    auto astar = planner.plan(start, goal, SearchType::AStar);

    check(dijkstra.success && astar.success, "Dijkstra vs A* with variable weights: both succeed");
    checkDouble(astar.totalCost, dijkstra.totalCost, "Dijkstra vs A* with variable weights: same optimal cost");
}


// ---------------
// BLOCKED START
// ---------------
void testBlockedStart()
{
    World world(3, 3);
    Graph graph(&world);
    Planner planner(graph);
    State start{ 1,1 }, goal{ 2,2 };

    world.setWeight(start, World::BLOCK);
    auto result = planner.plan(start, goal);

    check(!result.success, "blocked start: success == false");
    check(result.path.empty(), "blocked start: path empty");
}


// ----------------
// BLOCKED GOAL
// ----------------
void testBlockedGoal()
{
    World world(3, 3);
    Graph graph(&world);
    Planner planner(graph);
    State start{ 0,0 }, goal{ 2,2 };

    world.setWeight(goal, World::BLOCK);
    auto result = planner.plan(start, goal);

    check(!result.success, "blocked goal: success == false");
    check(result.path.empty(), "blocked goal: path empty");
}


// ----------------------
// BFS - SHORTEST PATH
// ----------------------
void testBFSReturnsShortestPathLength()
{
    World world(5, 5);
    Graph graph(&world);
    Planner planner(graph);
    State start{ 0,0 }, goal{ 4,4 };
    int expectedSteps = 4;

    auto result = planner.plan(start, goal, SearchType::BFS);
    check(result.success, "BFS shortest path: success");

    checkDouble(result.totalCost, static_cast<double>(expectedSteps),
        "BFS shortest path: correct minimal number of steps");
    check(static_cast<int>(result.path.size()) == expectedSteps + 1,
        "BFS shortest path: path size matches expected steps");
}


// -----------------------------
// TEST NODES EXPANDED COUNTER
// -----------------------------
void testNodesExpanded()
{
    World world(5, 5);
    Graph graph(&world);
    Planner planner(graph);
    State start{ 0, 0 }, goal{ 4, 4 };

    auto resultBFS = planner.plan(start, goal, SearchType::BFS);
    check(resultBFS.nodesExpanded > 0, "BFS nodes expanded greater than 0");

    auto resultDijkstra = planner.plan(start, goal, SearchType::Dijkstra);
    check(resultDijkstra.nodesExpanded > 0, "Dijkstra nodes expanded greater than 0");

    auto resultAStar = planner.plan(start, goal, SearchType::AStar);
    check(resultAStar.nodesExpanded > 0, "A* nodes expanded greater than 0");
}


// ------------------------------
// FULLY BLOCKED WORLD
// ------------------------------
void testPlannerFullyBlockedWorld()
{
    World world(3, 3);
    Graph graph(&world);
    Planner planner(graph);
    State start{ 0, 0 }, goal{ 2, 2 };

    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            world.setWeight({ x, y }, World::BLOCK);
        }
    }
    auto result = planner.plan(start, goal, SearchType::Dijkstra);

    check(!result.success, "fully blocked: success == false");
    check(result.path.empty(), "fully blocked: path empty");
}


// --------------------
// PLANNER RUN TESTS
// --------------------
void runPlannerTests()
{
    testHeader("PLANNER TESTS");

    testPlannerBasicPath();
    testPlannerWithObstacles();
    testPlannerSinglePath();
    testPlannerUnreachableGoal();
    testPlannerStartEqualsGoal();
    testDijkstraEqualsAStarWithFixedWeights();
    testDijkstraEqualsAStarWithVariableWeights();
    testBlockedStart();
    testBlockedGoal();
    testBFSReturnsShortestPathLength();
    testNodesExpanded();
    testPlannerFullyBlockedWorld();
}