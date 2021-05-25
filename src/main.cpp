#include "main.hpp"

int main(int argc, char const *argv[]) {
	// Check number of arguments in the command line.
	if (argc < 2) {
		std::cerr << "Error: Missing argument in the command line." << std::endl;
		return EXIT_FAILURE;
	}
	
	// Put the argument from command line in an stream in order to tokenize each field.
	std::stringstream expression(argv[1]);
	
	// Hashmap to put all the fields separated.
	hashmap table;
	
	// Tokenize and check each field is not empty.
	try {
		for(auto& [field, begin, end]: chronos::fields) {
			if (begin != end) {
				// Read and check the numeric field.
				expression >> table[field];
				chronos::check(field, table[field]);
				table[field] = chronos::expand(field, table[field], begin, end);
			} else {
				// Read and check the command field.
				std::getline(expression, table[field]);
				txt::trim(table[field]);
				chronos::check(field, table[field]);
			}
		}
	} catch(const std::string& error) {
		// Report error and return failure as soon as we found an incorrect input.
		std::cerr << error << std::endl;
		return EXIT_FAILURE;
	}

	// Print all the fields in the order as they appear in the configuration vector (chronos::fields).
	for (auto& [field, begin, end]: chronos::fields) {
		std::cout << std::setw(14) << std::left << std::setfill(' ') 
			<< field << table[field] << std::endl;
	}

	return EXIT_SUCCESS;
}