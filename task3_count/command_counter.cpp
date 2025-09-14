#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

int main(int argc, char* argv[]) {
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
