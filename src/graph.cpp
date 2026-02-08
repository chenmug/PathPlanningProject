#include "graph.h"

/***************** CONSTRUCTOR *****************/

Graph::Graph(const World* world) : world(world) {}


/**************** GET NEIGHBOR ****************/

std::vector<State> Graph::getNeighbors(const State& state) const
{
	std::vector<State> neighbors;
	static const std::vector<State> moves = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
	
	for (const auto& move : moves)
	{
		State next;
		next.x = state.x + move.x;
		next.y = state.y + move.y;

		if (world->isFree(next.x, next.y))
		{
			neighbors.push_back(next);
		}
	}

	return neighbors;
}