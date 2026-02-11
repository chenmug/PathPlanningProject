# Grid-Based Path Planning & Decision System (C++)

**Status:** Work in Progress – BFS implemented, Dijkstra & A* planned  

A grid-based path planning and decision system implemented in modern C++, focusing on algorithmic design, clean object-oriented architecture, and low-level implementation from scratch. No external libraries are used.

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
- **World:** Stores the grid as weighted cells. Free cells have weight 1, blocked cells use `INF`. Supports querying and updating weights, checking boundaries, and whether cells are walkable (`isFree`).
- **State:** Represents discrete positions `(x, y)` in the grid and is used in all pathfinding algorithms.
- **Graph:** Generates neighbors and connectivity.
- **Planner:** Computes paths (BFS implemented; Dijkstra & A* planned).
- **Decision:** Chooses goals and invokes the planner.
- **Simulation:** Applies actions in discrete steps.

---

## Algorithms
- **Implemented:** BFS, parent-based path reconstruction, hash-based visited tracking
- **Planned:** Dijkstra, A* with heuristics
- All implemented manually, no external libraries.

---

## Testing
Unit and integration tests cover:
- State equality & hashing
- World grid initialization, boundary checks, weights, and free/blocked cells
- Graph neighbor generation
- Planner correctness & path validation
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
- Support for diagonal movement and variable weights in the World
- Dijkstra and A* search with heuristics using cell weights
- Rule-based or multi-agent decision-making
- Simulation loop with logging/visualization
- Advanced motion models

---

## Build & Environment
- **Language:** C++
- **IDE:** Visual Studio (Windows/Linux)
- **Dependencies:** Standard library only

---

### Note: 
This is a work in progress. Current implementation demonstrates BFS, weighted World, and State; additional algorithms and features are planned.