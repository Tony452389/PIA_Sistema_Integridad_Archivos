/*
==========================================
Proyecto: Sistema de Integridad de Archivos (SIA)

Modulo:
File Scanner

Responsable:
Ricardo Estrada

Descripción:
Módulo encargado de la lectura del
contenido del archivo objetivo.

Verifica la existencia del archivo
y retorna su contenido como string.

Fecha:
Abril 2026
==========================================
*/

#include "file_scanner.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <vector>

#include <filesystem>

bool fileExistsOnSystem(const std::string& filePath){
    std::ifstream file(filePath);

    return file.good();
}

std::ifstream openFile(const std::string& filePath){
        std::ifstream file(filePath);

        return file;
}

std::vector <std::string> loadTargets(const std::string& targetsPath){
    std::vector <std::string> targets;

    std::ifstream file(targetsPath);

    if(!file){
        std::cout << "Error opening targets file."
                  << std::endl;
        
        return targets;
    }

    std::string line;
    
    while(std::getline(file, line)){
        if(!line.empty()){
            targets.push_back(line);
        }
    }

    return targets;
}

void restoreTestEnvironment(){
    //Elimina la base de datos
    std::string databasePath =
        "data/baseline.db";

    if(std::filesystem::exists(databasePath)){

        std::filesystem::remove(databasePath);
    }

    // Elimina archivos de prueba
    std::filesystem::remove("data/config.txt");
    std::filesystem::remove("data/notes.txt");
    std::filesystem::remove("data/system.conf");
    std::filesystem::remove("data/temp.log");
    std::filesystem::remove("data/targets.txt");

    //Recrea config.txt
    std::ofstream configFile(
        "data/config.txt"
    );

    configFile
        << "system_mode=production\n"
        << "max_connections=32\n";

    configFile.close();

    //Recrea notes.txt
    std::ofstream notesFile(
        "data/notes.txt"
    );

    notesFile
        << "Initial monitoring notes.\n";

    notesFile.close();

    //Recrea system.conf
    std::ofstream systemFile(
        "data/system.conf"
    );

    systemFile
        << "enable_logs=true\n"
        << "monitor_level=high\n";

    systemFile.close();

    //Recrea temp.log
    std::ofstream tempFile(
        "data/temp.log"
    );

    tempFile
        << "Temporary log initialized.\n";

    tempFile.close();

    //Recrea targets.txt
    std::ofstream targetsFile(
        "data/targets.txt"
    );

    targetsFile
        << "data/config.txt\n"
        << "data/notes.txt\n"
        << "data/system.conf\n"
        << "data/temp.log\n";

    targetsFile.close();

    std::cout << std::endl;

    std::cout << "Test environment restored successfully."
              << std::endl;
}