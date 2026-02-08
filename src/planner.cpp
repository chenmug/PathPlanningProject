#include "planner.h"
#include "graph.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>

/***************** CONSTRUCTOR *****************/

Planner::Planner(const Graph& graph) : graph(graph){}


/******************** PLAN ********************/

std::vector<State> Planner::plan(const State& start, const State& goal)
{
	std::unordered_set<State> visited;
	std::unordered_map<State, State> parents;
	std::queue<State> neighbors;
	std::vector<State> path;

	State current = start;

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

	if (current != goal)
	{
		return {};
	}

	while (current != start)
	{
		path.push_back(current);
		current = parents[current];
	}

	path.push_back(start);
	std::reverse(path.begin(), path.end());
	
	return path;
}