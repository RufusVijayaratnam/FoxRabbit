#ifndef MAP_HPP
#define MAP_HPP
#include <memory>
#include <string>
class Map {
private:

    class Implementation;
    std::unique_ptr<Implementation> implementation;

    // Private constructor to prevent another initialisation
    Map(); 
    // Delete copy constructor and copy assignment operator
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    // Delete move constructor and move assignment operator
    Map(Map&&) = delete;
    Map& operator=(Map&&) = delete;

    void validateMap();

public:
    
    static Map& getInstance();

    /**
     * @brief Load the map from a file
     *
     * @param mapPath A path to a png file of the map
     */
    void loadMap(std::string& mapPath);

};
#endif // !MAP_HPP
