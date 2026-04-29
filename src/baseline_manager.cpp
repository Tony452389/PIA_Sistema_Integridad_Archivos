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

#include <fstream>
#include <iostream>

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