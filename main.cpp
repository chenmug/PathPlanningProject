#include <iostream>
#include "world.h"
#include "state.h"
#include "graph.h"

int main()
{
	World world(10, 10);

	std::cout << "World size: " << world.getWidth() << "x" << world.getHeight() << std::endl;
	std::cout << "Is (5,5) free? " << world.isFree(5, 5) << std::endl;
	std::cout << "Is (-1,0) free? " << world.isFree(-1, 0) << std::endl;
	std::cout << "Is (0,10) free? " << world.isFree(0, 10) << std::endl;

	State state{ 5,0 };
	Graph graph(&world);

	auto neighbors = graph.getNeighbors(state);
	std::cout << "Neighbors of (5,0):" << std::endl;
	for (const auto& n : neighbors)
	{
		std::cout << "(" << n.x << "," << n.y << ")" << std::endl;
	}

	return 0;
}