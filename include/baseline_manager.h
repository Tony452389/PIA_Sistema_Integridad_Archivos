#ifndef BASELINE_MANAGER_H

#define BASELINE_MANAGER_H

#include <string>

//Verifica si el baseline existe
bool baselineExists(const std::string& path);

//Guarda el hash como baseline
void saveBaseline(const std::string& path, unsigned long hash);

//Lee el hash desde el baseline
unsigned long loadBaseline(const std::string& path);

#endif
