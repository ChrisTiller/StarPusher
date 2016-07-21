#ifndef LEVEL_H
#define LEVEL_H


#include <SDL2/SDL.h>
#include <vector>
#include <fstream>
#include "Texture.h"

enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Game;

class Level {

public:

    Level(const std::string);

    void setGame(Game*);

    void loadNextLevel();

    void renderLevel();

    void movePlayer(DIRECTION);

private:

    void placeFloorTexture(int, int);

    void fixLengths();

    void placeGrass();

    char* getChar(int, int, int);


    std::string _fileName;

    int _currentLevel;
    int _width;
    int _height;

    std::vector<std::vector<std::vector<char> > > _board;

    int _playerX;
    int _playerY;

    Game* _game;

    std::ifstream _inFile;

    Texture test;

};

#endif