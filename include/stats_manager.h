#ifndef STATS_MANAGER_H
#define STATS_MANAGER_H

#include "planner.h"
#include <string>

class StatsManager 
{
public:
    /**
     * @brief Prints the comparison results of multiple pathfinding algorithms.
     *
     * This function prints a table comparing the results of BFS, Dijkstra, and A* algorithms on the same grid.
     * It displays the cost, path length, expanded nodes, and execution time for each algorithm.
     *
     * Additionally, it checks if the A* algorithm is optimal by comparing its total cost with Dijkstra’s result. 
     * If both algorithms return the same total cost, A* is considered optimal.
     * 
     * @param bfsRes The results of the BFS algorithm.
     * @param dijRes The results of the Dijkstra algorithm.
     * @param aStarRes The results of the A* algorithm.
     */
    static void printComparisonResults(const PlanResults& bfsRes, const PlanResults& dijRes, const PlanResults& aStarRes);

    /**
     * @brief Prints a detailed correctness report for a given algorithm.
     *
     * Uses the correctness flags in PlanResults to display which verification checks passed:
     * monotonicityVerified, heuristicConsistent, and optimalGoalExtraction.
     * This helps visualize why an algorithm is correct and whether it returns an optimal path.
     *
     * @param r The PlanResults instance containing results and correctness flags.
     * @param name The name of the algorithm (e.g., "Dijkstra" or "A*").
     */
    void printCorrectnessReport(const PlanResults& r, const std::string& name);
};

#endif // STATS_MANAGER_H
