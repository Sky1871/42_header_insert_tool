#include "enby.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
  std::string targetDir = "./target";

  for (const auto& entry : fs::directory_iterator(targetDir)) {
    if (!entry.is_regular_file()) {
      continue;
    }

    std::string inFile = entry.path().string();
    std::string tempFile = inFile + "_temp";

    std::string baseFilename = entry.path().filename().string();
    std::string header = makeHeader(baseFilename);

    std::ifstream in(inFile);
    if (!in.is_open()) {
      std::cerr << "Couldn't open input file: " << inFile << "\n";
      continue;
    }

    std::ofstream out(tempFile);
    if (!out.is_open()) {
      std::cerr << "Error opening temp file for: " << inFile << "\n";
      in.close();
      continue;
    }

    out << header << in.rdbuf();

    in.close();
    out.close();

    std::remove(inFile.c_str());
    std::rename(tempFile.c_str(), inFile.c_str());

    std::cout << "Succesfully processed: " << inFile << "\n";
  }
  return 1;
}
