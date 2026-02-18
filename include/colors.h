#ifndef COLORS_H
#define COLORS_H

#include <string>

/**
 * @namespace Colors
 * @brief Namespace that contains ANSI color codes for terminal output.
 *
 * This namespace includes a set of constants for common terminal text colors,
 * providing easy access to change text colors in terminal applications.
 */
namespace Colors 
{
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[1;33m";
    const std::string BLUE = "\033[1;34m";
    const std::string CYAN = "\033[1;36m";
    const std::string GRAY = "\033[37m";
    const std::string LIGHT_PURPLE = "\033[38;5;177m";
}

#endif // COLORS_H