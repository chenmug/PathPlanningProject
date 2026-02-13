#include "state.h"
#include "test_framework.h"
#include <unordered_set>
#include <climits> // For INT_MAX, INT_MIN

void runStateTests()
{
    testHeader("STATE TESTS");

    State s1{ 3, 5 };
    State s2{ 3, 5 };
    State s3{ 4, 5 };

    // Reflexive
    check(s1 == s1, "operator== identifies equal states");
    // Symmetric
    check(s1 == s2 && s2 == s1, "Equality is symmetric");
    // Inequality
    check(s1 != s3, "operator!= identifies different states");

    // --------------------
    // HASH BEHAVIOR
    // --------------------
    std::hash<State> hasher;
    check(hasher(s1) == hasher(s2), "Equal states produce identical hash values");

    // --------------------
    // DEFAULT CONSTRUCTOR
    // --------------------
    State sDefault;
    check(sDefault.x == 0 && sDefault.y == 0, "Default constructor sets coordinates correctly");

    // --------------------
    // UNORDERED SET
    // --------------------
    std::unordered_set<State> stateSet;
    stateSet.insert(s1);

    check(stateSet.find(s2) != stateSet.end(),
        "unordered_set finds equivalent state using hash");

    check(stateSet.find(s3) == stateSet.end(),
        "unordered_set does not confuse different states");

    stateSet.insert(s3);
    check(stateSet.size() == 2, "unordered_set stores both distinct states");

    // --------------------
    // EXTREME VALUES
    // --------------------
    State sMax{ INT_MAX, INT_MAX };
    State sMin{ INT_MIN, INT_MIN };
    check(sMax != sMin, "Extreme states are distinct");
    check(hasher(sMax) != hasher(sMin), "Extreme states produce different hashes");
}