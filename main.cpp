#include <iostream>
#include "world.h"

int main()
{
	World world(10, 10);
	std::cout << "World size: " << world.getWidth() << "x" << world.getHeight() << std::endl;
	std::cout << "Is (5,5) free? " << world.isFree(5, 5) << std::endl;
	return 0;
}