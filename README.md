# Grid-Based Path Planning System (C++)

## Overview
A **grid-based path planning system** implemented in modern C++, showcasing classical search algorithms (**BFS, Dijkstra, A***).  
The project emphasizes **deterministic algorithmic behavior**, **clean object-oriented design**, and **low-level implementation from scratch**, with **no external graphics libraries** required.

This system supports **weighted grids**, **diagonal movement**, and **step-by-step visualization**.  
It is suitable for demonstrating pathfinding performance, experimenting with search strategies, and highlighting software engineering skills.

---

## Key Engineering Goals
- Clear separation of concerns between **World, Graph, Planner, Simulation, DisplayManager, StatsManager**, and core data structures **State**
- Deterministic and repeatable results  
- Efficient pathfinding in weighted or unweighted grids  
- Console visualization with **colored output** for clarity  
- Easily testable and extensible architecture  

---

## Core System Flow
1. **World**: A 2D grid of weighted cells (`1.0 = free`, `-1.0 = blocked`). Supports querying, updating weights, and boundary checks.  
2. **State**: Represents discrete `(x, y)` positions in the grid.  
3. **Graph**: Computes neighbors (8-directional), movement costs, and path validation.  
4. **Planner**: Implements BFS (unweighted), Dijkstra (weighted), and A* (weighted with Chebyshev heuristic), reconstructs paths, and computes total cost.  
5. **Simulation**: Executes paths step by step, visualizes Agent movement in the console, and displays metrics such as cost, steps, and expanded nodes.  
6. **DisplayManager**: Handles grid rendering with ANSI colors, marking Agent (`A`), path (`*`), goal (`G`), and obstacles (`#`).  
7. **StatsManager**: Prints comparisons of algorithm results in a table format, including cost, path length, expanded nodes, execution time, and checks for A* optimality.

---

## Algorithm Implementation
- **BFS**: Unweighted shortest path using a queue-based search  
- **Dijkstra**: Weighted shortest path for grids with variable costs  
- **A***: Weighted shortest path with heuristic (Chebyshev) and path reconstruction  
- All algorithms are implemented **from scratch** using standard C++ STL containers  
- Supports blocked cells, weighted cells, and **diagonal movement with √2 cost**  

---

## Visualization & Console Output
- Uses ANSI escape codes for **colored console output**  
- Symbols:  
  - `A` (blue) = Agent  
  - `*` (green) = Path taken  
  - `G` (yellow) = Goal  
  - `#` (red) = Obstacles  
- Displays **current step**, **points/cost**, and **selected cell weight** during simulation  
- Step-by-step movement animation improves clarity and debugging  
- Optional rerun with new random grid  

---

## Testing
Unit and integration tests cover:  
- **State**: equality, hashing, constructors  
- **World**: grid initialization, weight updates, boundary checks  
- **Graph**: neighbor generation, movement costs  
- **Planner**: correctness of BFS, Dijkstra, and A* paths, cost validation  
- **Simulation**: end-to-end console execution  
- **DisplayManager**: correct grid rendering, path and obstacle marking  
- **StatsManager**: result comparison tables and optimality checks  

---

## Project Structure


```
include/        
├─ state.h
├─ world.h
├─ graph.h
├─ planner.h
├─ simulation.h
├─ display_manager.h
├─ colors.h
├─ stats_manager.h

src/           
├─ display_manager.cpp
├─ world.cpp
├─ graph.cpp
├─ planner.cpp
├─ simulation.cpp
├─ stats_manager.cpp

tests/          # Unit tests

main.cpp        # Entry point with console menu for tests, simulation, and algorithm comparison
```

---


## Console Menu Features
- **Run Unit Tests**: Execute automated tests for all modules  
- **Run Console Simulation**: Select an algorithm and simulate Agent movement  
- **Compare Algorithms**: Run BFS, Dijkstra, and A* on the same grid and compare:  
  - Path cost  
  - Path length  
  - Expanded nodes  
  - Execution time  
  - Optimality check for A* against Dijkstra  

---

## How to Build & Run 

- **Language:** C++  
- **Dependencies:** Only C++ standard library, no external graphics or GUI libraries  

### Windows (Visual Studio)
- Open project in Visual Studio  
- Add all `.cpp` and `.h` files  
- Set `main.cpp` as startup  
- Build and Run  

### Linux / macOS
```bash
g++ -std=c++14 -Iinclude src/*.cpp main.cpp -o pathfinder
./pathfinder

```

- The console menu allows you to run unit tests, simulate agent movement, or compare algorithms.
	
---

## Future Extensions
- Multi-agent path planning  
- More complex heuristics or weighted movement strategies  
- Enhanced console visualization (ASCII or extended colors)  
- Integration with graphical visualization frameworks (optional)  

---

## Summary
This project demonstrates:
- Classical pathfinding algorithms implemented **from scratch**  
- Deterministic, testable behavior  
- Clean, modular object-oriented design  
- Interactive console-based visualization and performance comparison  

It is designed to showcase programming skills, OOP design, and algorithmic implementation.