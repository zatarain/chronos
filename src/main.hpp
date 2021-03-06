#ifndef __MAIN_HEADER__
#define __MAIN_HEADER__

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "common/text.hpp"
#include "common/parser.hpp"

using hashmap = std::unordered_map<std::string, std::string>;

/**
 * Entry point of the application.
 * 
 * @param int           Number of arguments on the command line.
 * @param const char*[] A list of arguments on the command line. First argument is the name of the application
 * @return int          Returns EXIT_SUCCESS if the application ran without errors, otherwise EXIT_FAILURE.
 */
int main(int, const char*[]);

#endif // __MAIN_HEADER__