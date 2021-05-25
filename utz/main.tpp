#include <utz.hpp>
#include <main.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>

void utz::test() {
	utz::log << "Starting main test cases..." << std::endl;
    // Arrange
    const char* arguments[] = { "chronos", "*/15 0 1,15 * 1-5 /usr/bin/find" };
    
    // Act
    int actual_result = __real_main(2, arguments);

    // Assertions
    "main call success (actual_result == EXIT_SUCCESS)."
        | expect(actual_result, is::equal, EXIT_SUCCESS);

	utz::log << "All test cases have finished!" << std::endl;
}