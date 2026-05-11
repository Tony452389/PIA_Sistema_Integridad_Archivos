/*
==========================================
Proyecto: Sistema de Integridad de Archivos (SIA)

Modulo:
File Scanner

Responsable:
Ricardo Estrada

Descripción:
Módulo encargado de la lectura del
contenido del archivo objetivo.

Verifica la existencia del archivo
y retorna su contenido como string.

Fecha:
Abril 2026
==========================================
*/

#include "file_scanner.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <vector>

bool fileExistsOnSystem(const std::string& filePath){
    std::ifstream file(filePath);

    return file.good();
}

std::ifstream openFile(const std::string& filePath){
        std::ifstream file(filePath);

        return file;
}

std::vector <std::string> loadTargets(const std::string& targetsPath){
    std::vector <std::string> targets;

    std::ifstream file(targetsPath);

    if(!file){
        std::cout << "Error opening targets file."
                  << std::endl;
        
        return targets;
    }

    std::string line;
    
    while(std::getline(file, line)){
        if(!line.empty()){
            targets.push_back(line);
        }
    }

    return targets;
}

