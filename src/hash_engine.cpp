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
#include <stdexcept>

std::string generateHash(std::istream& dataStream) {
    if (!dataStream) {
        throw std::runtime_error("Error: El flujo de datos no es válido o el archivo es inaccesible.");
    }

    unsigned long hash = 0;
    const size_t BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE];

    try {
        while (dataStream.read(buffer, BUFFER_SIZE) || dataStream.gcount() > 0) {
            for (std::streamsize i = 0; i < dataStream.gcount(); ++i) {
                hash = hash * 31 + static_cast<unsigned char>(buffer[i]);
            }
        }
    } catch (const std::exception& e) {
        return "ERROR_HASH_CONSISTENCY"; // Validación de consistencia
    }

    return std::to_string(hash);
}
