#include <utz.hpp>
#include <main.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <common/text.hpp>
using txt::operator""_m;

std::vector<std::tuple<std::string, std::vector<const char*>, int, std::string, std::string>> testcases{
	{
		"Test example using multiple features.",
		{ "chronos", "*/15 0 1,15 * 1-5 /usr/bin/find" },
		EXIT_SUCCESS,
		"minute        0 15 30 45"_m +
		"hour          0"_m +
		"day of month  1 15"_m +
		"month         1 2 3 4 5 6 7 8 9 10 11 12"_m +
		"day of week   1 2 3 4 5"_m +
		"command       /usr/bin/find"_m,
		"",
	},
	{
		"Test example using multiple features and extra arguments for the command.",
		{ "chronos", "*/15 0 1,15 * 1-5 find -iname *.txt -print -exec grep \"hello\" {} \;" },
		EXIT_SUCCESS,
		"minute        0 15 30 45"_m +
		"hour          0"_m +
		"day of month  1 15"_m +
		"month         1 2 3 4 5 6 7 8 9 10 11 12"_m +
		"day of week   1 2 3 4 5"_m +
		"command       find -iname *.txt -print -exec grep \"hello\" {} \;"_m,
		"",
	},
	{
		"Test example with no arguments on the command line.",
		{ "chronos" },
		EXIT_FAILURE,
		"",
		"Error: Missing argument in the command line."_m,
	},
	{
		"Test example using empty values for some fields.",
		{ "chronos", "*/15 * 5" },
		EXIT_FAILURE,
		"",
		"Error: The field 'month' is empty!"_m,
	},
	{
		"Test example using invalid values for some fields.",
		{ "chronos", "*/15 ? 1,15 * 1-5 /usr/bin/find" },
		EXIT_FAILURE,
		"",
		"Error: Invalid value for field 'hour' we found '?'!"_m,
	},
};

void utz::test() {
	utz::log << "Starting main test cases..." << std::endl;
	for (auto& [description, arguments, expected_result, expected_output, expected_errors ]: testcases) {
		utz::log << description
			<< ": #arguments = " << arguments.size()
			<< ", expected_result = " << expected_result << std::endl;
		
		// Arrange: Stream to capture standard output.
		std::stringstream output;
		// Arrange: Stream to capture standard errors.
		std::stringstream errors;

		// Arrange: Save the default buffers before redirection.
		auto old_output_buffer = std::cout.rdbuf();
		auto old_errors_buffer = std::cerr.rdbuf();

		// Arrange: Redirection for standard output and errors.
		std::cout.rdbuf(output.rdbuf());
		std::cerr.rdbuf(errors.rdbuf());

		// Act: Call to the actual main function.
		int actual_result = __real_main(arguments.size(), arguments.data());

		// Restoring standard output and errors.
		std::cout.rdbuf(old_output_buffer);
		std::cerr.rdbuf(old_errors_buffer);

		// Assertions
		"main call returns actual_result equals to expected_result."
			| expect(actual_result, is::equal, expected_result);

		"main call puts the expected output to standard output."
			| expect(output.str(), is::equal, expected_output);
		
		"main call puts the expected errors to standard errors."
			| expect(errors.str(), is::equal, expected_errors);
	}
	utz::log << "All test cases have finished!" << std::endl;
}