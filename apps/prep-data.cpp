#include <fstream>
#include <iostream>
#include <sstream>
#include "../src/util/util.h"

using std::string;
using std::stringstream;
using namespace wikigraph;

int main(int argc, char *argv[]) {
    log(string("[!] Preparing test data [!]"), true);

    // Number of Expected arguments
    int NUM_ARGS = 4;
    if (argc != NUM_ARGS + 1) {
        err(string("Incorrect syntax, Use ./prep-data [low_bound_inclusive] "
                   "[upper_bound_inclusive] [data_file.txt] [output_file.txt]"));
        return 1;
    }

    // Parse bounds
    stringstream lower_str(argv[1]);
    stringstream upper_str(argv[2]);
    int lower, upper;
    lower_str >> lower;
    upper_str >> upper;

    // Check file state and permissions
    if (!file_exists(argv[3])) {
        err(string("Data file not found :("));
        return 1;
    }
    std::ifstream dataFile(argv[3]);
    std::ofstream outputFile(argv[4]);
    if (!dataFile.is_open()) {
        err(string("Data file could not be opened :("));
        return 1;
    }
    if (!outputFile.is_open()) {
        err(string("Output file could not be created :("));
        return 1;
    }
    log(string("[!] Located files :D"), true);
    // Read lines
    int dataCounter = 0, finalCounter = 0;
    string line;
    while (getline(dataFile, line)) {
        // Ignore Comments
        if (line[0] == '#')
            continue;

        stringstream stream(line);
        int first, second;
        stream >> first;
        stream >> second;
        dataCounter++;
        if (isValid(lower, upper, first) && isValid(lower, upper, second)) {
            // Print to output
            finalCounter++;
            outputFile << line << std::endl;
        }
    }
    outputFile.close();
    dataFile.close();

    log(string("[!] Done."), true);
    std::cout << "Reduced data from " << dataCounter << " to " << finalCounter
              << " lines.\n";
    return 0;
}
