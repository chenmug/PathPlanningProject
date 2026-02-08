#include "state.h"
#include "test_framework.h"
#include <unordered_set>

void runStateTests()
{
    testHeader("STATE TESTS");

    // Equality and inequality operators
    State s1{ 3, 5 };
    State s2{ 3, 5 };
    State s3{ 4, 5 };

    check(s1 == s2, "operator== identifies equal states");
    check(s1 != s3, "operator!= identifies different states");

    // Hash behavior in unordered_set
    std::unordered_set<State> stateSet;
    stateSet.insert(s1);

    check(stateSet.find(s2) != stateSet.end(),
        "unordered_set finds equivalent state using hash");

    check(stateSet.find(s3) == stateSet.end(),
        "unordered_set does not confuse different states");
}