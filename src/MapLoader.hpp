#include "Map.hpp"
#include <fstream>
#include <string>

#ifndef MAPLOADER_HPP
#define MAPLOADER_HPP

class MapLoader {
private:
	// Preventing Instantiation
	MapLoader();
	~MapLoader();
public:
	static void loadMapFromFile(int map[Map::MAP_SIZE][Map::MAP_SIZE], const std::string& filePath);
};

#endif