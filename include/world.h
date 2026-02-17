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
    static const int BLOCK = -1; // Represents a blocked cell (obstacle)
    static const int FREE = 1;   // Default weight for free cells

private:
    int width;                          // Width of the world (number of columns)
    int height;                         // Height of the world (number of rows)
    std::vector<std::vector<int>> grid; // Grid storing weights for each cell

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
     * Initializes all cells with default weight 1 (free).
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
     * Retrieves the weight (or movement cost) of the specified cell based on its state.
     *
     * @param s The state of the cell.
     * 
     * @return Weight of the cell
     */
    int getWeight(const State& s) const;

    /**
     * @brief Sets the weight (movement cost) of a given cell.
     *
     * Updates the weight (movement cost) for the specified cell, using its state.
     *
     * @param s The state of the cell.
     * @param weight The new weight to assign to the cell.
     * 
     * @return true if the cell exists and was updated, false if out of bounds
     */
    bool setWeight(const State& s, int weight);

    /**
     * @brief Checks whether a given cell is free (walkable).
     *
     * Determines if the specified cell is free (walkable), meaning its weight is not -1
     * and it is within the grid boundaries.
     *
     * @param s The state of the cell.
     * 
     * @return true if the cell is free (walkable), false otherwise
     */
    bool isFree(const State& s) const;

    /**
     * @brief Resets all cells to default weight (1 = free).
     */
    void clearGrid();
};

#endif // WORLD_H