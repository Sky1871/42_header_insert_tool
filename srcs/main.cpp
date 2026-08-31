/* #include "enby.hpp" */
#include <fstream>
#include <iostream>

int main() {
  std::ofstream file("test");
  if (!file.is_open()) {
    std::cerr << "Couldn't open file";
    return 1;
  } else {
    file << "test";
    file.close();
  }
  return 0;
}
