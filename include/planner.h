#ifndef PLANNER_H
#define PLANNER_H

#include "graph.h"
#include "state.h"
#include <vector>
#include <unordered_map>

/**
 * @enum SearchType
 * @brief Specifies which pathfinding algorithm to use in the Planner.
 *
 * - BFS: Unweighted breadth-first search (ignores edge weights)
 * - Dijkstra: Weighted shortest path search based on accumulated cost
 * - AStar: Weighted search using accumulated cost + heuristic (f = g + h)
 */
enum class SearchType
{
    BFS,
    Dijkstra,
    AStar
};

/**
 * @struct PlanResults
 * @brief Holds the results of a path planning execution.
 *
 * - path: The computed path from start to goal, empty if none found
 * - success: True if a path was found, false otherwise
 * - totalCost: Total accumulated cost of the path
 *
 * If no path is found, `path` is empty and `totalCost` is 0.
 */
struct PlanResults
{
    std::vector<State> path; // Computed path from start to goal
    bool success;            // True if a valid path exists
    int totalCost;           // Total cost of the path
};

/**
 * @class Planner
 * @brief Computes a path between two states using graph search algorithms.
 *
 * The Planner operates on a Graph instance and provides methods to compute paths
 * from a start state to a goal state using BFS, Dijkstra, or A*.
 *
 * Responsibilities:
 * - Compute paths in a state-space graph
 * - Track total cost and path sequence
 *
 * The Planner does not modify the Graph and does not handle simulation or agent logic.
 */
class Planner
{
private:
    const Graph& graph; // The graph representing the world

    /**
     * @struct PQCompare
     * @brief Comparison operator function for priority queue (used in Dijkstra/A*).
     *
     * States with smaller priority (cost) come first.
     */
    struct PQCompare 
    {
        bool operator()(const std::pair<int, State>& a, const std::pair<int, State>& b) const
        {
            return a.first > b.first;
        }
    };

    /**
     * @brief Estimates cost from one state to another using Chebyshev distance.
     *
     * Assumes 8-direction movement (cardinal + diagonal) and is admissible for A*.
     *
     * @param a Current state
     * @param b Target state (goal)
     * 
     * @return Estimated cost (integer)
     */
    int heuristic(const State& a, const State& b) const;

    /**
     * @brief Executes Breadth-First Search (BFS) from start to goal.
     *
     * Expands states in increasing order of depth (unweighted search).
     *
     * @param start Starting state
     * @param goal Goal state
     * 
     * @return PlanResults containing the path, success flag, and total path length
     */
    PlanResults runBFS(const State& start, const State& goal) const;

    /**
     * @brief Executes a weighted search algorithm (Dijkstra or A*).
     *
     * - Dijkstra: Expands nodes based on accumulated cost (g-value)
     * - A*: Expands nodes based on g + heuristic (f-value)
     *
     * Tracks parents for path reconstruction and priority queue for state ordering.
     *
     * @param start Starting state
     * @param goal Goal state
     * @param type SearchType::Dijkstra or SearchType::AStar
     * 
     * @return PlanResults containing path, success flag, and total accumulated cost
     */
    PlanResults runWeightedSearch(const State& start, const State& goal, SearchType type) const;

    /**
     * @brief Executes Dijkstra's shortest path search.
     *
     * Wrapper around runWeightedSearch with type = Dijkstra.
     *
     * @param start Starting state
     * @param goal Goal state
     * 
     * @return PlanResults containing path, success, and total cost
     */
    PlanResults runDijkstra(const State& start, const State& goal) const;

    /**
     * @brief Executes A* search algorithm.
     *
     * Wrapper around runWeightedSearch with type = AStar.
     *
     * @param start Starting state
     * @param goal Goal state
     * 
     * @return PlanResults containing path, success, and total cost
     */
    PlanResults runAStar(const State& start, const State& goal) const;

    /**
     * @brief Reconstructs the path from goal to start using parent mapping.
     *
     * Traverses the parent map generated during search and builds the final path.
     *
     * @param start Starting state
     * @param goal Goal state
     * @param parents Map of child -> parent states
     * 
     * @return Vector of states representing the reconstructed path; empty if no path
     */
    std::vector<State> reconstructPath(const State& start, const State& goal,
        const std::unordered_map<State, State>& parents) const;

public:
    /**
     * @brief Constructs a Planner using a given graph.
     *
     * @param graph Reference to the Graph (must remain valid for Planner's lifetime)
     */
    Planner(const Graph& graph);

    /**
     * @brief Computes a path from start to goal using the specified algorithm.
     *
     * @param start Starting state
     * @param goal Goal state
     * @param type Search algorithm to use (default: BFS)
     * 
     * @return PlanResults containing path, success flag, and total cost
     */
    PlanResults plan(const State& start, const State& goal, SearchType type = SearchType::BFS) const;
};

#endif // PLANNER_H