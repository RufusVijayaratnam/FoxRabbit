// main.cpp
#include <iostream>
#include "ProgramOptions.hpp"

int main(int argc, const char *argv[]) {
    ProgramOptions& programOptions = ProgramOptions::getInstance();
    if(programOptions.parse(argc, argv) != 0) {
        // Program options failure
        throw std::runtime_error("Failed to parse program options");
    }
}
