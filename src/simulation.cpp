#include "simulation.h"
#include "stats_manager.h"
#include "display_manager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib> // for rand()


// Static helper function declaration
static double generateCellWeight(SearchType type);


/**************** CONSTRUCTOR *****************/

Simulation::Simulation(int width, int height, const State& start, const State& goal)
    : width(width), height(height), world(width, height), graph(&world), planner(graph),
    start(start), goal(goal)
{}


/*************** RANDOM OBSTACLES **************/

void Simulation::generateRandomObstacles(int obstaclePercentage, SearchType type)
{
    int x = 0;
    int y = 0;

    for (x = 0; x < width; ++x)
    {
        for (y = 0; y < height; ++y)
        {
            if ((x == start.x && y == start.y) || (x == goal.x && y == goal.y))
            {
                world.setWeight({ x, y }, world.FREE);
                continue;
            }

            if (rand() % 100 < obstaclePercentage)
            {
                world.setWeight({ x, y }, World::BLOCK);
                continue;
            }

            world.setWeight({ x, y }, generateCellWeight(type));
        }
    }
}


/**************** VISUALIZE PATH ****************/

void Simulation::visualizePath(const PlanResults& results, SearchType type)
{
    std::vector<State> pathSoFar;
    double points = 0.0;
    size_t step = 0;

    for (step = 1; step < results.path.size(); ++step)
    {
        State prev = results.path[step - 1];
        State curr = results.path[step];
        pathSoFar.push_back(prev);

        if (type == SearchType::BFS)
        {
            points = static_cast<int>(step);
        }
        else
        {
            points += world.getWeight(curr);
        }

        // Clear the screen and display the grid in real-time
        DisplayManager::clearScreen();
        DisplayManager::displayGrid(world, curr, pathSoFar, type, goal, step, points);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    pathSoFar.push_back(results.path.back());

    // Display the final grid
    DisplayManager::clearScreen();
    DisplayManager::displayGrid(world, goal, pathSoFar, type, goal, static_cast<int>(results.path.size() - 1), points);

    std::cout << "\nGoal reached! Total points/cost: " << points
        << ", Execution time: " << results.executionTime << " ms\n";
}


/**************** VERIFY CORRECTNESS ****************/

void Simulation::verifyCorrectness(const PlanResults& results, SearchType type)
{
    if (type == SearchType::Dijkstra || type == SearchType::AStar)
    {
        StatsManager stats;
        std::string name = (type == SearchType::Dijkstra) ? "Dijkstra" : "A*";

        std::cout << "\nAlgorithm finished. Checking shortest-path correctness...\n";
        stats.printCorrectnessReport(results, name);

        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}


/**************** RUN SIMULATION ****************/

void Simulation::run(SearchType type)
{
    generateRandomObstacles(20, type);
    
    PlanResults results = planner.plan(start, goal, type);
    if (!results.success)
    {
        DisplayManager::displayGrid(world, start, {}, type, goal, 0, 0);
       std::cout << "\nNo path found!\n";
       return;
    }

    visualizePath(results, type);                       
    verifyCorrectness(results, type);                  
}


/*************** COMPARE ALGORITHMS ***************/

void Simulation::compareAlgorithms() 
{
    generateRandomObstacles(20, SearchType::Dijkstra);

    PlanResults bfsRes = planner.plan(start, goal, SearchType::BFS);
    PlanResults dijRes = planner.plan(start, goal, SearchType::Dijkstra);
    PlanResults aStarRes = planner.plan(start, goal, SearchType::AStar);

    StatsManager::printComparisonResults(bfsRes, dijRes, aStarRes);
}


/*********** HELPER FUNCTION ***********/

static double generateCellWeight(SearchType type)
{
    if (type == SearchType::BFS)
    {
        return 1.0;
    }

    return 1.0 + (rand() / (double)RAND_MAX) * 7.0;
}