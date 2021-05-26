#ifndef __PARSER_HEADER__
#define __PARSER_HEADER__

#include <algorithm>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <regex>

namespace chronos {
	/**
	 * Width for each field name at the output. 
	 */
	inline const int width = 14;

	/**
	 *	Configuration vector of tuples with field names, first value and range size.
	 */
	inline const std::vector<std::tuple<std::string, int, int>> fields{
		{"minute", 0, 60},
		{"hour", 0, 24},
		{"day of month", 1, 31},
		{"month", 1, 12},
		{"day of week", 1, 7},
		{"command", 0, 0},
	};

	/**
	 *	Checks whether the field is empty, if so throws an exception. 
	 */
	void check(const std::string&, const std::string&);

	/**
	 * Generates a sequence in the interval [begin, end) doing steps.
	 * 
	 * @param int			Begin of the sequence.
	 * @param int			End of the sequence.
	 * @param int			Optional. Step of the sequence, by default is 1.
	 * @returns std::string	Space-separated text of the representation of the generated sequence.
	 */
	std::string sequence(int, int, int = 1);
	
	/**
	 * Returns a space-separated list with all possible values of a field.
	 * 
	 * @param std::smatch&	Parsed field value from the user input (regular expression matches).
	 * @param int			First valid value for the field (normally 0 or 1).
	 * @param int			Size of maximun range of the field (i.e. 60 for minutes).
	 * @return std::string	An expanding string representing the expression.
	 * @throws std::out_of_range
	 */
	std::string all(std::smatch&, int, int);

	/**
	 * Returns a space-separated list with all possible values of a field.
	 * 
	 * @param std::smatch&	Parsed field value from the user input (regular expression matches).
	 * @param int			First valid value for the field (normally 0 or 1).
	 * @param int			Size of maximun range of the field (i.e. 60 for minutes).
	 * @return std::string	An expanding string representing the expression.
	 * @throws std::out_of_range
	 */
	std::string each(std::smatch&, int, int);

	/**
	 * Returns a space-separated list with values in a range.
	 * 
	 * @param std::smatch&	Parsed field value from the user input (regular expression matches).
	 * @param int			First valid value for the field (normally 0 or 1).
	 * @param int			Size of maximun range of the field (i.e. 60 for minutes).
	 * @return std::string	An expanding string representing the expression.
	 * @throws std::out_of_range
	 */
	std::string range(std::smatch&, int, int);

	/**
	 * Returns a space-separated list with values in the input matches.
	 * 
	 * @param std::smatch&	Parsed field value from the user input (regular expression matches).
	 * @param int			First valid value for the field (normally 0 or 1).
	 * @param int			Size of maximun range of the field (i.e. 60 for minutes).
	 * @return std::string	An expanding string representing the expression.
	 * @throws std::out_of_range
	 */
	std::string list(std::smatch&, int, int);

	/**
	 * Returns a single fixed value.
	 * 
	 * @param std::smatch&	Parsed field value from the user input (regular expression matches).
	 * @param int			First valid value for the field (normally 0 or 1).
	 * @param int			Size of maximun range of the field (i.e. 60 for minutes).
	 * @return std::string	An expanding string representing the expression.
	 * @throws std::out_of_range
	 */
	std::string fixed(std::smatch&, int, int);
	
	/**
	 * Type for the generator callback function after parse the user input with regex.
	 */
	using generator = std::function<std::string(std::smatch&, int, int)>;
	
	/**
	 * Configuration map for the patterns and their callback generator functions.
	 */
	inline const std::unordered_map<std::string, generator> patterns{
		{"^\\*$", all},
		{"^\\*/([0-9]+)$", each},
		{"^([0-9]+)-([0-9]+)$", range},
		{"^([0-9]+)(,([0-9]+))+$", list},
		{"^([0-9]+)$", fixed},
	};

	/**
	 * Expands a numeric cron-expression depending of the pattern matching.
	 * 
	 * @param const std::string&	Field name.
	 * @param const std::string&	Field value from the user input.
	 * @param int					First valid value for the field (normally 0 or 1).
	 * @param int					Size of maximun range of the field (i.e. 60 for minutes).
	 * @return std::string			An expanding string representing the expression.
	 */
	std::string expand(const std::string&, const std::string&, int, int);
}

#endif // __PARSER_HEADER__