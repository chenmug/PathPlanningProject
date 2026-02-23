#pragma once
#include <string>
#include <cmath>
#include <iostream>

/**
 * @brief Checks whether two double values are approximately equal within a small tolerance.
 *
 * This helper function is used across multiple test files to verify floating-point calculations.
 * 
 * @param actual The computed or observed value
 * @param expected The expected value to compare against
 * @param testName A descriptive name for the test, printed with the result
 */
void checkDouble(double actual, double expected, const char* testName);