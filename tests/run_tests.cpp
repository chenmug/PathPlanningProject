#include "run_tests.h"
#include "test_framework.h"

void runStateTests();
void runWorldTests();
void runGraphTests();
void runPlannerTests();


void runAllTests()
{
    runStateTests();
    runWorldTests();
    runGraphTests();
    runPlannerTests();

    printSummary();
}