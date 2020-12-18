#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>
#include <vector>

/** \brief Split std::string by specified delimiter
 *
 * This utility splits the input string into tokens or words based on a
 * specified delimiter. This function properly handles/compresses repeated
 * delimiters. Shamelessly copy-pasted from:
 * https://www.systutorials.com/how-to-split-and-iterate-a-string-separated-by-another-string-in-c/
 *
 * \param[in] str the string to be split.
 * \param[in] delim the delimiter to split str by.
 */
std::vector<std::string> StringSplit(const std::string str, char delim);

#endif /* end of include guard: UTILS_HPP */
