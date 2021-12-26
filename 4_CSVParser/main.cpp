#include <iostream>
#include <tuple>
#include <string>
#include <fstream>
#include "Common/Common.h"
#include "CSVParser/CSVParser.h"

int main() {

    std::ifstream file("data.csv");
    CSVParser<std::string, int, bool> cp(file, 1, ';', ',');

    try {
        for (const auto &t : cp) {
            std::cout << t << std::endl;
        }
    }
    catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }



    return 0;
}
