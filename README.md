# Grid-Based Path Planning & Decision System (C++)

This project implements a **grid-based path planning and decision system** in modern C++,
with a strong focus on **algorithmic design**, **clean object-oriented architecture**,
and **low-level implementation from scratch**.

The system models a 2D world as a state-space graph, computes paths between states using
classical graph search algorithms, and is designed to support higher-level
decision-making and simulation layers.

No external planning, robotics, or graph libraries are used.

---

## Project Motivation

This project was developed to demonstrate:

- Strong C++ fundamentals and object-oriented design
- Implementation of classical algorithms from scratch
- Clear separation of responsibilities in a non-trivial system
- Ability to design extensible infrastructure for planning and simulation

The architecture is intentionally generic and deterministic, making it suitable
for future extensions such as robotics-style planning and autonomous agent simulation.

---

## System Overview

The system is organized into clearly separated layers:

	World -> Graph -> Planner -> Decision -> Simulation


Each layer has a single, well-defined responsibility and communicates only through
explicit interfaces.

---

## Core Components

### World
Represents a 2D grid environment.

Responsibilities:
- Defines world dimensions
- Validates whether a cell is inside bounds
- Provides environmental constraints (e.g., free / blocked cells)

The world does **not** contain agent logic or planning algorithms.

---

### State
Represents a discrete position in the grid.

Features:
- Lightweight data structure
- Equality comparison (`operator==`)
- Hashing support for use in `std::unordered_map` and `std::unordered_set`

States serve as nodes in the state-space graph and are intentionally kept minimal.

---

### Graph
Represents the state-space graph induced by the world.

Responsibilities:
- Generates valid neighboring states
- Enforces world constraints via composition (reference to `World`)
- Provides connectivity information only

The graph does **not** perform search, planning, or decision-making.

---

### Planner
Computes paths between states in the graph.

Current capabilities:
- Implements **Breadth-First Search (BFS)**
- Uses a queue-based frontier
- Tracks visited states using hash-based containers
- Reconstructs paths using a parent map
- Returns an empty path if the goal is unreachable

The planner is fully decoupled from the world and operates only on the graph interface.

---

### Decision Layer (Designed & Extensible)
The decision layer is designed to:
- Select goals based on rules or system state
- Invoke the planner to compute paths
- Remain independent of low-level execution details

This separation enables future extensions such as rule-based or heuristic decision logic.

---

### Simulation Layer (Designed & Extensible)
The simulation layer is designed to:
- Combine world, planner, and decision logic
- Advance the system in discrete time steps
- Apply actions and update agent state deterministically

This layer enables reproducible experiments and debugging.

---

## Algorithms

Implemented:
- Breadth-First Search (BFS)
- Hash-based visited state tracking
- Parent-based path reconstruction

Planned:
- Dijkstra
- A* with heuristic functions
- Cost-aware planning

All algorithms are implemented manually without relying on external libraries.

---

## Testing

The project includes a dedicated test executable with comprehensive coverage:

- State equality and hashing correctness
- World boundary and edge conditions
- Graph neighbor generation (center, edge, corner cases)
- Planner correctness (path validity, unreachable goals)
- Integration-level sanity checks

Test output is explicit, readable, and designed to validate both correctness and design assumptions.

---

## Project Structure

- `include/` - Header files for each class
- `src/` - Implementation files
- `tests/` - Unit and integration tests
- `main.cpp` - Entry point of the program

---

## Design Principles

- Clear separation of responsibilities
- Deterministic behavior
- Minimal coupling between components
- Algorithm-first implementation
- Test-driven validation
- Extensible architecture

---

## Planned Extensions

- Obstacles and blocked cells
- Weighted edges and cost functions
- A* search with heuristics
- Rule-based decision-making
- Multiple agents
- Simulation loop with logging / visualization
- More advanced motion models (orientation, actions)

---

## Build & Environment

- Language: C++
- IDE: Visual Studio
- Platform: Windows / Linux
- Dependencies: None (standard library only)