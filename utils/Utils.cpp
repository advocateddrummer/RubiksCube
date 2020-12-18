#include "Utils.hpp"

std::vector<std::string> StringSplit(const std::string str, char delim)
{
  std::vector<std::string> result;
  std::istringstream ss{str};
  std::string token;

  while (std::getline(ss, token, delim)) {
    if (!token.empty()) {
      result.push_back(token);
    }
  }

  return result;
}
