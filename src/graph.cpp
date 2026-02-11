#include "graph.h"

#define DIAGONAL_COST 1.4142

/***************** STATIC MOVES *****************/

const std::vector<State> Graph::moves = 
{
	{1,0}, {-1,0}, {0,1}, {0,-1},   // cardinal
	{1,1}, {1,-1}, {-1,1}, {-1,-1}  // diagonal
};

/***************** CONSTRUCTOR *****************/

Graph::Graph(const World* world) : world(world) {}


/**************** GET NEIGHBOR ****************/

std::vector<State> Graph::getNeighbors(const State& state) const
{
	std::vector<State> neighbors;
	
	for (const auto& move : moves)
	{
		State next;
		next.x = state.x + move.x;
		next.y = state.y + move.y;

		if (isValid(next))
		{
			neighbors.push_back(next);
		}
	}

	return neighbors;
}


/***************** GET COST *****************/

int Graph::getCost(const State& from, const State& to) const
{
	int dx = 0;
	int dy = 0;

	if (!isValid(to))
	{
		return world->INF;
	}

	dx = abs(to.x - from.x);
	dy = abs(to.y - from.y);
	if (dx + dy == 2)
	{
		return int(DIAGONAL_COST * world->getWeight(to));  // diagonal
	}

	else
	{
		return world->getWeight(to);  // cardinal
	}
}


/***************** IS VALID *****************/

bool Graph::isValid(const State& state) const
{
	return world->isFree(state);
}


/***************** IS GOAL ******************/

bool Graph::isGoal(const State& state, const State& goal) const
{
	return state == goal;
}