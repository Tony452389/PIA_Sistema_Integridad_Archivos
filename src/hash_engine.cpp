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

unsigned long generateHash(const std::string& content){
    unsigned long hash = 0;
    
    for(char c : content){
        hash = hash *31 + c;
    }

    return hash;
}