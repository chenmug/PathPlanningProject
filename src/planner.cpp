#include "planner.h"
#include "graph.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <cmath>

/***************** CONSTRUCTOR *****************/

Planner::Planner(const Graph& graph) : graph(graph){}


/****************** HEURISTIC ******************/

int Planner::heuristic(const State& a, const State& b) const
{
	int dx = std::abs(a.x - b.x);
	int dy = std::abs(a.y - b.y);

	return std::max(dx, dy);
}


/******************* RUN BFS *******************/

PlanResults Planner::runBFS(const State& start, const State& goal) const
{
	std::unordered_set<State> visited;
	std::unordered_map<State, State> parents;
	std::queue<State> neighbors;
	State current = start;
	int totalCost = 0;

	if (start == goal)
	{
		return { {start}, true, 0 };
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
		return PlanResults{ {}, false, 0 };
	}
	else
	{
		auto path = reconstructPath(start, goal, parents);
		totalCost = path.size() - 1;

		return PlanResults{ path, true, totalCost };
	}
}


/************** RUN WEIGHT SEARCH **************/

PlanResults Planner::runWeightedSearch(const State& start, const State& goal, SearchType type) const
{
	// priority_queue: {priority, state}, min-heap
	using PQElement = std::pair<int, State>;
	std::priority_queue<PQElement, std::vector<PQElement>, std::greater<>> pq;

	std::unordered_map<State, int> g_cost;
	std::unordered_map<State, State> parents;
	State current = start;
	int priority = 0;
	int new_cost = 0;

	if (start == goal)
	{
		return PlanResults{ {start}, true, 0 };
	}

	g_cost[start] = 0;
	parents[start] = start;
	pq.push({ 0, start });

	while (!pq.empty())
	{
		PQElement elem = pq.top();
		pq.pop();

		priority = elem.first;
		current = elem.second;

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
				priority = new_cost;

				if (type == SearchType::AStar)
				{
					priority += heuristic(neighbor, goal);
				}
				pq.push({ priority, neighbor });
			}
		}
	}

	if (parents.find(goal) == parents.end())
	{
		return { {}, false, 0 };
	}
	else
	{
		auto path = reconstructPath(start, goal, parents);
		return { path, true, g_cost[goal] };
	}
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
		auto it = parents.find(current);
		if (it == parents.end())
		{
			return {}; 
		}
		current = it->second;
	}

	path.push_back(start);
	std::reverse(path.begin(), path.end());

	return path;
}


/******************** PLAN ********************/

PlanResults Planner::plan(const State& start, const State& goal, SearchType type) const
{
	switch (type)
	{
	case SearchType::BFS:
		return runBFS(start, goal);

	case SearchType::Dijkstra:
		return runDijkstra(start, goal);

	case SearchType::AStar:
		return runAStar(start, goal);

	default:
		return { {}, false, 0 };
	}
}