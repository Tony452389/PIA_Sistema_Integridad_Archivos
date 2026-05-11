#ifndef FILE_SCANNER_H

#define FILE_SCANNER_H

#include <string>
#include <fstream>

#include <vector>

#include <filesystem>

bool fileExistsOnSystem(const std::string& filePath);

std::ifstream openFile(const std::string& filePath);

std::vector <std::string> loadTargets(const std::string& targetsPath);

void restoreTestEnvironment();
#endif