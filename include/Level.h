#ifndef LEVEL_H
#define LEVEL_H


#include <SDL2/SDL.h>
#include <vector>
#include <fstream>
#include "Texture.h"

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

    bool levelCompleted();

    void loadLevels();

    void gotoNextLevel();
    void gotoPrevLevel();

    void resetLevel();

    void renderLevel();

    void movePlayer(DIRECTION);

private:

    void placeFloorTexture(int, int, int);

    void fixLengths(int);

    void placeGrass(int);

    char* getChar(int, int, int);
    char* getChar(int, int);


    void getPlayerPos();
    void updatePlayerPos(DIRECTION);

    CHAR_TYPE getCharType(int,int);
    void setChar(int, int, CHAR_TYPE);

    bool movePlayer(int, int, int, int);
    bool moveStar(int, int);

    std::string _fileName;

    int _currentLevel;
    int _levels;
    int _width;
    int _height;

    vector<vector<vector<char> > > _board;

    vector<vector<char> > _currentBoard;

    vector<Point> _stars;
    vector<Point> _goals;

    int _playerX;
    int _playerY;

    bool _EOF;

    Game* _game;

    std::ifstream _inFile;

};

#endif
