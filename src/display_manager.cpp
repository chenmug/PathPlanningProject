#include "display_manager.h"
#include "colors.h"
#include <iostream>


// Static helper function declarations
static void markObstacles(const World& world, std::vector<std::vector<char>>& grid);

static void markPath(const std::vector<State>& path, std::vector<std::vector<char>>& grid,
    const State& agentPos, const State& goal);

static void printAlgorithmHeader(SearchType type, int step, int points);

static void printGrid(const std::vector<std::vector<char>>& grid);



/****************** CLASS FUNCTIONS ******************/

/**************** DISPLAY GRID ****************/

void DisplayManager::displayGrid(const World& world, const State& agentPos, const std::vector<State>& path,
    SearchType type, const State& goal, int step, int points)
{
    std::vector<std::vector<char>> grid(world.getHeight(), std::vector<char>(world.getWidth(), '.'));
    double currentWeight = 0.0;

    markObstacles(world, grid);
    markPath(path, grid, agentPos, goal);

    printAlgorithmHeader(type, step, points);
    printGrid(grid);

    if (type != SearchType::BFS) // If it's Dijkstra or A*, display the weight of the selected cell
    {
        currentWeight = world.getWeight(agentPos);
        std::cout << "Selected cell weight = " << currentWeight << " (choosing best option)\n";
    }

    std::cout << "\n";
}


/************* CLEAR SCREEN *************/

void DisplayManager::clearScreen()
{
    std::cout << "\033[H\033[2J"; // Clear the screen using ANSI escape codes
}


/*********** HELPER FUNCTIONS ***********/

// Mark Obstacles
static void markObstacles(const World& world, std::vector<std::vector<char>>& grid)
{
    int x = 0;
    int y = 0;
    State s{ x, y };

    for (y = 0; y < world.getHeight(); ++y)
    {
        for (x = 0; x < world.getWidth(); ++x)
        {
            s.x = x;
            s.y = y;

            if (!world.isFree(s))
            {
                grid[y][x] = '#'; 
            }
        }
    }
}


// Mark path
static void markPath(const std::vector<State>& path, std::vector<std::vector<char>>& grid,
    const State& agentPos, const State& goal)
{
    for (const auto& stepPos : path)
    {
        if (stepPos != agentPos && stepPos != goal)
        {
            grid[stepPos.y][stepPos.x] = '*'; // Mark as part of the path
        }
    }

    if (agentPos != goal) // Mark the goal, only if the agent is not already at the goal
    {
        grid[goal.y][goal.x] = 'G';
    }
    grid[agentPos.y][agentPos.x] = 'A'; // Mark the agent
}


// Print algorithm header
static void printAlgorithmHeader(SearchType type, int step, int points)
{
    std::cout << "===== Algorithm: ";

    switch (type)
    {
    case SearchType::Dijkstra:
        std::cout << "Dijkstra";
        break;

    case SearchType::AStar:
        std::cout << "A*";
        break;

    default:
        std::cout << "BFS";
        break;
    }

    std::cout << " | Step: " << step << " | Points/Cost: " << points << " =====\n\n";
}


// Print grid
static void printGrid(const std::vector<std::vector<char>>& grid)
{
    const std::string cellSpacing = "  ";
    int x = 0;
    int y = 0;
    char c = '0';
    std::string color;

    // Print the grid with colors
    for (y = 0; y < grid.size(); ++y)
    {
        for (x = 0; x < grid[0].size(); ++x)
        {
            c = grid[y][x];
            if (c == '#')
            {
                color = Colors::RED;
            }
            else if (c == '*')
            {
                color = Colors::GREEN;
            }
            else if (c == 'A')
            {
                color = Colors::BLUE;
            }
            else if (c == 'G')
            {
                color = Colors::YELLOW;
            }
            else
            {
                color = Colors::GRAY;
            }

            std::cout << color << c << Colors::RESET << cellSpacing;
        }

        std::cout << "\n";
    }
}