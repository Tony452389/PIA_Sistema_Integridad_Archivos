#ifndef HASH_ENGINE_H
#define HASH_ENGINE_H

#include <string>
#include <iostream>

unsigned long generateHash(std::istream& dataStream);

unsigned long generateHash(const std::string& content);

#endif
