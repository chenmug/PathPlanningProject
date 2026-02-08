# Grid-Based Path Planning & Decision System (C++)

A **grid-based path planning and decision system** implemented in modern C++, with a focus on **algorithmic design**, **clean object-oriented architecture**, and **low-level implementation from scratch**. 
No external libraries are used.

The system models a 2D world as a state-space graph, computes paths, and supports higher-level decision and simulation layers:

	World -> Graph -> Planner -> Decision -> Simulation

---

## Motivation

- Demonstrate strong C++ fundamentals and object-oriented design  
- Implement classical algorithms from scratch  
- Build a clear, extensible architecture for planning and simulation  
- Maintain deterministic behavior and testability  

---

## System Overview

**Layers & Responsibilities:**

- **World:** Defines grid dimensions and environmental constraints.  
- **State:** Represents discrete positions in the grid (hashable, comparable).  
- **Graph:** Generates neighbors and connectivity information.  
- **Planner:** Computes paths (currently BFS, planned Dijkstra & A*).  
- **Decision:** Chooses goals and invokes the planner.  
- **Simulation:** Advances system in discrete steps, applies actions, enables reproducible experiments.  

Each layer is **loosely coupled** and communicates via explicit interfaces.

---

## Algorithms

- **Implemented:** BFS, parent-based path reconstruction, hash-based visited tracking  
- **Planned:** Dijkstra, A* with heuristics, cost-aware planning  

All implemented manually, without external libraries.

---

## Testing

Includes unit and integration tests for:

- State equality & hashing  
- World boundary checks  
- Graph neighbor generation  
- Planner correctness & path validation  
- End-to-end system sanity  

---

## Project Structure

- `include/` - Header files for each class
- `src/` - Implementation files
- `tests/` - Unit and integration tests
- `main.cpp` - Entry point 

---

## Design Principles

- Clear separation of responsibilities  
- Deterministic behavior  
- Minimal coupling  
- Test-driven validation  
- Extensible architecture  

---

## Planned Extensions

- Obstacles and weighted edges  
- A* search with heuristics  
- Rule-based or multi-agent decision-making  
- Simulation loop with logging/visualization  
- Advanced motion models  

---

## Build & Environment

- **Language:** C++  
- **IDE:** Visual Studio (Windows/Linux)  
- **Dependencies:** Standard library only