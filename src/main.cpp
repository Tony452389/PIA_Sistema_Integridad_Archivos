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
#include <fstream>

int main(){
    initializeDatabase();

    std::string fileName = "config.txt";
    std::string filePath = "data/config.txt";

    //Verifica si el archivo ya existe en la tabla Files
    if(!fileExistsInDatabase(filePath)){
        insertFile(fileName, filePath);
    }

    //Obtiene FileID
    int fileID = getFileID(filePath);

    std::cout <<"FileID:" 
              << fileID
              << std::endl;
    
    //Abre el archivo para generar el Hash
    std::ifstream file(filePath);

    if(!file){
        std::cout << "Error opening file."
                  << std::endl;

        return 1;
    }

    //Generar Hash actual
    std::string currentHash = generateHash(file);

    std::cout <<"Current Hash:" 
              << currentHash
              << std::endl;

    //Obtener ultimo Hash registrado
    std::string lastHash = getLastHash(fileID);

    std::cout <<"Last Hash:" 
              << lastHash
              << std::endl;

    //parametros temporales
    std::string eventType = "NEW";
    std::string timestamp = "2026-05-10 02:00";

    
    insertBaseline(
        fileID,
        currentHash,
        timestamp,
        eventType
    );

    return 0;
}

    /*
    Main original de entrega 1

    d::string filePath = "data/test_file.txt";

    std::string baselinePath = "data/baseline.txt";

    std::cout << "File: "
              << filePath
              << std::endl;

    std::cout << "Leyendo el archivo..."
              << std::endl;

    std::string content = readFile(filePath);

    if(content.empty()){
        std::cout << "Falla en la lectura del Archivo."
                  << std::endl;
        
        return 1;
    }

    std::cout << "Generando Hash..."
              << std::endl;

    unsigned long currentHash = generateHash(content);
          
    std::cout << "Hash generado: "
              << currentHash
              << std::endl;

    if(!baselineExists(baselinePath)){
        std::cout << "Baseline no encontrado."
                  << std::endl;
        
        saveBaseline(baselinePath, currentHash);

        std::cout << "Status: SEGURO"
                  << std::endl;

        return 0;
    }

    std::cout << "Baseline encontrado."
                  << std::endl;

    unsigned long storedHash = loadBaseline(baselinePath);
    
    std::cout << "Comparando hashes..."
                  << std::endl;

    std::string status = analyzeRisk(currentHash, storedHash);


    std::cout << "Status: "
              << status
              << std::endl;
    */
