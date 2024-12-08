#include <boost/program_options.hpp>
#include <iostream>
int main(int argc, const char *argv[]) {
    namespace po = boost::program_options;
    try {
        int rabbitPopulation;
        // Define command line options
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "Produce help message")
            ("rp", po::value<int>(&rabbitPopulation)->default_value(10), "Initial rabbit population");

        po::variables_map vm;

        // Parse command line options, allowing long options with a single dash
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
        std::cout << "Rabbit population: " << rabbitPopulation << std::endl;

    } catch(std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    } catch(...) {
        std::cerr << "Unknown error!" << "\n";
        return 1;
    }
}
