#include "parser.hpp"

void chronos::check_not_empty(const std::string& value) {
	if (value.size() == 0) {
		throw std::invalid_argument("Error: The field '%s' is empty!");
	}
}

void chronos::check_range(int value, int begin, int size) {
	if (value < begin || value >= size + begin) {
		std::stringstream message;
		message << "Error: The field '%s' must have a value between " << begin << " and " << size
			<< " (" << (begin ? "inclusive" : "exclusive" ) << "), we found '" << value << "'!";
		throw std::out_of_range(message.str().c_str());
	}
}

std::string chronos::sequence(int begin, int end, int step) {
	std::stringstream output;
	for (int value = begin; value < end; value += step) {
		output << (value > begin ? " " : "") << value;
	}
	return output.str();
}

std::string chronos::all(std::smatch& matches, int begin, int size) {
	return sequence(begin, size + begin);
}

std::string chronos::each(std::smatch& matches, int begin, int size) {
	int step = std::stoi(matches[1].str());
	if (step > 0 && size % step != 0) {
		throw std::invalid_argument("Error: Invalid frequency on field '%s' we found '%s'!");
	}
	return sequence(begin, size, step);
}

std::string chronos::range(std::smatch& matches, int begin, int size) {
	int start = std::stoi(matches[1].str());
	int finish = std::stoi(matches[2].str());
	if (finish < start) {
		throw std::out_of_range("Error: Invalid range for field '%s' we found '%s'!");
	}
	check_range(start, begin, size);
	check_range(finish, begin, size);
	return sequence(start, finish + 1);
}

std::string chronos::list(std::smatch& matches, int begin, int size) {
	std::string text = matches.str();
	std::replace(text.begin(), text.end(), ',', ' ');
	std::stringstream values(text);
	int value;
	while (values >> value)	{
		check_range(value, begin, size);	
	}	
	return text;
}

std::string chronos::fixed(std::smatch& matches, int begin, int size) {
	int value = std::stoi(matches.str());
	check_range(value, begin, size);
	return matches.str();
}

std::string chronos::expand(const std::string& value, int begin, int size) {
	for (auto& [pattern, callback]: patterns) {
		std::regex expression(pattern);
		std::smatch matches;
		if (std::regex_match(value, matches, expression)) {
			return callback(matches, begin, size);
		}
	}

	throw std::invalid_argument("Error: Invalid value for field '%s' we found '%s'!");
}
