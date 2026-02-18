#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "world.h"
#include "state.h"
#include "planner.h"
#include <vector>
#include <string>

class DisplayManager 
{
public:
    /**
     * @brief Displays the grid, marking obstacles, path, agent, and goal.
     *
     * This function generates a grid with obstacles and path, then prints it to the screen.
     * It also marks the agent's position and the goal.
     * It displays the current algorithm, step, and points/cost information.
     *
     * @param world The World object representing the grid
     * @param agentPos The current position of the agent
     * @param path A vector containing the sequence of states representing the path
     * @param type The search algorithm used (BFS, Dijkstra, A*)
     * @param goal The goal position the agent is trying to reach
     * @param step The current step in the pathfinding process
     * @param points The accumulated cost or points associated with the path
     */
    static void displayGrid(const World& world, const State& agentPos, const std::vector<State>& path,
        SearchType type, const State& goal, int step, int points);

    /**
     * @brief Clears the screen.
     *
     * This function clears the console screen using ANSI escape codes to update the display in real-time.
     */
    static void clearScreen();
};

#endif // DISPLAY_MANAGER_H