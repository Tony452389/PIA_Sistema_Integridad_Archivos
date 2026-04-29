#ifndef RISK_ANALYZER_H

#define RISK_ANALYZER_H

#include <string>

//Determina el estado del archivo
std::string analyzeRisk(unsigned long currentHash,
                        unsigned long storedHash);

#endif