#include "enby.hpp"
#include <string>

void dataUpdate(int mode, char* str) {
  std::string value = str;
  if (mode == 4) { // SET USER
    updateConfig("USER", value);
  } else if (mode == 5) { // SET EMAIL
    updateConfig("EMAIL", value);
  } else if (mode == 6) { // RESET ALL
    updateConfig("USER", "");
    updateConfig("EMAIL", "");
    updateConfig("ROOT", "");
  } else if (mode == 7) { // RESET USER
    updateConfig("USER", "");
  } else if (mode == 8) { // RESET EMAIL
    updateConfig("EMAIL", "");
  } else if (mode == 9) { // SET ROOT
    updateConfig("ROOT", value);
  } else if (mode == 10) { // RESET ROOT
    updateConfig("ROOT", "");
  }
  return ;
}
