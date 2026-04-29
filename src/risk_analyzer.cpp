/*
==========================================
Proyecto: Sistema de Integridad de Archivos (SIA)

Modulo:
Rysk Analyzer

Responsable:
Sergio Sepulveda

Descripción:
Módulo encargado de analizar el
resultado de la comparación entre
hashes.

Determina el estado del archivo:

SAFE      → Sin modificaciones
MODIFIED  → Archivo alterado

Fecha:
Abril 2026
==========================================
*/

#include "risk_analyzer.h"

std::string analyzeRisk(unsigned long currentHash, unsigned long storedHash){
    if(currentHash == storedHash){
        return "SEGURO";

    }
    else{ 
        return "MODIFICADO";
    }
}