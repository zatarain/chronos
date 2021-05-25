#ifndef __TEXT_HEADER__
#define __TEXT_HEADER__

#include <string>
#include <cctype>
#include <algorithm>
#include <functional>
#include <sstream>

namespace txt {
	/**
	 * Suffix to add std::endl to the end of string literal (it doesn't support wchar-strings).
	 * 
	 * @param const char*	C-style string literal.
	 * @param std::size_t	Length of the string literal.
	 * @return std::string 	Object of type std::string with end-of-line mark at the end.
	 */
	std::string operator"" _m(const char*, std::size_t);

	/**
	 * Removes the blank characters at the start and end of a string text in-place.
	 * 
	 * @param std::string& Reference to the input text.
	 * @return void
	 */
	void trim(std::string&);

	/**
	 * Convert characters to upper case in a string text in-place.
	 * 
	 * @param std::string& Reference to the input text.
	 * @return void
	 */
	void uppercase(std::string&);
}

#endif // __TEXT_HEADER__
