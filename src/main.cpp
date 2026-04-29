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

int main(){
    std::string filePath = "data/test_file.txt";

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

    return 0;
}