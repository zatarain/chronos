#include <utz.hpp>
#include <vector>
#include <tuple>
#include <common/parser.hpp>

std::vector<std::tuple<std::string, std::string, std::string>> testcases_check_not_empty{
    {"Test with a non empty string shouldn't throw any exception.", "Non-empty text", ""},
    {"Test with a non empty string (even with blank characters) shouldn't throw any exception.", " \t\n", ""},
    {"Test with an empty string must throw any exception.", "", "Error: The field '%s' is empty!"},
};

void test_check_not_empty() {
    for (auto& [description, text, expected]: testcases_check_not_empty) {
        std::string actual;
        try {
            chronos::check_not_empty(text);
        } catch (std::exception& error) {
            actual = error.what();
        }
        description
        | expect(actual, is::equal, expected);
    }
}

std::vector<std::tuple<std::string, int, int, int, std::string>> testcases_check_range{
    {"Test with a valid value in range (0-based).", 5, 0, 10, ""},
    {"Test with a valid value in range (1-based).", 10, 1, 10, ""},
    {"Test with an invalid value out of range (0-based).", 10, 0, 10, 
        "Error: The field '%s' must have a value between 0 and 10 (exclusive), we found '10'!"},
    {"Test with an invalid value out of range (1-based).", 11, 1, 10, 
        "Error: The field '%s' must have a value between 1 and 10 (inclusive), we found '11'!"},
};

void test_check_range() {
    for (auto& [description, value, begin, size, expected]: testcases_check_range) {
        std::string actual;
        try {
            chronos::check_range(value, begin, size);
        } catch (std::exception& error) {
            actual = error.what();
        }
        description
        | expect(actual, is::equal, expected);
    }
}

void utz::test() {
    test_check_not_empty();
    test_check_range();
}
