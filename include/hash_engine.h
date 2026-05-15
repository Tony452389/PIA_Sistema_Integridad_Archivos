#ifndef HASH_ENGINE_H
#define HASH_ENGINE_H

#include <string>
#include <iostream>
#include <stdexcept>

enum class HashAlgorithm {
    ROLLING_HASH, 
    CRC32        
};

std::string generateHash(std::istream& dataStream, HashAlgorithm algo = HashAlgorithm::ROLLING_HASH);

#endif
