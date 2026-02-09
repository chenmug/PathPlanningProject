#include "planner.h"
#include "graph.h"
#include "world.h"
#include "state.h"
#include "test_framework.h"


// Helper to check path validity
bool isValidPath(const std::vector<State>& path, const Graph& graph)
{
    if (path.empty()) return true;

    for (size_t i = 1; i < path.size(); ++i)
    {
        auto neighbors = graph.getNeighbors(path[i - 1]);
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


void testPlannerBasicPath()
{
    World world(5, 5);
    Graph graph(&world);
    Planner planner(graph);

    State start{ 0, 0 };
    State goal{ 4, 4 };

    auto path = planner.plan(start, goal);

    check(!path.empty(), "basic path: path is not empty");
    check(path.front() == start, "basic path: starts at start");
    check(path.back() == goal, "basic path: ends at goal");
    check(isValidPath(path, graph), "basic path: each step is valid neighbor");
}


void testPlannerWithObstacles()
{
    World world(5, 5);
    Graph graph(&world);
    Planner planner(graph);

    State start{ 0, 0 };
    State goal{ 4, 4 };

    world.addObstacle({ 1,0 });
    world.addObstacle({ 1,1 });
    world.addObstacle({ 2,1 });
    world.addObstacle({ 3,2 });

    auto path = planner.plan(start, goal);

    check(!path.empty(), "with obstacles: path is not empty");
    check(path.front() == start, "with obstacles: starts at start");
    check(path.back() == goal, "with obstacles: ends at goal");
    check(isValidPath(path, graph), "with obstacles: each step is valid neighbor");
}


void testPlannerSinglePath()
{
    World world(3, 3);
    Graph graph(&world);
    Planner planner(graph);

    State start{ 1, 1 };
    State goal{ 2, 2 };

    // Block almost all neighbors of start
    world.addObstacle({ 0,1 });
    world.addObstacle({ 1,0 });
    world.addObstacle({ 1,2 });

    auto path = planner.plan(start, goal);

    check(path.size() == 3, "single path: path length is 3");
    check(isValidPath(path, graph), "single path: each step is valid neighbor");
}


void testPlannerUnreachableGoal()
{
    World world(3, 3);
    Graph graph(&world);
    Planner planner(graph);

    State start{ 1,1 };
    State goal{ 2,2 };

    // Block all neighbors of start
    world.addObstacle({ 0,1 });
    world.addObstacle({ 1,0 });
    world.addObstacle({ 1,2 });
    world.addObstacle({ 2,1 });

    auto path = planner.plan(start, goal);

    check(path.empty(), "unreachable goal: path is empty");
}


void testPlannerStartEqualsGoal()
{
    World world(3, 3);
    Graph graph(&world);
    Planner planner(graph);

    State start{ 1,1 };
    State goal{ 1,1 };

    auto path = planner.plan(start, goal);

    check(path.size() == 1 && path.front() == start, "start equals goal: path contains only start");
}


void runPlannerTests()
{
    testHeader("PLANNER TESTS");

    testPlannerBasicPath();
    testPlannerWithObstacles();
    testPlannerSinglePath();
    testPlannerUnreachableGoal();
    testPlannerStartEqualsGoal();
}