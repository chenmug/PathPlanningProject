#ifndef PLANNER_H
#define PLANNER_H

#include "graph.h"
#include "state.h"
#include <vector>

/**
 * @class Planner
 * @brief Computes a path between two states using a graph-based search.
 *
 * The Planner class encapsulates path planning algorithms over a given
 * state-space graph. It is responsible for finding a valid path from a
 * start state to a goal state, if such a path exists.
 *
 * The Planner does not perform decision-making or simulation. it only
 * computes paths based on the graph connectivity.
 */
class Planner
{
private:
	const Graph& graph; // The graph that represent the world

public:

	/**
	 * @brief Constructs a Planner using the given graph.
	 *
	 * The Planner does not take ownership of the graph and assumes that
	 * the graph remains valid for the lifetime of the Planner.
	 *
	 * @param graph Reference to the state-space graph
	 */
	Planner(const Graph& graph);


	/**
	 * @brief Plans a path from a start state to a goal state.
	 *
	 * This function searches the state-space graph for a valid path from
	 * the given start state to the goal state.
	 *
	 * @param start The starting state
	 * @param goal  The goal state
	 * @return A vector of states representing the path from start to goal if exists,
	 *         otherwise the returned vector is empty.
	 */
	std::vector<State> plan(const State& start, const State& goal);
};

#endif // PLANNER_H