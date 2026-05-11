/*
==========================================
Proyecto: Sistema de Integridad de Archivos (SIA)

Moduloo:
Baseline Manager

Responsable:
Josué Castro

Descripción:
Módulo encargado de la gestión del
baseline del sistema.

Funciones principales:

- Verificar existencia del baseline
- Guardar hash inicial
- Leer hash almacenado
- Preparar datos para comparación

Fecha:
Abril 2026
==========================================
*/

#include "baseline_manager.h"

#include <sqlite3.h>

#include <fstream>
#include <iostream>
#include <string>

bool baselineExists(const std::string& path){
    std::ifstream file(path);

    return file.good();
}

void saveBaseline(const std::string& path, unsigned long hash){
    std::ofstream file(path);

    if(!file.is_open()){
        std::cerr << "Error: No fue posible crear el Baseline."
                  << std::endl;
        
        return;
    }

    file << hash;

    file.close();

    std::cout << "Baseline creado."
              << std::endl;
}

unsigned long loadBaseline(const std::string& path){
    std::ifstream file(path);

    unsigned long storedHash = 0;

    if(!file.is_open()){
        std::cerr << "Error: No fue posible leer el baseline."
                  << std::endl;

        return 0;
    }

    file >> storedHash;

    file.close();

    return storedHash;
}

void initializeDatabase(){
    sqlite3* db;

    int result = sqlite3_open("data/baseline.db", &db);

    if(result != SQLITE_OK){
        std::cout << "Error initializing database."
                  << std::endl;
    
        return;
    }

    std::cout << "Database initialized successfully!"
              << std::endl;

    const char* createFilesTable = R"(
        CREATE TABLE IF NOT EXISTS Files (
            FileID INTEGER PRIMARY KEY AUTOINCREMENT,
            
            Name TEXT NOT NULL,

            FilePath TEXT NOT NULL
        );  
    )";

    const char* createBaselinesTable = R"(
        CREATE TABLE IF NOT EXISTS Baselines(
            BaselineID INTEGER PRIMARY KEY AUTOINCREMENT,

            FileID INTEGER,

            Hash TEXT NOT NULL,

            Timestamp TEXT NOT NULL,

            EventType TEXT NOT NULL,

            FOREIGN KEY(FileID)
            REFERENCES Files(FileID)
        );
    )";

    char* errorMessage = nullptr;

    result = sqlite3_exec(
        db,
        createFilesTable,
        nullptr,
        nullptr,
        &errorMessage
    );

    if(result != SQLITE_OK){
        std::cout << "Error creating Files table:"
                  << errorMessage
                  << std::endl;

        sqlite3_free(errorMessage);
    }
    else{
        std::cout << "Files table created successfully!"
                  << std::endl;
    }
    
    result = sqlite3_exec(
        db,
        createBaselinesTable,
        nullptr,
        nullptr,
        &errorMessage
    );

    if(result != SQLITE_OK){
        std::cout << "Error creating Baselines table:"
                  << errorMessage
                  << std::endl;

        sqlite3_free(errorMessage);
    }
    else{
        std::cout << "Baselines table created successfully!"
                  << std::endl;
    }

    sqlite3_close(db);

}

void insertFile(const std::string& name, const std::string& filePath){
    sqlite3* db;
    
    int result = sqlite3_open("data/baseline.db", &db);

    if(result != SQLITE_OK){
        std::cout << "Error opening database."
                  << std::endl;

        return;
    }

    std::string sql =
        "INSERT INTO Files (Name, FilePath) VALUES ('" +
        name +
        "', '" +
        filePath +
        "');";

    char* errorMessage = nullptr;

    result = sqlite3_exec(
        db,
        sql.c_str(),
        nullptr,
        nullptr,
        &errorMessage
    );

    if(result != SQLITE_OK){
        std::cout << "Error inserting file:"
                  << errorMessage
                  << std::endl;

        sqlite3_free(errorMessage);
    }
    else{
        std::cout << "File inserted successfully!"
                  << std::endl;
    }

    sqlite3_close(db);
}