#include "planner.h"
#include "graph.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <cmath>
#include <chrono>   


/***************** CONSTRUCTOR *****************/

Planner::Planner(const Graph& graph) : graph(graph) {}


/****************** HEURISTIC ******************/

double Planner::heuristic(const State& a, const State& b) const
{
    double dx = std::abs(a.x - b.x);
    double dy = std::abs(a.y - b.y);

    return std::max(dx, dy); // Chebyshev distance
}


/******************* RUN BFS *******************/

PlanResults Planner::runBFS(const State& start, const State& goal) const
{
    std::unordered_set<State> visited;
    std::unordered_map<State, State> parents;
    std::queue<State> neighbors;
    State current = { 0,0 };
    double totalCost = 0.0;

    if (start == goal)
    {
        return { {start}, true, 0.0, 0.0 };
    }

    neighbors.push(start);
    visited.insert(start);

    while (!neighbors.empty())
    {
        current = neighbors.front();
        neighbors.pop();

        if (current == goal)
        {
            break;
        }

        for (const auto& neighbor : graph.getNeighbors(current))
        {
            if (visited.find(neighbor) == visited.end())
            {
                parents[neighbor] = current;
                neighbors.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }

    if (parents.find(goal) == parents.end())
    {
        return { {}, false, 0.0, 0.0 };
    }

    auto path = reconstructPath(start, goal, parents);
    totalCost = static_cast<double>(path.size() - 1);

    return { path, true, totalCost, 0.0 };
}


/************** RUN WEIGHT SEARCH **************/

PlanResults Planner::runWeightedSearch(const State& start, const State& goal, SearchType type) const
{
    using PQElement = std::pair<double, State>;
    std::priority_queue<PQElement, std::vector<PQElement>, PQCompare> pq;
    std::unordered_map<State, double> g_cost;
    std::unordered_map<State, State> parents;
    double new_cost = 0.0;
    double new_priority = 0.0;

    if (start == goal)
    {
        return { {start}, true, 0.0, 0.0 };
    }

    g_cost[start] = 0.0;
    parents[start] = start;
    pq.push({ 0.0, start });

    while (!pq.empty())
    {
        auto [priority, current] = pq.top();
        pq.pop();

        if (current == goal)
        {
            break;
        }

        for (const auto& neighbor : graph.getNeighbors(current))
        {
            new_cost = g_cost[current] + graph.getCost(current, neighbor);

            if (g_cost.find(neighbor) == g_cost.end() || new_cost < g_cost[neighbor])
            {
                g_cost[neighbor] = new_cost;
                parents[neighbor] = current;
                new_priority = new_cost;

                if (type == SearchType::AStar)
                {
                    new_priority += heuristic(neighbor, goal);
                }

                pq.push({ new_priority, neighbor });
            }
        }
    }

    if (parents.find(goal) == parents.end())
    {
        return { {}, false, 0.0, 0.0 };
    }

    auto path = reconstructPath(start, goal, parents);
    return { path, true, g_cost[goal], 0.0 };
}


/**************** RUN DIJKSTRA *****************/

PlanResults Planner::runDijkstra(const State& start, const State& goal) const
{
    return runWeightedSearch(start, goal, SearchType::Dijkstra);
}


/******************* RUN A* ********************/

PlanResults Planner::runAStar(const State& start, const State& goal) const
{
    return runWeightedSearch(start, goal, SearchType::AStar);
}


/************** RECONSTRUCT PATH ***************/

std::vector<State> Planner::reconstructPath(const State& start, const State& goal,
    const std::unordered_map<State, State>& parents) const
{
    std::vector<State> path;
    State current = goal;

    if (parents.find(goal) == parents.end())
    {
        return {};
    }

    while (current != start)
    {
        path.push_back(current);
        current = parents.at(current);
    }

    path.push_back(start);
    std::reverse(path.begin(), path.end());

    return path;
}


/******************** PLAN ********************/

PlanResults Planner::plan(const State& start, const State& goal, SearchType type) const
{
    if (!graph.isValid(start) || !graph.isValid(goal))
    {
        return { {}, false, 0.0, 0.0 };
    }

    auto startTime = std::chrono::steady_clock::now();
    PlanResults result;

    switch (type)
    {
    case SearchType::BFS:
        result = runBFS(start, goal);
        break;

    case SearchType::Dijkstra:
        result = runDijkstra(start, goal);
        break;

    case SearchType::AStar:
        result = runAStar(start, goal);
        break;

    default:
        return { {}, false, 0.0, 0.0 };
    }

    auto endTime = std::chrono::steady_clock::now();
    result.executionTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();

    return result;
}