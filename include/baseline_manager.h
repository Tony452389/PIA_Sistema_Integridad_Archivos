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

std::string getLastHash(int fileID);

std::string getCurrentTimestamp();

void displayLatestBaselines();

#endif
