#ifndef PLANNER_H
#define PLANNER_H

#include "graph.h"
#include "state.h"
#include <vector>

/**
 * @enum SearchType
 * @brief Defines the search algorithm used by the Planner.
 *
 * Specifies which pathfinding strategy will be applied:
 * - BFS: Unweighted breadth-first search (ignores edge weights)
 * - Dijkstra: Weighted shortest path search (considers accumulated path cost)
 * - AStar: Heuristic-guided shortest path search (uses accumulated cost + heuristic)
 */
enum class SearchType
{
    BFS,
    Dijkstra,
    AStar
};

/**
 * @struct PlanResults
 * @brief Stores the result of a path planning execution.
 *
 * Contains the computed path (if found), an indication of success,
 * and the total path cost.
 *
 * If success is false:
 * - path will be empty
 * - totalCost may be set to 0 or INF (implementation-defined)
 */
struct PlanResults
{
    std::vector<State> path; // The computed path from start to goal
    bool success;            // Indicates whether a valid path was found
    int totalCost;           // Total accumulated cost of the path
};

/**
 * @class Planner
 * @brief Computes a path between two states using graph search algorithms.
 *
 * The Planner class encapsulates classical pathfinding algorithms
 * over a given state-space graph (e.g., BFS, Dijkstra, A*).
 *
 * It is responsible for computing a valid path from a start state
 * to a goal state, if such a path exists.
 *
 * The Planner does not modify the graph and does not perform
 * decision-making or simulation. It strictly performs path computation
 * based on graph connectivity and edge costs.
 */
class Planner
{
private:
    const Graph& graph; // The graph representing the world

    /**
     * @brief Estimates the cost from one state to another.
     *
     * Computes a Euclidean distance between state @p a and state @p b,
     * assuming movement in all 8 directions (including diagonals).
     *
     * This heuristic is admissible and consistent for A*, guaranteeing
     * optimal paths when used with uniform cost.
     *
     * @param a The current state
     * @param b The target state (goal)
     * 
     * @return An estimated cost between the two states
     */
    int heuristic(const State& a, const State& b) const;

    /**
     * @brief Executes Breadth-First Search (BFS).
     *
     * Performs an unweighted search over the graph, expanding states
     * in increasing order of depth from the start state.
     *
     * @param start The starting state
     * @param goal  The goal state
     * 
     * @return The computed path if found, otherwise an empty vector
     */
    std::vector<State> runBFS(const State& start, const State& goal) const;

    /**
     * @brief Executes a weighted shortest-path search.
     *
     * Shared implementation for Dijkstra and A* algorithms.
     *
     * - Dijkstra: expands states based on accumulated cost only (g-value)
     * - A*: expands states based on accumulated cost + heuristic (f = g + h)
     *
     * Maintains distance tracking, parent reconstruction,
     * and priority queue ordering according to the selected strategy.
     *
     * @param start The starting state
     * @param goal  The goal state
     * @param type  Specifies whether to run Dijkstra or A*
     * 
     * @return The computed path if found, otherwise an empty vector
     */
    std::vector<State> runWeightedSearch(const State& start, const State& goal, SearchType type) const;

    /**
     * @brief Executes Dijkstra's shortest path algorithm.
     *
     * Finds the shortest path based on accumulated cost only.
     * Wrapper around runWeightedSearch with type = Dijkstra.
     *
     * @param start The starting state
     * @param goal  The goal state
     * @return The computed path if found, otherwise an empty vector
     */
    std::vector<State> runDijkstra(const State& start, const State& goal) const;

    /**
     * @brief Executes A* search algorithm.
     *
     * Finds the shortest path using both accumulated cost and
     * a Euclidean heuristic (f = g + h).
     * Wrapper around runWeightedSearch with type = AStar.
     *
     * @param start The starting state
     * @param goal  The goal state
     * 
     * @return The computed path if found, otherwise an empty vector
     */
    std::vector<State> runAStar(const State& start, const State& goal) const;

    /**
     * @brief Reconstructs the path from goal to start using parent map.
     *
     * Traverses the parent map generated during search and builds
     * the final path from start to goal.
     *
     * @param start The starting state
     * @param goal  The goal state
     * @param parents A mapping from each state to its predecessor
     * 
     * @return A vector of states representing the reconstructed path
     */
    std::vector<State> reconstructPath(const State& start, const State& goal,
        const std::unordered_map<State, State>& parents) const;

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
     * @brief Computes a path from a start state to a goal state.
     *
     * Executes the selected graph search algorithm to find a valid
     * path between the given start and goal states.
     *
     * @param start The starting state
     * @param goal  The goal state
     * @param type  The search algorithm to use (default is BFS)
     * 
     * @return A PlanResults struct containing:
     * - path: vector of states from start to goal, empty if no path
     * - success: true if a valid path was found, false otherwise
     * - totalCost: accumulated cost of the path, undefined if no path found
     */
    PlanResults plan(const State& start, const State& goal, SearchType type = SearchType::BFS) const;
};

#endif // PLANNER_H