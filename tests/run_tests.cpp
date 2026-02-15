#include "test_state.cpp"
#include "test_world.cpp"
#include "test_graph.cpp"
#include "test_planner.cpp"
#include "test_framework.h"

int main()
{
    runStateTests();
    runWorldTests();
    runGraphTests();
    runPlannerTests();

    printSummary();

    return 0;
}