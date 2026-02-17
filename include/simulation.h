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
 * - Show stats (steps, cost, success)
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
     * @param obstaclePercentage Percentage of blocked cells
     */
    void generateRandomObstacles(int obstaclePercentage, SearchType type);


    /**
     * @brief Prints the current grid to the console.
     *        Shows agent position, goal, obstacles, and path.
     * 
     * @param agentPos Current position of the agent
     * @param path Optional path to highlight (can show arrows or asterisks)
     */
    void displayGrid(const State& agentPos, const std::vector<State>& path, SearchType type, int step, int points) const;

public:
    /**
     * @brief Constructs a simulation with given grid size and start/goal positions.
     */
    Simulation(int width, int height, const State& start, const State& goal);

    /**
     * @brief Runs a single simulation in the console.
     *        Allows selecting the algorithm, generates obstacles,
     *        computes the path, animates the agent, and prints stats.
     */
    void run(SearchType type);
};

#endif // SIMULATION_H