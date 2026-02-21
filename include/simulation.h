#ifndef SIMULATION_H
#define SIMULATION_H

#include "world.h"
#include "graph.h"
#include "planner.h"
#include <vector>

/**
 * @class Simulation
 * @brief Handles console-based simulation of an agent moving from start to goal.
 *
 * Responsibilities:
 * - Generate a random world with obstacles
 * - Allow user to select algorithm (BFS, Dijkstra, A*)
 * - Run the planner and get the path
 * - Animate the agent moving along the path
 * - Display grid and path in console
 * - Show stats (steps, cost, success, time)
 */
class Simulation
{
private:
    int width;
    int height;
    World world;
    Graph graph;
    Planner planner;
    State start;
    State goal;

    /**
     * @brief Fills the world with random obstacles.
     * 
     * @param obstaclePercentage How many cells to block as obstacles (0 = none, 100 = all)
     * @param type The search algorithm type (BFS, Dijkstra, or A*) used to decide weight assignment
     */
    void generateRandomObstacles(int obstaclePercentage, SearchType type);

    /**
     * @brief Animates the path found by the search algorithm using displayGrid function.
     *
     * This function visualizes the agent moving along the computed path step by step.
     *
     * @param results The PlanResults structure containing the computed path and metadata
     * @param type The type of algorithm that computed the path (BFS, Dijkstra, or A*)
     */
    void visualizePath(const PlanResults& results, SearchType type);

    /**
     * @brief Checks and prints the correctness of weighted search results.
     *
     * For Dijkstra and A*, this function prints a correctness report that verifies:
     * - Monotonic extraction of nodes (Dijkstra)
     * - Heuristic consistency (A*)
     * - Optimal goal extraction
     *
     * @param results The PlanResults structure containing the computed path and correctness flags
     * @param type The type of algorithm (Dijkstra or A*) being verified
     */
    void verifyCorrectness(const PlanResults& results, SearchType type);

public:
    /**
     * @brief Constructs a simulation with a given grid size and start/goal positions.
     *
     * @param width The width of the grid
     * @param height The height of the grid
     * @param start The starting position of the agent
     * @param goal The goal position the agent needs to reach
     */
    Simulation(int width, int height, const State& start, const State& goal);

    /**
     * @brief Runs a single simulation in the console.
     *        Allows the user to select the algorithm, computes the path
     *        animates the agent, and prints stats.
     *
     * @param type The search algorithm to use (BFS, Dijkstra, or A*)
     */
    void run(SearchType type);

    /**
     * @brief Compares the performance of different algorithms (BFS, Dijkstra, A*) on the same grid.
     *
     * This function executes each algorithm (BFS, Dijkstra, A*) on a randomly generated world and compares:
     * - The time taken to compute the path
     * - The number of nodes expanded during the search
     * - The computed path and its cost
     *
     * The goal is to provide insights into the efficiency and optimality of each algorithm in various scenarios.
     */
    void compareAlgorithms();
};

#endif // SIMULATION_H