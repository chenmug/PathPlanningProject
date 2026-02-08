#include "planner.h"
#include "graph.h"
#include "world.h"
#include "state.h"
#include "test_framework.h"

void runPlannerTests()
{
    testHeader("PLANNER TESTS");

    World world(5, 5);
    Graph graph(&world);
    Planner planner(graph);

    State start{ 0, 0 };
    State goal{ 4, 4 };

    size_t i = 0;
    bool validPath = true;
    bool found = false;

    auto path = planner.plan(start, goal);

    // Basic path validity
    check(!path.empty(), "path is not empty");
    check(path.front() == start, "path starts at start state");
    check(path.back() == goal, "path ends at goal state");

    // Check that each step is a valid neighbor of the previous one
    for (i = 1; i < path.size(); ++i)
    {
        auto neighbors = graph.getNeighbors(path[i - 1]);
        found = false;

        for (const auto& n : neighbors)
        {
            if (n == path[i])
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            validPath = false;
            break;
        }
    }

    check(validPath, "each step is a valid neighbor");

    // Test unreachable goal
    State unreachableGoal{ -1, -1 };
    auto unreachablePath = planner.plan(start, unreachableGoal);
    check(unreachablePath.empty(), "unreachable goal returns empty path");
}