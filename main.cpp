#include "simulation.h"
#include "run_tests.h"    
#include "colors.h"
#include <iostream>


// ----------------------------
// PRINT MAIN MENU - HELPER
// ----------------------------
void printMainMenu()
{
    std::cout << Colors::LIGHT_PURPLE << "=====================================" << Colors::RESET << "\n";
    std::cout << Colors::CYAN << "            PATH PLANNER            " << Colors::RESET << "\n";
    std::cout << Colors::LIGHT_PURPLE << "=====================================" << Colors::RESET << "\n\n";

    std::cout << Colors::CYAN << "  [1]  Run Unit Tests" << Colors::RESET << "\n";
    std::cout << Colors::CYAN << "  [2]  Run Console Simulation" << Colors::RESET << "\n";
    std::cout << Colors::CYAN << "  [3]  Compare All Algorithms" << Colors::RESET << "\n";
    std::cout << Colors::CYAN << "  [4]  Exit" << Colors::RESET << "\n\n";

    std::cout << Colors::LIGHT_PURPLE << "-------------------------------------" << Colors::RESET << "\n";
    std::cout << Colors::GRAY << "Select option: " << Colors::RESET;
}


// ----------------------------
// CHOOSE ALGORITHM - HELPER
// ----------------------------
SearchType chooseAlgorithm()
{
    int choice = 0;
    
    std::cout << "\nSelect algorithm:\n";
    std::cout << "  [1] BFS\n";
    std::cout << "  [2] Dijkstra\n";
    std::cout << "  [3] A*\n";
    std::cout << "Choice: ";

    std::cin >> choice;
    switch (choice)
    {
    case 2: 
        return SearchType::Dijkstra;

    case 3: 
        return SearchType::AStar;

    default: 
        return SearchType::BFS;
    }
}


// -----------------------------
// CONSOLE SIMULATION - HELPER
// -----------------------------
void runConsoleSimulation()
{
    int width = 15;
    int height = 15;
    State start{ 0,0 };
    State goal{ 14,14 };

    char answer = 'y';
    while (answer == 'y' || answer == 'Y')
    {
        SearchType type = chooseAlgorithm();

        Simulation sim(width, height, start, goal);
        sim.run(type);

        std::cout << "\nRun again with new random obstacles? (y/n): ";
        std::cin >> answer;
    }
}


// -----------------------------
// RUN COMPARISON - HELPER
// -----------------------------
void runComparison()
{
    int width = 15;
    int height = 15;
    State start{ 0,0 };
    State goal{ 14,14 };

    Simulation sim(width, height, start, goal);

    sim.compareAlgorithms();

    std::cout << "\nPress Enter to return to menu...";
    std::cin.ignore();
    std::cin.get();
}


// -------------------------
// MAIN
// -------------------------
int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    bool running = true;
    int choice = 0;

    while (running)
    {
        printMainMenu();
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            runAllTests();
            break;

        case 2:
            runConsoleSimulation();
            break;

        case 3:
            runComparison();
            break;

        case 4:
            running = false;
            break;

        default:
            std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}