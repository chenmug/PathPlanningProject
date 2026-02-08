#ifndef GRAPH_H
#define GRAPH_H

#include "state.h"
#include "world.h"
#include <vector>

/**
 * @class Graph
 * @brief Represents the state-space graph of the world.
 *
 * The Graph class defines which states are reachable from a given state
 * based on the world's constraints.
 * It provides neighborhood and connectivity information, but does not
 * perform planning, goal selection, or decision-making.
 */
class Graph
{
private:
	/**
	* @brief Pointer to the world representation.
	*
	* The Graph uses this pointer to query world constraints
	* such as boundaries and obstacle information.
	* The Graph does not own the World object.
	*/
	const World* world;

public:
	/**
	 * @brief Constructs a graph using the given world.
	 *
	 * @param world Pointer to the world representation
	 */
	Graph(const World* world);


	/**
	 * @brief Returns all valid neighboring states of a given state.
	 *
	 * @param state Current state
	 * @return Vector of reachable neighboring states
	 */
	std::vector<State> getNeighbors(const State& state) const;

	// TODO:
	// Add isValid(State), getCost(State, State), isGoal(State)
};

#endif // GRAPH_H