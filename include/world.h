#ifndef WORLD_H
#define WORLD_H

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

    // TODO:
    // Add, remove, print, reset obstacles
};

#endif // WORLD_H