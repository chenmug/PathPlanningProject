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

    /**
     * @brief Possible moves including diagonals.
     */
    static const std::vector<State> moves;

public:
    static constexpr double DIAGONAL_COST = 1.4142; // diagonal move multiplier
    static const int NOT_NEIGHBOR = -2; // non-neighbor state

    /**
     * @brief Constructs a graph using the given world.
     * 
     * @param world Pointer to the world
     */
    Graph(const World* world);

    /**
     * @brief Returns all valid neighboring states of a given state.
     * 
     * @param state Current state
     * 
     * @return Vector of reachable neighboring states
     */
    std::vector<State> getNeighbors(const State& state) const;

    /**
     * @brief Returns the movement cost between two adjacent states.
     * 
     * @param from Starting state
     * @param to Ending state
     * 
     * @return 
     * - Returns `BLOCK` if 'to' is blocked or out-of-bounds.
     * - Returns `NOT_NEIGHBOR` if 'to' is not a neighbor of 'from'.
     * - Returns `DIAGONAL_COST * weight` if moving diagonally.
     * - Returns `weight` if moving cardinally.
     */
    int getCost(const State& from, const State& to) const;

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