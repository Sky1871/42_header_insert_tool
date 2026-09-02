#include "enby.hpp"
#include <string>
#include <vector>
#include <fstream>

bool hasHeader(const std::string& filepath) {
  std::ifstream in(filepath);
  if (!in.is_open()) {
    return false;
  }

  std::string line;
  std::vector<std::string> lines;
  
  // Attempt to read the first 11 lines
  for (int i = 0; i < 11; ++i) {
    if (!std::getline(in, line)) {
      return false; // File has fewer than 11 lines, so no header
    }
    lines.push_back(line);
  }

  // Check if the specific lines contain the 42 header signatures
  bool hasBy      = lines[5].find("By: ") != std::string::npos;
  bool hasCreated = lines[7].find("Created: ") != std::string::npos;
  bool hasUpdated = lines[8].find("Updated: ") != std::string::npos;

  return hasBy && hasCreated && hasUpdated;
}
