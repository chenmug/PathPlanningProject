#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "state.h"


/**
 * @class World
 * @brief Represents a 2D grid world where each cell has a movement cost (weight).
 *
 * The World class is responsible for storing the environment grid,
 * including weights for each cell, and determining whether a cell is free (walkable)
 * or blocked.
 *
 * It does not handle agent logic, path planning, or decision-making.
 */
class World 
{
public:
    static constexpr double BLOCK = -1.0; // Represents a blocked cell (obstacle)
    static constexpr double FREE = 1.0;  // Default weight for free cells

private:
    int width;                             // Width of the world (number of columns)
    int height;                            // Height of the world (number of rows)
    std::vector<std::vector<double>> grid; // Grid storing weights for each cell

    /**
     * @brief Checks if the given coordinates are within world boundaries.
     *
     * This is a private helper used internally by other functions.
     *
     * @param x X-coordinate
     * @param y Y-coordinate
     * 
     * @return true if (x, y) is inside the grid, false otherwise
     */
    bool inBounds(int x, int y) const;

public:

    /**
     * @brief Constructs a world object with given dimensions.
     *
     * Initializes all cells with default weight 1.0 (free).
     *
     * @param w Width of the world
     * @param h Height of the world
     */
    World(int w, int h);

    /**
     * @brief Returns the width of the world.
     *
     * @return Width of the world
     */
    int getWidth() const;

    /**
     * @brief Returns the height of the world.
     *
     * @return Height of the world
     */
    int getHeight() const;

    /**
     * @brief Returns the weight (movement cost) of a given cell.
     *
     * Retrieves the weight (or movement cost) for the specified cell based on its state. 
     * The function return `BLOCK` if the cell is out of bounds.
     *
     * @param s The state of the cell to check
     *
     * @return Weight of the cell (double), representing the movement cost (or -1.0 for blocked cells)
     */
    double getWeight(const State& s) const;

    /**
     * @brief Sets the weight (movement cost) of a given cell.
     *
     * Updates the weight (movement cost) for the specified cell, identified by its state.
     * If the cell is out of bounds, the function returns false and does not update the grid.
     * If the provided weight is negative, it will be set to `BLOCK`.
     *
     * @param s The state of the cell to modify
     * @param weight The new weight (movement cost) to assign to the cell
     *
     * @return true if the cell exists within bounds and was updated, false if the cell is out of bounds
     */
    bool setWeight(const State& s, double weight);

    /**
     * @brief Checks whether a given cell is free (walkable).
     *
     * Determines if the specified cell is free (walkable), meaning its weight is not -1.0
     * and it is within the grid boundaries.
     *
     * @param s The state of the cell.
     * 
     * @return true if the cell is free (walkable), false otherwise
     */
    bool isFree(const State& s) const;

    /**
     * @brief Resets all cells to the default weight (1.0 = free).
     *
     * This function resets the entire world grid, setting every cell's weight to 1.0, which represents a free (walkable) cell.
     * It will override all previously set weights, including blocked cells (which had weight = -1.0), setting them all to the default value of 1.0.
     */
    void clearGrid();
};

#endif // WORLD_H