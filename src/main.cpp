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
	for(auto& [field, begin, size]: chronos::fields) {
		try {
			if (size > 0) {
				// Read and check the numeric field.
				expression >> table[field];
				chronos::check_not_empty(table[field]);
				table[field] = chronos::expand(table[field], begin, size);
			} else {
				// Read and check the command field.
				std::getline(expression, table[field]);
				txt::trim(table[field]);
				chronos::check_not_empty(table[field]);
			}
		} catch(const std::exception& error) {
			// Report error and return failure as soon as we found an incorrect input.
			char message[256];
			sprintf(message, error.what(), field.c_str(), table[field].c_str());
			std::cerr << message << std::endl;
			return EXIT_FAILURE;
		}
	}

	// Print all the fields in the order as they appear in the configuration vector (chronos::fields).
	for (auto& [field, begin, size]: chronos::fields) {
		std::cout << std::setw(chronos::width) << std::left << std::setfill(' ') 
			<< field << table[field] << std::endl;
	}

	return EXIT_SUCCESS;
}