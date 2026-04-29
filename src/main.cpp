#include "file_scanner.h"

#include <iostream>

int main(){
    std::string filePath = "data/test_file.txt";

    std::cout << "File: "
              << filePath
              << std::endl;

    std::cout << "Reading file..."
              << std::endl;

    std::string content = readFile(filePath);

    if(content.empty()){
        std::cout << "Failed to read the file."
                  << std::endl;
        
        return 1;
    }

    std::cout << "File read successfully."
              << std::endl;

    std::cout << "\nFile content:\n";

    std::cout << content
              << std::endl;

    return 0;
}