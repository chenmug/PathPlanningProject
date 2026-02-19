#include "stats_manager.h"
#include <iostream>
#include <iomanip>


// Static helper function declaration
static void printRow(const std::string& name, const PlanResults& r);


/****************** CLASS FUNCTION ******************/

/*********** PRINT COMPARISON RESULTS ************/

void StatsManager::printComparisonResults(const PlanResults& bfsRes, const PlanResults& dijRes, const PlanResults& aStarRes) 
{
    const double eps = 0.0001;

    std::cout << "\n==============================================================";
    std::cout << "\n                     ALGORITHM COMPARISON";
    std::cout << "\n==============================================================\n\n";

    // The header of the table
    std::cout << std::left
        << std::setw(15) << "Algorithm"
        << std::setw(10) << "Cost"
        << std::setw(10) << "Length"
        << std::setw(15) << "Expanded"
        << std::setw(10) << "Time(ms)"
        << "\n";

    std::cout << "-------------------------------------------------------------\n";

    printRow("BFS (steps)", bfsRes);
    printRow("Dijkstra", dijRes);

    // Check if A* is optimal by comparing it with Dijkstra
    if (aStarRes.success && dijRes.success && std::abs(aStarRes.totalCost - dijRes.totalCost) < eps) 
    {
        printRow("A* (optimal)", aStarRes);
    }
    else
    {
        printRow("A*", aStarRes);
    }

    std::cout << "\n";
    std::cout << "\n==============================================================\n\n";
    std::cout << "Note: Cost = steps for BFS, total weights for Dijkstra/A*\n";
    std::cout << "      All algorithms run on the same grid with identical obstacles\n\n";
}


/**************** HELPER FUNCTION ****************/

// Print row
static void printRow(const std::string& name, const PlanResults& r)
{
    std::cout << std::left
        << std::setw(15) << name
        << std::setw(10) << std::fixed << std::setprecision(2) << r.totalCost
        << std::setw(10) << r.path.size()
        << std::setw(15) << r.nodesExpanded
        << std::setw(10) << std::setprecision(3) << r.executionTime
        << "\n";
}