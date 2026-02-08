#ifndef STATE_H
#define STATE_H

#include <functional> // For std::hash

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

    /**
	 * @brief Compares two State objects for equality.
	 *
	 * Two states are considered equal if they represent the same position
	 * in the grid world, i.e., if both their x and y coordinates are equal.
	 *
	 * This operator is required for using State as a key in hash-based
	 * containers (std::unordered_map, std::unordered_set) and for
	 * determining whether two states refer to the same logical node in
	 * search and planning algorithms.
	 *
	 * @param other The state to compare with.
	 * @return true if both states represent the same position, false otherwise.
	 */
	bool operator==(const State& other) const
	{
		return (x == other.x && y == other.y);
	}
};


namespace std
{
	template<>
	struct hash<State>
	{
		/**
		 * @brief Computes a hash value for a State object.
		 *
		 * This function generates a hash value based on the state's
		 * coordinates (x, y) and is used by hash-based containers such as
		 * std::unordered_map and std::unordered_set.
		 *
		 * The hash function must satisfy the requirement that if two State
		 * objects are considered equal (according to operator==), then they
		 * must produce the same hash value.
		 *
		 * @param s The state to hash.
		 * @return A hash value representing the given state.
		 */
		size_t operator()(const State& s) const
		{
			return hash<int>()(s.x) ^ (hash<int>()(s.y) << 1);
		}
	};
}
#endif // STATE_H