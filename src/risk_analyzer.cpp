#include "risk_analyzer.h"

std::string analyzeRisk(unsigned long currentHash, unsigned long storedHash){
    if(currentHash == storedHash){
        return "SEGURO";

    }
    else{ 
        return "MODIFICADO";
    }
}