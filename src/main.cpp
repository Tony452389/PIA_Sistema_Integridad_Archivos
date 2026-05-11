/*
==========================================
Proyecto: Sistema de Integridad de Archivos (SIA)

Archivo:
main.cpp

Responsable:
Josué Castro

Descripción:
Archivo principal del sistema.
Coordina la ejecución de los módulos:
File Scanner, Hash Engine,
Baseline Manager y Risk Analyzer.

Responsable también de la integración
general del sistema.

Fecha:
Abril 2026
==========================================
*/

#include "file_scanner.h"
#include "hash_engine.h"
#include "baseline_manager.h"
#include "risk_analyzer.h"

#include <iostream>
#include <string>

#include <vector>

int main(){
    initializeDatabase();

    //Carga la lista de archivos desde targets.txt
    std::vector <std::string> targets = loadTargets("data/targets.txt");

    //Recorre cada archivo objetivo
    for(const auto& filePath : targets){
        std::cout << "\nProcessing: "
                  << filePath
                  << std::endl;

        //Verifica si el archivo existe fisicamente
        bool existsOnSystem = fileExistsOnSystem(filePath);

        //Verifica si el archivo existe en la DB
        bool existsOnDatabase = fileExistsInDatabase(filePath);

        //Verifica DELETED
        if(!existsOnSystem && existsOnDatabase){
            int fileID = getFileID(filePath);

            std::string lastHash = getLastHash(fileID);

            std::string timestamp = getCurrentTimestamp();

            insertBaseline(
                fileID,
                lastHash,
                timestamp,
                "DELETED"
            );

            std::cout << "Event: DELETED"
                      << std::endl;

            continue;
        }

        //Archivo inexistente y desconocido
        if(!existsOnSystem && !existsOnDatabase){
            std::cout << "File not found."
                      << std::endl;

            continue;
        }

        //Inserta Archivo si es nuevo
        if(!existsOnDatabase){
            insertFile(
                filePath,
                filePath
            );
        }

        //Obtiene FileID
        int fileID = getFileID(filePath);

        //Abre el archivo
        std::ifstream file = openFile(filePath);

        if(!file){
            std::cout << "Error opening file."
                      << std::endl;

            continue;
        }

        //Genera Hash actual
        std::string currentHash = generateHash(file);

        //Recupera ultimo Hash
        std::string lastHash = getLastHash(fileID);

        //Determina evento
        std::string eventType = determineEventType(currentHash, lastHash);

        //Obtiene timestamp
        std::string timestamp = getCurrentTimestamp();

        //Registra baseline
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

    return 0;
}