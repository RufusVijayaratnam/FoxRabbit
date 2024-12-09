// includes/ProgramOptions.hpp
#ifndef PROGRAMOPTIONS_HPP
#define PROGRAMOPTIONS_HPP
#include "ProgramOptions.hpp"

#include <boost/program_options.hpp>
#include <iostream>
#include <stdexcept>

#include "LoggingMacros.hpp"

int ProgramOptions::parse(int argc, const char *argv[]) {
    namespace po = boost::program_options;
    try {
        LOG_DEBUG("Attempting to parse program options");
        // Define command line options
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "Produce help message")
            ("rp", po::value<int>(&rabbitPopulation)->default_value(10), "Initial rabbit population")
            ("fp", po::value<int>(&rabbitPopulation)->default_value(10), "Initial fox population")
            ("map", po::value<std::string>(&mapPath)->default_value("assets/map.png"), "Map file path");

        po::variables_map vm;
        po::store(
            po::command_line_parser(argc, argv)
            .options(desc)
            .style(po::command_line_style::unix_style | po::command_line_style::allow_long_disguise)
            .run(),
            vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 1;
        }
        po::notify(vm);

    } catch(std::exception& e) {
        LOG_ERROR(e.what());
        return 1;
    } catch(...) {
        LOG_ERROR("Unknown error");
        return 1;
    }
    LOG_INFO("Program options parsed successfully" << *this);
    return 0;
}

std::ostream& operator<<(std::ostream& os, const ProgramOptions& po) {
    os << "\nProgram Options:" <<
        std::left << std::setw(30) << "\nInitial rabbit population:" <<
        std::right << std::setw(30) << po.rabbitPopulation <<
        std::left << std::setw(30) << "\nInitial fox population:" <<
        std::right << std::setw(30) << po.foxPopulation <<
        std::left << std::setw(30) << "\nMap file path:" <<
        std::right << std::setw(30) << po.mapPath;
    return os;
}

#endif
