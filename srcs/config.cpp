#include "enby.hpp"
#include <fstream>
#include <iostream>
#include <string>

const std::string CONFIG_PATH = "data/header_config";

void readConfig(std::string& user, std::string& email) {
  std::ifstream file(CONFIG_PATH);
  if (!file.is_open()) return ;

  std::string line;
  while (std::getline(file, line)) {
    if (line.find("USER=") == 0 && line.length() > 5) {
      user = line.substr(5);
    } else if (line.find("EMAIL=") == 0 && line.length() > 6) {
      email = line.substr(6);
    }
  }
}

void updateConfig(const std::string& key, const std::string& value) {
  std::string user = "", email = "";
  readConfig(user, email);

  if (key == "USER") user = value;
  if (key == "EMAIL") email = value;

  std::ofstream file(CONFIG_PATH);
  if (file.is_open()) {
    file << "USER=" << user << "\n";
    file << "EMAIL=" << email << "\n";
    std::cout << "Succesfully updated " << key << " in config\n";
  } else {
    std::cerr << "Error: Could not open config file\n";
  }
}
