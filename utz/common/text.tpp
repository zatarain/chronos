#include <utz.hpp>
#include <vector>
#include <tuple>
#include <common/text.hpp>

void test_operator_literal_multiline_string() {
	// Arrange
	std::stringstream expected;
	expected << "Hello" << std::endl;
	using txt::operator""_m;

	// Act
	std::string actual = "Hello"_m;

	// Assert
	"Suffix _m adds the proper end-of-line mark to the string."
	| expect(actual, is::equal, expected.str());
}

std::vector<std::tuple<std::string, std::string, std::string>> testcases_trim{
	{"Test trim/remove spaces on the left.",   "   hello world", "hello world"},
	{"Test trim/remove spaces on the right.",  "hello world   ", "hello world"},
	{"Test trim/remove spaces on both sides.", " hello world  ", "hello world"},
	{"Test trim/remove any blank characters on both sides.", " \thello world\n ", "hello world"},
	{"Test no trim or unalterate text without blank characters on any side.", "hello world", "hello world"},
};

void test_trim() {
	for (auto& [description, input, expected]: testcases_trim) {
		txt::trim(input);
		description
		| expect(input, is::equal, expected);
	}
}

// Test cases considering only simple english alphabet characters.
std::vector<std::tuple<std::string, std::string, std::string>> testcases_uppercase{
	{"Test with all lower case letters to upper case letters.", "ulises", "ULISES"},
	{"Test with all upper case letters to be unalterated.", "ULISES", "ULISES"},
	{"Test with mix casing to be all upper case letters.", "Ulises Tirado Zatarain", "ULISES TIRADO ZATARAIN"},
};

void test_uppercase() {
	for (auto& [description, input, expected]: testcases_uppercase) {
		txt::uppercase(input);
		description
		| expect(input, is::equal, expected);
	}
}

void utz::test() {
	test_operator_literal_multiline_string();
	test_trim();
	test_uppercase();
}