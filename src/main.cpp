#include "file_scanner.h"
#include "hash_engine.h"

#include <iostream>

int main(){
    std::string filePath = "data/test_file.txt";

    std::cout << "File: "
              << filePath
              << std::endl;

    std::cout << "Leyendo el archivo..."
              << std::endl;

    std::string content = readFile(filePath);

    if(content.empty()){
        std::cout << "Falla en la lectura del Archivo."
                  << std::endl;
        
        return 1;
    }

    std::cout << "Generando Hash..."
              << std::endl;

    unsigned long hash = generateHash(content);
          
    std::cout << "Hash generado: "
              << hash
              << std::endl;

    return 0;
}