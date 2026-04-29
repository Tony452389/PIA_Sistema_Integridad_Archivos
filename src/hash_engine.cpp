#include "hash_engine.h"

unsigned long generateHash(const std::string& content){
    unsigned long hash = 0;
    
    for(char c : content){
        hash = hash *31 + c;
    }

    return hash;
}