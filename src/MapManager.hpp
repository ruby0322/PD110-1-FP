#include "Map.hpp"
#include <fstream>

#ifndef MAPMANAGER_HPP
#define MAPMANAGER_HPP

class MapManager {
private:
	// Preventing Instantiation
	MapManager();
	~MapManager();
public:
	static void LoadMapFromFile(int map[Map::MAP_SIZE][Map::MAP_SIZE], const std::string& filePath);
};

#endif