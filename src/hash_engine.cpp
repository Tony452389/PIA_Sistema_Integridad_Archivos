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

std::string generateHash(std::istream& dataStream) {
    unsigned long hash = 0;
    const size_t BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE];

    while (dataStream.read(buffer, BUFFER_SIZE) || dataStream.gcount() > 0) {
        for (std::streamsize i = 0; i < dataStream.gcount(); ++i) {
            hash = hash * 31 + static_cast<unsigned char>(buffer[i]);
        }
    }

    // Conversión a std::string antes de retornar
    return std::to_string(hash);
}
