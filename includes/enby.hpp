#ifndef ENBY_H
# define ENBY_H

#include <string>

std::string makeHeader(const std::string& filename, std::string existingCreated);
bool hasHeader(const std::string& filepath);
int checkArgs(int ac, char **av);
std::string readConfig(std::string key);
void updateConfig(const std::string& key, const std::string& value);

#endif
