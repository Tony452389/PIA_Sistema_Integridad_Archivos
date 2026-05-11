#ifndef RISK_ANALYZER_H

#define RISK_ANALYZER_H

#include <string>

std::string determineEventType(
    const std::string& currentHash,
    const std::string& lastHash
);

bool isFileDeleted(
    const std::string& filePath,
    bool fileExistsonSystem
);

void processFile(const std::string& filePath);

#endif