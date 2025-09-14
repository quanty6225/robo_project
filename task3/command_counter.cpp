#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <log_file_path>" << std::endl;
        return 1;
    }

    std::ifstream logFile(argv[1]);
    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    std::unordered_map<std::string, int> commandCounts;
    std::string line;
    while (std::getline(logFile, line)) {
        if (!line.empty()) {
            commandCounts[line]++;
        }
    }

    for (const auto& pair : commandCounts) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    logFile.close();
    return 0;
}
