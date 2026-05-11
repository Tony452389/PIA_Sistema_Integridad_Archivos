#ifndef BASELINE_MANAGER_H

#define BASELINE_MANAGER_H

#include <string>

//Verifica si el baseline existe
bool baselineExists(const std::string& path);

//Guarda el hash como baseline
void saveBaseline(const std::string& path, unsigned long hash);

//Lee el hash desde el baseline
unsigned long loadBaseline(const std::string& path);

//Funcion temporal para crear DB
void initializeDatabase();

//Funcion para insertar los archivos en la tabla Files
void insertFile(
    const std::string& name,
    const std::string& filePath
);

//Funcion para obtener el FileID
int getFileID(const std::string& filePath);

//Funcion para evitar duplicados en tabla Files
bool fileExistsInDatabase(const std::string& filePath);

//Funcion para insertar eventos en la tabla Baselines
void insertBaseline(
    int fileID,
    const std::string& hash,
    const std::string& timestamp,
    const std::string& eventType
);

#endif

/*
 initializeDatabase();

     if(!fileExistsInDatabase("data/notes.txt")){
        insertFile("notes.txt", "data/notes.txt");
    }

    if(!fileExistsInDatabase("data/config.txt")){
        insertFile("config.text", "data/config.txt");
    }

    if(!fileExistsInDatabase("data/system.conf")){
        insertFile("system.conf", "data/system.conf");
    }

    if(!fileExistsInDatabase("data/temp.log")){
        insertFile("temp.log", "data/temp.log");
    }

    int fileID = getFileID("data/config.txt");

    insertBaseline(
        fileID,
        "123456789",
        "2026-05-10 15:00",
        "NEW"
    );

    return 0;
    */