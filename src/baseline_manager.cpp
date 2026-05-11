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

#include <ctime>
#include <iomanip>
#include <sstream>

//Callback de apoyo para capturar FileID
static int callbackFileID(
    void* data,
    int argc,
    char** argv,
    char** azColName
){
    if(argc > 0 && argv[0] != nullptr){
        *(static_cast < int* > (data)) = std::stoi(argv[0]);
    }

    return 0;
}

//Callback de apoyo para evitar duplicados en tabla Files
static int callbackFileExists(
    void* data,
    int argc,
    char** argv,
    char** azColName
){
    bool* exists = static_cast <bool*> (data);

    *exists = true;

    return 0;
}

//Callback de apoyo para obtener el ultimo Hash
static int callbackLastHash(
    void* data,
    int argc,
    char** argv,
    char** azColName
){
    if(argc > 0 && argv[0] != nullptr){
        *(static_cast <std::string*> (data)) = argv[0];
    }

    return 0;
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
        std::cout << "Error creating Files table: "
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
        std::cout << "Error creating Baselines table: "
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
        std::cout << "Error inserting file: "
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

int getFileID(const std::string& filePath){
    sqlite3* db;

    int result = sqlite3_open("data/baseline.db", &db);

    if(result != SQLITE_OK){
        std::cout << "Error opening database."
                  << std::endl;

        return -1;
    }

    int fileID = -1;

    std::string sql =
        "SELECT FileID FROM Files WHERE FilePath = '" +

        filePath +

        "';";

    char* errorMessage = nullptr;

    result = sqlite3_exec(
        db,
        sql.c_str(),
        callbackFileID,
        &fileID,
        &errorMessage
    );

    if(result != SQLITE_OK){
        std::cout << "Error retrieving FileID: "
                  << errorMessage
                  << std::endl;

        sqlite3_free(errorMessage);
    }

    sqlite3_close(db);

    return fileID;
}

bool fileExistsInDatabase(
    const std::string& filePath
){
    sqlite3* db;

    int result = sqlite3_open("data/baseline.db", &db);

    if(result != SQLITE_OK){
        std::cout << "Error opening database."
                  << std::endl;

        return false;
    }

    bool exists = false;

    std::string sql =
        "SELECT FileID FROM Files WHERE FilePath = '" +
        filePath +
        "' LIMIT 1;";

    char* errorMessage = nullptr;

    result = sqlite3_exec(
        db,
        sql.c_str(),
        callbackFileExists,
        &exists,
        &errorMessage
    );

    if(result != SQLITE_OK){
        std::cout << "Error checking file existence: "
                  << errorMessage
                  << std::endl;

        sqlite3_free(errorMessage);
    }

    sqlite3_close(db);

    return exists;
}

void insertBaseline(
    int fileID,
    const std::string& hash,
    const std::string& timestamp,
    const std::string& eventType
){
    sqlite3* db;

    int result = sqlite3_open("data/baseline.db", &db);

    if(result != SQLITE_OK){
        std::cout << "Error opening database."
                  << std::endl;

        return;
    }

    std::string sql = 
        "INSERT INTO Baselines "
        "(FileID, Hash, Timestamp, EventType) VALUES (" +
        
        std::to_string(fileID) +
        
        ", '" +

        hash +

        "', '" +

        timestamp +

        "', '" +
        
        eventType +

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
        std::cout << "Error inserting baseline: "
                  << errorMessage
                  << std::endl;

        sqlite3_free(errorMessage);
    }
    else{
        std::cout << "Baseline inserted successfully!"
                  << std::endl;
    }

    sqlite3_close(db);   
}

std::string getLastHash(int fileID){
    sqlite3* db;

    int result = sqlite3_open("data/baseline.db", &db);

    if(result != SQLITE_OK){
        std::cout << "Error opening database."
                  << std::endl;

        return "";
    }

    std::string lastHash = "";

    std::string sql =
        "SELECT Hash FROM Baselines "
        "WHERE FileID = " +

        std::to_string(fileID) +

        " ORDER BY BaselineID DESC LIMIT 1;";

    char* errorMessage = nullptr;

    result = sqlite3_exec(
        db,
        sql.c_str(),
        callbackLastHash,
        &lastHash,
        &errorMessage
    );

    if(result != SQLITE_OK){
        std::cout << "Error retrieving last hash: "
                  << errorMessage
                  << std::endl;

        sqlite3_free(errorMessage);
    }

    sqlite3_close(db);

    return lastHash;
}

std::string getCurrentTimestamp(){
    std::time_t now = std::time(nullptr);

    std::tm* localTime = std::localtime(&now);
    
    std::stringstream timestamp;

    timestamp << std::put_time(
        localTime,
        "%Y-%m-%d %H:%M:%S"
    );

    return timestamp.str();
}

