#include "graph.h"

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
	State next;
	
	for (const auto& move : moves)
	{
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

double Graph::getCost(const State& from, const State& to) const
{
	int dx = 0;
	int dy = 0;

	if (!isValid(to))
	{
		return world->BLOCK;
	}

	dx = abs(to.x - from.x);
	dy = abs(to.y - from.y);

	if ((dx > 1) || (dy > 1) || (dx == 0 && dy == 0))
	{
		return NOT_NEIGHBOR;
	}

	if (dx + dy == 2)
	{
		return DIAGONAL_COST * world->getWeight(to);  // diagonal
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