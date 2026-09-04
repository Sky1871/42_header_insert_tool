#include "enby.hpp"
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> parser(std::string str) {
  char sep = ',';
  std::vector<std::string> tokens;
  std::string token;
  std::stringstream ss(str);

  while (std::getline(ss, token, sep)) {
    tokens.push_back(token);
  }
  return tokens;
}
