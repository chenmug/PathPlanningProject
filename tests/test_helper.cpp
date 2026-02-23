#include "test_helper.h"
#include "test_framework.h"

// -------------------------
// DOUBLE COMPARISON HELPER
// -------------------------
void checkDouble(double actual, double expected, const char* testName)
{
    check(std::abs(actual - expected) < 1e-6, testName);
}