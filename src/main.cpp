#include "file_scanner.h"
#include "hash_engine.h"
#include "baseline_manager.h"
#include "risk_analyzer.h"

#include <iostream>
#include <vector>
#include <string>

int main(){

    int option;

    std::cout << std::endl;

    std::cout << "===== File Integrity Monitor ====="
              << std::endl;

    std::cout << std::endl;

    std::cout << "1. Run Monitor"
              << std::endl;

    std::cout << "2. Restore Test Environment"
              << std::endl;

    std::cout << "3. Exit"
              << std::endl;

    std::cout << std::endl;

    std::cout << "Select an option: ";

    std::cin >> option;

    std::cout << std::endl;

    switch(option){

        case 1: {

            initializeDatabase();

            std::vector<std::string> targets =
                loadTargets("data/targets.txt");

            for(const auto& filePath : targets){

                processFile(filePath);
            }

            displayLatestBaselines();

            break;
        }

        case 2: {

            restoreTestEnvironment();

            break;
        }

        case 3: {

            std::cout << "Exiting program."
                      << std::endl;

            break;
        }

        default: {

            std::cout << "Invalid option."
                      << std::endl;

            break;
        }
    }

    return 0;
}