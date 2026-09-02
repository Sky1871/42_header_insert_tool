#include "enby.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char **argv) {
  int mode = checkArgs(argc, argv);
  if (mode == 0) {
    return 1;
  }

  if (mode >= 4 && mode <= 8) {
    if (mode == 4) { // SET USER
      updateConfig("USER", argv[3]);
    } else if (mode == 5) { // SET EMAIL
      updateConfig("EMAIL", argv[3]);
    } else if (mode == 6) { // RESET ALL
      updateConfig("USER", "");
      updateConfig("EMAIL", "");
    } else if (mode == 7) { // RESET USER
      updateConfig("USER", "");
    } else if (mode == 8) { // RESET EMAIL
      updateConfig("EMAIL", "");
    }
    return 0;
  }

  std::string targetDir = "./target";

  for (const auto& entry : fs::directory_iterator(targetDir)) {
    if (!entry.is_regular_file()) {
      continue;
    }

    std::string inFile = entry.path().string();
    std::string tempFile = inFile + "_temp";

    bool headerExists = hasHeader(inFile);
    std::string baseFilename = entry.path().filename().string();

    std::ifstream in(inFile);
    if (!in.is_open()) {
      std::cerr << "Couldn't open input file: " << inFile << "\n";
      continue;
    }

    std::ofstream out(tempFile);

    if (mode == 1) {
      /* INSERT */
      if (headerExists) {
        std::cout << "skipping: " << inFile << " (header already exists)\n";
        continue;
      }
      out << makeHeader(baseFilename, "") << in.rdbuf();

    } else if (mode == 2) {
      /* UPDATE */
      if (!headerExists) {
        std::cout << "skipping: " << inFile << " (no header to update)\n";
        continue;
      }

      std::string line, existingCreated;
      for (int i = 0; i < 11; i++) {
        std::getline(in, line);
        if (i == 7) {
          size_t start = line.find("Created: ");
          size_t end = line.find("by ", start);
          if (start != std::string::npos && end != std::string::npos) {
            size_t endOfUser = line.find(' ', end + 3);
            if (endOfUser != std::string::npos) {
              existingCreated = line.substr(start, endOfUser - start);
            }
          }
        }
      }
      out << makeHeader(baseFilename, existingCreated) << in.rdbuf();

    } else if (mode == 3) {
      /* DELETE */
      if (!headerExists) {
        std::cout << "skipping: " << inFile << " (no header to delete)\n";
        continue;
      }

      std::string dump;
      for (int i = 0; i < 12; ++i) {
        std::getline(in, dump);
      }
      out << in.rdbuf();
    }

    in.close();
    out.close();

    std::remove(inFile.c_str());
    std::rename(tempFile.c_str(), inFile.c_str());

    std::cout << "Succesfully processed: " << inFile << "\n";
  }
  return 0;
}
