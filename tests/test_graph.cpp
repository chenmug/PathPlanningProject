#include "graph.h"
#include "world.h"
#include "state.h"
#include "test_framework.h"

void runGraphTests()
{
    testHeader("GRAPH TESTS");

    World world(5, 5);
    Graph graph(&world);

    // Test neighbors in the middle of the grid
    State center{ 2, 2 };
    auto neighbors = graph.getNeighbors(center);
    check(neighbors.size() == 4, "center cell has 4 neighbors");

    // Test neighbors in a corner
    State corner{ 0, 0 };
    auto cornerNeighbors = graph.getNeighbors(corner);
    check(cornerNeighbors.size() == 2, "corner cell has 2 neighbors");

    // Test neighbors on an edge
    State edge{ 0, 2 };
    auto edgeNeighbors = graph.getNeighbors(edge);
    check(edgeNeighbors.size() == 3, "edge cell has 3 neighbors");
}