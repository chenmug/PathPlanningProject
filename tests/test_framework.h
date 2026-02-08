#pragma once
#include <iostream>
#include <string>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BOLD    "\033[1m"
#define BLUE    "\033[34m"


struct TestStats
{
    int passed = 0;
    int failed = 0;
};


inline TestStats& stats()
{
    static TestStats s;
    return s;
}

// Print a header for each test suite
inline void testHeader(const std::string& name)
{
    std::cout << "\n" << BOLD << BLUE << "===== " << name << " =====" << RESET << std::endl;
}

// Check a single condition and print [PASS]/[FAIL] in color
inline void check(bool condition, const std::string& description)
{
    if (condition)
    {
        std::cout << GREEN << "[PASS]" << RESET << " " << description << std::endl;
        stats().passed++;
    }
    else
    {
        std::cout << RED << "[FAIL]" << RESET << " " << description << std::endl;
        stats().failed++;
    }
}


// Print final summary of all tests
inline void printSummary()
{
    std::cout << "\n\n" << BOLD << BLUE << "======= TEST SUMMARY =======" << RESET << std::endl;

    std::cout << GREEN << "[PASS]" << RESET << "Total: " << stats().passed << std::endl;
    std::cout << RED << "[FAIL]" << RESET << "Total: " << stats().failed << "\n\n" << std::endl;

    if (stats().failed == 0)
    {
        std::cout << GREEN << BOLD << "ALL TESTS PASSED" << RESET << std::endl;
    }
    else
    {
        std::cout << RED << BOLD << "SOME TESTS FAILED" << RESET << std::endl;
    }
}