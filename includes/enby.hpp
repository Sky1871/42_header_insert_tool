#ifndef ENBY_H
# define ENBY_H

#include <string>

std::string makeHeader(const std::string& filename, std::string existingCreated = "");
bool hasHeader(const std::string& filepath);
int checkArgs(int ac, char **av);

#endif
