#ifndef LEVEL_H
#define LEVEL_H


#include <SDL2/SDL.h>
#include <vector>
#include <fstream>
#include "Texture.h"
#include "Log.h"

using std::vector;

struct Point {
    int x;
    int y;
};

enum CHAR_TYPE {
    WALL,
    STAR,
    PLAYER,
    PLAYER_ON_GOAL,
    GOAL_WITH_STAR,
    GOAL_WITHOUT_STAR,
    FLOOR,
    GRASS,
    NONE
};

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
    ~Level();

    void setGame(Game*);

    void loadNextLevel();

    void renderLevel();

    void movePlayer(DIRECTION);

private:

    void placeFloorTexture(int, int);

    void fixLengths();

    void placeGrass();

    char* getChar(int, int, int);
    void setChar(int, int, int, CHAR_TYPE);

    void updatePlayerPos(DIRECTION);

    CHAR_TYPE getCharType(int,int);

    bool movePlayer(int, int, int, int);
    bool moveStar(int, int, int, int);

    std::string _fileName;

    int _currentLevel;
    int _width;
    int _height;

    vector<vector<vector<char> > > _board;

    vector<Point> _stars;
    vector<Point> _goals;

    int _playerX;
    int _playerY;

    bool _EOF;

    Game* _game;

    std::ifstream _inFile;

    Log _logger;

};

#endif
