#include "parser.hpp"

void chronos::check_not_empty(const std::string& value) {
	if (value.size() == 0) {
		throw std::invalid_argument("Error: The field '%s' is empty!");
	}
}

std::string chronos::sequence(int begin, int end, int step) {
	std::stringstream output;
	output << begin;
	for (int value = begin + step; value < end; value += step) {
		output << ' ' << value;
	}
	return output.str();
}

std::string chronos::all(std::smatch& matches, int begin, int end) {
	return sequence(begin, end + begin);
}

std::string chronos::each(std::smatch& matches, int begin, int end) {
	int step = std::stoi(matches[1].str());
	return sequence(begin, end, step);
}

std::string chronos::range(std::smatch& matches, int begin, int end) {
	int start = std::stoi(matches[1].str());
	int finish = std::stoi(matches[2].str());
	return sequence(start, finish + 1);
}

std::string chronos::list(std::smatch& matches, int begin, int end) {
	std::string text = matches.str();
	std::replace(text.begin(), text.end(), ',', ' ');
	return text;
}

std::string chronos::fixed(std::smatch& matches, int begin, int end) {
	return matches.str();
}

std::string chronos::expand(const std::string& value, int begin, int end) {
	for (auto& [pattern, callback]: patterns) {
		std::regex expression(pattern);
		std::smatch matches;
		if (std::regex_match(value, matches, expression)) {
			return callback(matches, begin, end);
		}
	}

	throw std::invalid_argument("Error: Invalid value for field '%s' we found '%s'!");
}
