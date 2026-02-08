#include <iostream>
#include "planner.h"
#include <unordered_set>
#include <unordered_map>

/***************** CONSTRUCTOR *****************/

Planner::Planner(const Graph& graph) : graph(graph)
{
	std::cout << "Create Planner" << std::endl;
}


/***************** DESTRUCTOR *****************/

Planner::~Planner()
{
	std::cout << "Destroy Planner" << std::endl;
}


/******************** PLAN ********************/

std::vector<State> Planner::plan(const State& start, const State& goal)
{
	std::unordered_set<State> visited;
	std::unordered_map<State, State> parents;
}