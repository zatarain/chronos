#include "text.hpp"

void txt::trim(std::string& text) {
	text.erase(text.begin(), std::find_if_not(text.begin(), text.end(), ::isspace));
	text.erase(std::find_if_not(text.rbegin(), text.rend(), ::isspace).base(), text.end());
}

void txt::uppercase(std::string& text) {
	std::transform(text.begin(), text.end(), text.begin(), ::toupper);
}

std::string txt::operator"" _m(const char* text, std::size_t length) {
	std::stringstream generated;
	generated << text << std::endl;
	return generated.str();
}