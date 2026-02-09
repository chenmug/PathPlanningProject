#ifndef WORLD_H
#define WORLD_H

#include <unordered_set>
#include "state.h"

/**
 * @class World
 * @brief Represents a 2D grid world in which an agent can move.
 *
 * The World class is responsible for defining the boundaries of the environment
 * and determining whether a given position is free or blocked.
 * It does not handle agent logic, planning, or decision-making.
 */
class World {
private:
    int width;  // Width of the world (number of columns)
    int height; // Height of the world (number of rows)
    std::unordered_set<State> obstacles;  // Set of blocked cells in the world

public:
    /**
     * @brief Constructs a world object with given dimensions.
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
     * @brief Checks whether a given cell is free.
     *
     * This function determines if the position (x, y) is inside the world
     * boundaries and not blocked.
     *
     * @param x X-coordinate
     * @param y Y-coordinate
     * @return true if the cell is free, false otherwise
     */
    bool isFree(int x, int y) const;

    /**
     * @brief Add a single obstacle to the 2D grid world.
     *
     * @param obstacle An obstacle to add
     * @return true if the obstacle was added, false if it already existed
     */
    bool addObstacle(const State& obstacle);

    /**
     * @brief Remove a single obstacle from the 2D grid world.
     *
     * @param obstacle An obstacle to remove
     * @return true if the obstacle was removed, false if it did not exist
     */
    bool removeObstacle(const State& obstacle);

    /**
     * @brief Clear all obstacles from the 2D grid world
     */
    void clearObstacles();

    /**
     * @brief Print the 2D grid world
     */
    void printWorld() const;
};

#endif // WORLD_H