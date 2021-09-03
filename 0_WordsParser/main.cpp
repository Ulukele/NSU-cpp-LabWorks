#include "WordsParser.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    if (argc != 3) {
        std::cout << "Invalid usage...\nExample:\n\t./main input.txt output.csv";
        return 0;
    }

    // Parse filenames
    std::string inputFilename = (std::string)argv[1];
    std::string outputFilename = (std::string)argv[2];

    WordsParser* wp = new WordsParser(
        inputFilename,
        outputFilename
    );
    wp->ParseFile();
    wp->WriteToCSV();
}