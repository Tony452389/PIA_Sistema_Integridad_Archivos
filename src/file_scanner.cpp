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


