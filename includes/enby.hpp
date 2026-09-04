#ifndef ENBY_H
# define ENBY_H

#include <string>
#include <vector>

std::string makeHeader(const std::string& filename, std::string existingCreated);
bool hasHeader(const std::string& filepath);
int checkArgs(int ac, char **av);
std::string readConfig(std::string key);
void updateConfig(const std::string& key, const std::string& value);
std::vector<std::string> parser(std::string str);
void dataUpdate(int mode, char* str);

#endif
