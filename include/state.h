#ifndef STATE_H
#define STATE_H

/**
 * @struct State
 * @brief Represents a discrete position in the grid world.
 *
 * The State struct stores the agent's current location in the world.
 * It contains only state variables and does not include any logic
 * related to movement, planning, or decision-making.
 *
 * This structure is typically used by planners and search algorithms
 * (e.g., BFS, A*, Dijkstra) to represent nodes in the state space.
 */
struct State
{
	int x;  // X-coordinate (column index)
	int y;  // Y-coordinate (row index)
};

// Add a comparison function later for planner

#endif // STATE_H