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
#include "baseline_manager.h"

std::string determineEventType(
    const std::string& currentHash,
    const std::string& lastHash
){

    if(lastHash.empty()){

        return "NEW";
    }

    if(currentHash == lastHash){

        return "UNCHANGED";
    }

    return "MODIFIED";
}

bool isFileDeleted(
    const std::string& filePath,
    bool fileExistsOnSystem
){
    if(!fileExistsOnSystem && fileExistsInDatabase(filePath)){
        
        return true;
    }

    return false;
}