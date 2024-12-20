#include <cstdio>
#include <stdio.h>
#include <stdexcept>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "Map.hpp"

#include "LoggingMacros.hpp"
class Map::Implementation {
private:
    cv::Mat map;

public:
    void loadMap(std::string &mapPath) {
        LOG_INFO("Attempting to load map");

        if(mapPath.empty()) {
            LOG_ERROR("Map path is empty.");
            throw std::invalid_argument("Map path cannot be empty.");
        }

        this->map = cv::imread(mapPath, cv::IMREAD_COLOR);

        if(map.empty()) {
            LOG_ERROR("Could not open map file: " << mapPath);
            throw std::runtime_error("Failed to load map image from path: " + mapPath);
        }

        LOG_DEBUG("Loaded map image successfully.\n"
                  "Height: " << this->map.rows << " pixels\n"
                  "Width: " << this->map.cols << " pixels");
    }
};

Map::Map() : implementation(std::make_unique<Implementation>()) {};

Map& Map::getInstance() {
    static Map instance;
    return instance;
}

void Map::loadMap(std::string &mapPath) {
    implementation->loadMap(mapPath);
}
