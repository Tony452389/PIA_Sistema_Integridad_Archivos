#include "file_scanner.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::string readFile(const std::string& filePath){
    std::ifstream file (filePath);

    if(!file.is_open()){
        std::cerr << "Error: Could not open file: "
                  << filePath << std::endl;

        return "";          
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    file.close();

    return buffer.str();
}


