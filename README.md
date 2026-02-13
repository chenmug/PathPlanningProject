# Grid-Based Path Planning & Decision System (C++)

**Status:** Work in Progress – BFS, Dijkstra & A* implemented  

A grid-based path planning and decision system implemented in modern C++, focusing on algorithmic design, clean object-oriented architecture, and low-level implementation from scratch. No external libraries are used (SFML optional for visualization).

---

## Motivation
- Showcase C++ fundamentals and object-oriented design
- Implement classical pathfinding algorithms from scratch
- Build a clear, extensible architecture for planning and decision-making
- Maintain deterministic behavior and testability

---

## System Overview

Layers:

```
World -> Graph -> Planner -> Decision -> Simulation
```

**Responsibilities:**
- **World:** Stores the grid as weighted cells. Free cells have weight 1, blocked cells use -1. Supports querying and updating weights, checking boundaries, and whether cells are walkable (`isFree`).
- **State:** Represents discrete positions `(x, y)` in the grid and is used in all pathfinding algorithms.
- **Graph:** Generates neighbors (8-directional) and movement costs, handles blocked cells, and provides `getCost` for both cardinal and diagonal moves.
- **Planner:** Computes paths using BFS (unweighted), Dijkstra (weighted), and A* (weighted with Chebyshev heuristic). Handles path reconstruction and total cost calculation.
- **Decision:** Chooses goals and invokes the planner.
- **Simulation:** Applies actions in discrete steps; optionally visualized with SFML.

---

## Algorithms
- **Implemented:** BFS, Dijkstra, A* with heuristics, parent-based path reconstruction, hash-based visited tracking  
- Supports weighted edges, 8-directional movement, and blocked/free cells (-1 = blocked, 1 = free)  
- All implemented manually, no external libraries  

---

## Testing
Unit and integration tests cover:
- **State:** equality & hashing, default constructor, extreme values
- **World:** grid initialization, default/free/blocked cells, boundary checks, weight updates, negative weight protection, `clearGrid`
- **Graph:** neighbor generation (8 directions) and cost calculations
- **Planner:** pathfinding correctness & path validation for BFS, Dijkstra, and A*
- End-to-end system sanity

---

## Project Structure

```
include/      # Header files
src/          # Implementation files
tests/        # Unit & integration tests
main.cpp      # Entry point
```

---

## Planned Extensions
- Rule-based or multi-agent decision-making
- Simulation loop with logging/visualization
- Advanced motion models

---

## Build & Environment
- **Language:** C++
- **IDE:** Visual Studio (Windows/Linux)
- **Dependencies:** Standard library only (SFML optional for visualization)

---