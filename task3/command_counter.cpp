#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <log_file_path>" << endl;
        return 1;
    }

    ifstream logFile(argv[1]);
    unordered_map<string, int> commandCounts;
    string line;

    while (getline(logFile, line)) {
        if (!line.empty()) {
            commandCounts[line]++;
        }
    }

    for (const auto& pair : commandCounts) {
        cout << pair.first << ": " << pair.second << endl;
    }

    logFile.close();
    return 0;
}
