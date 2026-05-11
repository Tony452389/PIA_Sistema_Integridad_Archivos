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
#include "file_scanner.h"
#include "hash_engine.h"

#include <iostream>
#include <fstream>

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

void processFile(
    const std::string& filePath
){

    std::cout << "\nProcessing: "
              << filePath
              << std::endl;

    // Verificar existencia física

    bool existsOnSystem =
        fileExistsOnSystem(filePath);

    // Verificar existencia en DB

    bool existsInDatabase =
        fileExistsInDatabase(filePath);

    // Caso DELETED

    if(!existsOnSystem && existsInDatabase){

        int fileID = getFileID(filePath);

        std::string lastHash =
            getLastHash(fileID);

        std::string timestamp =
            getCurrentTimestamp();

        insertBaseline(
            fileID,
            lastHash,
            timestamp,
            "DELETED"
        );

        std::cout << "Event: DELETED"
                  << std::endl;

        return;
    }

    // Archivo inexistente y desconocido

    if(!existsOnSystem && !existsInDatabase){

        std::cout << "File not found."
                  << std::endl;

        return;
    }

    // Insertar archivo si es nuevo

    if(!existsInDatabase){

        insertFile(
            filePath,
            filePath
        );
    }

    // Obtener FileID

    int fileID = getFileID(filePath);

    // Abrir archivo

    std::ifstream file =
        openFile(filePath);

    if(!file){

        std::cout << "Error opening file."
                  << std::endl;

        return;
    }

    // Generar hash actual

    std::string currentHash =
        generateHash(file);

    // Recuperar último hash

    std::string lastHash =
        getLastHash(fileID);

    // Determinar evento

    std::string eventType =
        determineEventType(
            currentHash,
            lastHash
        );

    // Obtener timestamp

    std::string timestamp =
        getCurrentTimestamp();

    // Registrar baseline

    insertBaseline(
        fileID,
        currentHash,
        timestamp,
        eventType
    );

    std::cout << "Event: "
              << eventType
              << std::endl;
}