#ifndef GRAPH_H
#define GRAPH_H

#include "state.h"
#include "world.h"
#include <vector>

/**
 * @class Graph
 * @brief Represents the state-space graph of the world with weighted movement.
 *
 * The Graph class defines which states are reachable from a given state
 * based on the world's constraints. It provides neighborhood, connectivity,
 * and movement cost information.
 */
class Graph
{
private:
    const World* world;  // Pointer to the world; Graph does not own it.
    static const std::vector<State> moves; // Possible moves including diagonals.

public:
    static constexpr double DIAGONAL_COST = 1.4142; // Represents the cost multiplier for diagonal movement
    static constexpr int NOT_NEIGHBOR = -2;         // Indicates that 'to' is not a valid neighbor

    /**
     * @brief Constructs a graph using the given world.
     * 
     * @param world Pointer to the world
     */
    Graph(const World* world);

    /**
     * @brief Returns all valid neighboring states of a given state.
     *
     * This function generates all neighboring states (8 directions), and checks if each one is valid
     * (i.e., not blocked and within grid boundaries).
     *
     * @param state The current state
     * @return A vector of reachable neighboring states
     */
    std::vector<State> getNeighbors(const State& state) const;

    /**
     * @brief Returns the movement cost between two adjacent states.
     *
     * This function calculates the cost of moving between two states (from 'from' to 'to').
     * - Returns `BLOCK` if 'to' is blocked or out-of-bounds.
     * - Returns `NOT_NEIGHBOR` if 'to' is not a valid neighbor of 'from'.
     * - Returns `DIAGONAL_COST * weight` for diagonal moves.
     * - Returns `weight` for cardinal (horizontal or vertical) moves.
     *
     * @param from Starting state
     * @param to Ending state
     * @return The movement cost between the two states
     */
    double getCost(const State& from, const State& to) const;

    /**
     * @brief Checks if a state is valid (inside world and not blocked).
     * 
     * @param state State to check
     * 
     * @return true if valid, false otherwise
     */
    bool isValid(const State& state) const;

    /**
     * @brief Checks if a state is the goal.
     * 
     * @param state State to check
     * @param goal Goal state
     * 
     * @return true if state equals goal
     */
    bool isGoal(const State& state, const State& goal) const;
};

#endif // GRAPH_H