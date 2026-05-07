/*
==========================================
Proyecto: Sistema de Integridad de Archivos (SIA)

Modulo:
Hash Engine

Responsable:
Marco Vargas

Descripción:
Módulo encargado de generar el hash
del contenido del archivo utilizando
un algoritmo de tipo rolling hash:

hash = hash * 31 + caracter

Fecha:
Abril 2026
==========================================
*/

#include "hash_engine.h"
#include <fstream>

unsigned long generateHash(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    unsigned long hash = 0;
    char c;

    // Procesamos el archivo carácter por carácter (o por bloques) 
    // sin cargarlo todo en un string gigante
    while (file.get(c)) {
        hash = hash * 31 + static_cast<unsigned char>(c); [cite: 11]
    }

    return hash;
}
