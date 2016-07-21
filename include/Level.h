#ifndef LEVEL_H
#define LEVEL_H


#include <SDL2/SDL.h>
#include <vector>
#include <fstream>
#include "Texture.h"

class Game;

class Level {

public:

    Level(Game*, const std::string);
    ~Level();

    void loadNextLevel();

    void renderLevel();

private:

    void placeFloorTextures();

    std::string _fileName;

    int _currentLevel;
    int _width;
    int _height;

    std::vector<std::vector<std::vector<Texture> > > _board;

    int _playerX;
    int _playerY;

    Game* _game;

    std::ifstream _inFile;

};

#endif