#include <string>
/**
 * @class ProgramOptions
 * @brief A singleton class to hold program configuration options
 *
 */
class ProgramOptions {
private:
    // Simulation Start Values
    int rabbitPopulation;
    int foxPopulation;

    // Map
    std::string mapPath;
    
    // Private constructor to prevent another initialisation
    ProgramOptions () = default;

    // Delete copy constructor and copy assignment operator
    ProgramOptions(const ProgramOptions&) = delete;
    ProgramOptions& operator=(const ProgramOptions&) = delete;

    // Delete move constructor and move assignment operator
    ProgramOptions(ProgramOptions&&) = delete;
    ProgramOptions& operator=(ProgramOptions&&) = delete;

public:
    /**
     * @brief Get the singleton ProgramOptions instance
     *
     * @return A reference to the singleton ProgramOptions instance 
     */
    static ProgramOptions& getInstance() {
        static ProgramOptions instance;
        return instance;
    }

    /**
     * @brief Parses command line options and populates a ProgramOptions instance
     *
     * This function parses the command line options provided in argc and argv, and populates
     * the ProgramOptions instance with the parsed values.
     *
     * @param argc The number of command line arguments
     * @param argv An array of C-style strings containing the command line arguments
     * @return An integer indicating the success or failure of the parsing process
     */
    int parse(int argc, const char *argv[]);

    /**
     * @brief Overloaded stream insertion operator for ProgramOptions
     *
     * This friend function overloads the stream insertion operator (<<) to allow
     * printing the contents of a ProgramOptions instance to an output stream.
     *
     * @param os The output stream where the ProgramOptions instance will be printed
     * @param po The ProgramOptions instance to be printed
     * @return A reference to the output stream after printing the ProgramOptions
     */
    friend std::ostream& operator<<(std::ostream& os, const ProgramOptions& po);
};
