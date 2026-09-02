#include "enby.hpp"
#include <string>
#include <iostream>

int checkArgs(int ac, char **av) {
  if (ac == 1) {
    std::cout << "--- Performing Insertion ---\n";
    return 1;
  }

  std::string opt = av[1];
  if (opt == "u" || opt == "update") {
    std::cout << "--- Performing Updates ---\n";
    return 2;
  } else if (opt == "d" || opt == "delete") {
    std::cout << "--- Performing Deletion ---\n";
    return 3;
  } else if (opt == "s" || opt == "set") {
    if (ac != 4) {
      std::cerr << "Usage: HIT <set or s> <user or email> <value>\n";
      return 0;
    }
    std::string s_opt = av[2];
    if (s_opt == "user") {
      return 4;
    } else if (s_opt == "email") {
      return 5;
    }
    std::cerr << "Usage: HIT <set or s> <user or email> <value>\n";
    return 0;
  } else if (opt == "r" || opt == "reset") {
    if (ac == 2) {
      return 6;
    } else if (ac == 3) {
      std::string r_opt = av[2];
      if (r_opt == "user") {
        return 7;
      } else if (r_opt == "email") {
        return 8;
      }
    }
    std::cerr << "Usage: HIT <r or reset> <user or email or EMPTY>\n";
    return 0;
  }
  std::cerr << "#  Usage: HIT <option>                     #\n";
  std::cerr << "#  EMPTY -> insert headers                 #\n";
  std::cerr << "#  u or update -> update existing headers  #\n";
  std::cerr << "#  d or delete -> delete existing headers  #\n";
  std::cerr << "#  s or set -> <user> or <email>           #\n";
  std::cerr << "#   user <value> -> set user to <value>    #\n";
  std::cerr << "#   email <value> -> set email to <value>  #\n";
  std::cerr << "#  r or reset -> reset email and user      #\n";
  std::cerr << "#   user -> reset only user                #\n";
  std::cerr << "#   email -> reset only email              #\n";
  return 0;
}
