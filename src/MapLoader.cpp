#include "MapLoader.hpp"

void MapLoader::loadMapFromFile(int map[Map::MAP_SIZE][Map::MAP_SIZE], const std::string& filePath) {
	std::ifstream inFile;
	inFile.open(filePath.c_str());
	if (inFile.fail()) {
		std::cout << "[MapLoader] Unable to open file \"" << filePath << "\"." << std::endl;
		return;
	}

	for (int i = 0; i < Map::MAP_SIZE; ++i) {
		for (int j = 0; j < Map::MAP_SIZE; ++j) {
			inFile >> map[i][j];
		}
	}

	inFile.close();
}