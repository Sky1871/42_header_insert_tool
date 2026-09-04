#include "enby.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

const std::string CONFIG_PATH = "data/header_config";

std::string readConfig(std::string key) {
  std::ifstream file(CONFIG_PATH);
  if (!file.is_open()) return "";

  std::string line;
  std::transform(key.begin(), key.end(), key.begin(), ::toupper);
  while (std::getline(file, line)) {
    if (line.find(key + "=") == 0 && line.length() > (key.length() + 1)) {
      return line.substr(key.length() + 1);
    }
  }
  return "";
}

void updateConfig(const std::string& key, const std::string& value) {
  std::string user = readConfig("USER");
  std::string email = readConfig("EMAIL");
  std::string root = readConfig("ROOT");
  std::string exc_dir = readConfig("EXC_DIR");
  std::string ftype = readConfig("FTYPE");

  if (key == "USER") user = value;
  if (key == "EMAIL") email = value;
  if (key == "ROOT") root = value;
  if (key == "EXC_DIR") exc_dir = value;
  if (key == "FTYPE") ftype = value;

  std::ofstream file(CONFIG_PATH);
  if (file.is_open()) {
    file << "USER=" << user << "\n";
    file << "EMAIL=" << email << "\n";
    file << "ROOT=" << root << "\n";
    file << "EXC_DIR=" << exc_dir << "\n";
    file << "FTYPE=" << ftype << "\n";
    std::cout << "Succesfully updated " << key << " in config\n";
  } else {
    std::cerr << "Error: Could not open config file\n";
  }
}
