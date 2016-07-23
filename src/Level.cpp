#include "../include/Level.h"
#include "../include/Game.h"

#include <iostream>
#include <algorithm>

Level::Level(const std::string fileName) {
    _fileName = fileName;
    _EOF = false;

    _logger.setFileName("../logs/log.txt");
}

Level::~Level() {
    if (_inFile.is_open()){
        _inFile.close();
    }
}

void Level::setGame(Game* game) {
    _game = game;
}

void Level::loadNextLevel() {

    if (!_inFile.is_open()) {

        _inFile.open(_fileName.c_str());

        if (!_inFile.is_open()) {
            printf("Couldn't load file");
            return;
        }

    }

    std::string line;
    int lineNumber = 0;

    _board.clear();
    _goals.clear();
    _stars.clear();

    std::vector<char> floorRow;
    std::vector<std::vector<char> > floorMultiRow;

    Point star;
    Point goal;

    while ( getline (_inFile, line) ) {

        if (line.length() != 0) {

            if (line[0] != ';') {


                for (int i = 0; i < line.length() ; i++) {

                    switch (line[i]) {

                            case ' ':
                            case '#':
                                floorRow.push_back(line[i]);
                                break;
                            case '$':
                                star.x = i;
                                star.y = lineNumber;
                                _stars.push_back(star);
                                floorRow.push_back(' ');
                                break;
                            case '.':
                                goal.x = i;
                                goal.y = lineNumber;
                                _goals.push_back(goal);
                                floorRow.push_back(' ');
                                break;
                            case '+':
                                goal.x = i;
                                goal.y = lineNumber;
                                _goals.push_back(goal);
                                floorRow.push_back(' ');
                                _playerX = i;
                                _playerY = lineNumber;
                                break;
                            case '*':
                                goal.x = i;
                                goal.y = lineNumber;
                                _goals.push_back(goal);

                                star.x = i;
                                star.y = lineNumber;
                                _stars.push_back(star);

                                floorRow.push_back(' ');
                                break;
                            case '@':
                                floorRow.push_back(' ');
                                _playerX = i;
                                _playerY = lineNumber;
                                break;
                    }

                }

                floorMultiRow.push_back(floorRow);

                floorRow.clear();

                lineNumber++;

            } else {

                if (floorMultiRow.size() > 0) {

                    _board.push_back(floorMultiRow);
                }
            }
        } else {
            if (_board.size() > 0) {


                fixLengths();

                _width = _board.at(0).at(0).size();
                _height = _board.at(0).size();


                placeFloorTexture(_playerX, _playerY);

                placeGrass();

                *getChar(0, _playerX, _playerY) = '@';

                for (int i = 0; i < _goals.size(); i++) {
                    Point p = _goals.at(i);
                    if (p.x == _playerX && p.y == _playerY) {
                        *getChar(0, p.x, p.y) = '+';
                    } else {
                        *getChar(0, p.x, p.y) = '.';
                    }
                }

                for (int i = 0; i < _stars.size(); i++) {
                    Point p = _stars.at(i);

                    if ( *(getChar(0, p.x, p.y)) == '.') {
                        *getChar(0, p.x, p.y) = '*';
                    } else {
                        *getChar(0, p.x, p.y) = '$';
                    }
                }
                return;
            }
        }
    }

    _EOF = true;
}

void Level::fixLengths() {

    int biggestNum = 0;

    for (int i = 0; i < _board.at(0).size(); i++) {

        if (_board.at(0).at(i).size() > biggestNum) {
            biggestNum = _board.at(0).at(i).size();
        }
    }

    for (int i = 0; i < _board.at(0).size(); i++) {

        while (_board.at(0).at(i).size() < biggestNum) {
            _board.at(0).at(i).push_back(' ');
        }
    }
}

void Level::placeFloorTexture(int startX, int startY) {

    char *temp;

    if (startX >= _width || startY >= _height) {
        return;
    }

    if (startX < 0 || startY < 0) {
        return;
    }

    if (*(temp = &_board.at(0).at(startY).at(startX)) == ' ') {

        *temp = 'F';

        placeFloorTexture(startX - 1, startY);
        placeFloorTexture(startX, startY - 1);
        placeFloorTexture(startX + 1, startY);
        placeFloorTexture(startX, startY + 1);
    }
}

void Level::placeGrass() {

    char *temp;

    for ( int i = 0; i < _height; i++) {
        for ( int j = 0; j < _width; j++) {

            if ( *( temp = &_board.at(0).at(i).at(j) ) == ' ') {
                *temp = 'G';
            }
        }
    }
}

void Level::renderLevel() {

    if (_EOF) {
        return;
    }

    //int tileWidth = _board.at(0).at(0).at(0).getWidth();
    int tileWidth = 50;
    //int tileHeight = _board.at(0).at(0).at(0).getHeight();
    int tileHeight = 40;

    int boardWidth = _board.at(0).at(0).size() * tileWidth;
    int boardHeight = _board.at(0).size() * tileHeight;

    int startX = ( _game->getWindowPtr()->getWidth() / 2 ) - ( boardWidth / 2 );
    int startY = ( _game->getWindowPtr()->getHeight() / 2 ) - ( boardHeight / 2 );

    int xOffset = 0;
    int yOffset = 0;

    std::vector<std::vector<char> > floorMap = _board.at(0);

    Texture currentTexture;

    int cameraX = _game->getCamera().getXPos();
    int cameraY = _game->getCamera().getYPos();

    for (int i = 0; i < floorMap.size(); i++) {

        xOffset = 0;

        for ( int j = 0; j < floorMap.at(i).size(); j++) {


            switch (floorMap.at(i).at(j)) {

                case 'G':
                        currentTexture.loadTexture("Grass_Block.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                    break;
                case 'F':
                        currentTexture.loadTexture("Plain_Block.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                    break;
                case '#':


                    currentTexture.loadTexture("Wood_Block_Tall.png");
                    _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                    break;


                case '.':
                        currentTexture.loadTexture("Plain_Block.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                        currentTexture.loadTexture("RedSelector.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                        break;
                case '$':
                        currentTexture.loadTexture("Plain_Block.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                        currentTexture.loadTexture("Star.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                        break;
                case '@':
                        currentTexture.loadTexture("Plain_Block.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                        currentTexture.loadTexture("boy.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                        break;
                case '*':
                        currentTexture.loadTexture("Plain_Block.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                        currentTexture.loadTexture("Selector.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                        currentTexture.loadTexture("Star.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                    break;
                case '+':
                        currentTexture.loadTexture("Plain_Block.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                        currentTexture.loadTexture("RedSelector.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                        currentTexture.loadTexture("boy.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                    break;
            }
            xOffset += tileWidth;
        }
        yOffset += tileHeight;
    }
}

void Level::movePlayer(DIRECTION dir) {


    int x, y, x2, y2;

    switch (dir) {

        case UP:

          x = _playerX;
          y = _playerY - 1;
          x2 = _playerX;
          y2 = _playerY - 2;

          break;

        case DOWN:

          x = _playerX;
          y = _playerY + 1;
          x2 = _playerX;
          y2 = _playerY + 2;

          break;

        case LEFT:

          x = _playerX - 1;
          y = _playerY;
          x2 = _playerX - 2;
          y2 = _playerY;

          break;

        case RIGHT:

          x = _playerX + 1;
          y = _playerY;
          x2 = _playerX + 2;
          y2 = _playerY;

          break;
    }

    if (movePlayer(x, y, x2, y2)) {
        updatePlayerPos(dir);
    }
}

char* Level::getChar(int board, int x, int y) {
    return &_board.at(board).at(y).at(x);
}

void Level::setChar(int board, int x, int y, CHAR_TYPE type) {

    if (x < 0 || y < 0 || x >= _width || y >= _height) {
        return;
    }

    switch (type)  {
        case WALL:
            _board.at(board).at(y).at(x) = '#';
            return;
        case PLAYER:
            _board.at(board).at(y).at(x) = '@';
            return;
        case STAR:
            _board.at(board).at(y).at(x) = '$';
            return;
        case GOAL_WITHOUT_STAR:
            _board.at(board).at(y).at(x) = '.';
            return;
        case GOAL_WITH_STAR:
            _board.at(board).at(y).at(x) = '*';
            return;
        case PLAYER_ON_GOAL:
            _board.at(board).at(y).at(x) = '+';
            return;
        case FLOOR:
            _board.at(board).at(y).at(x) = 'F';
            return;
        case GRASS:
            _board.at(board).at(y).at(x) = 'G';
            return;
        case NONE:
            _board.at(board).at(y).at(x) = ' ';
            return;
    }
}

void Level::updatePlayerPos(DIRECTION dir) {

  switch (dir) {

    case UP:
        _playerY--;
      break;
    case DOWN:
      _playerY++;
      break;
    case LEFT:
      _playerX--;
      break;
    case RIGHT:
      _playerX++;
      break;
  }
}

CHAR_TYPE Level::getCharType(int x, int y) {

    if (x < 0 || y < 0 || x >= _width || y >= _height) {
        return NONE;
    }

    switch (*getChar(0, x, y)) {

        case '#':
            return WALL;
        case ' ':
            return NONE;
        case 'G':
            return GRASS;
        case '@':
            return PLAYER;
        case '$':
            return STAR;
        case '.':
            return GOAL_WITHOUT_STAR;
        case '*':
            return GOAL_WITH_STAR;
        case '+':
            return PLAYER_ON_GOAL;
        case 'F':
            return FLOOR;
    }
}

bool Level::movePlayer(int x, int y, int x2, int y2) {

    if (getCharType(x, y) == WALL) {
        return false;
    }

    switch (getCharType(_playerX, _playerY)) {

        case PLAYER:

            switch (getCharType(x, y)) {

                case FLOOR:
                    setChar(0, x, y, PLAYER);
                    setChar(0, _playerX, _playerY, FLOOR);
                    return true;

                case STAR:

                    if (moveStar(x, y, x2, y2)) {
                        setChar(0, x, y, PLAYER);
                        setChar(0, _playerX, _playerY, FLOOR);
                        return true;
                    } else {
                        return false;
                    }

                case GOAL_WITH_STAR:

                    if (moveStar(x, y, x2, y2)) {

                        setChar(0, x, y, PLAYER_ON_GOAL);
                        setChar(0, _playerX, _playerY, FLOOR);

                        return true;
                    } else {
                        return false;
                    }

                case GOAL_WITHOUT_STAR:

                    setChar(0, x, y, PLAYER_ON_GOAL);
                    setChar(0, _playerX, _playerY, FLOOR);

                    return true;

            }

            break;

        case PLAYER_ON_GOAL:

            switch (getCharType(x, y)) {

                case FLOOR:

                    setChar(0, x, y, PLAYER);
                    setChar(0, _playerX, _playerY, GOAL_WITHOUT_STAR);

                    return true;

                case STAR:

                    if (moveStar(x, y, x2, y2)) {

                        setChar(0, x, y, PLAYER);
                        setChar(0, _playerX, _playerY, GOAL_WITHOUT_STAR);

                        return true;
                    } else {
                        return false;
                    }

                case GOAL_WITHOUT_STAR:

                    setChar(0, x, y, PLAYER_ON_GOAL);
                    setChar(0, _playerX, _playerY, GOAL_WITHOUT_STAR);

                    return true;

                case GOAL_WITH_STAR:

                    if (moveStar(x, y, x2, y2)) {

                        setChar(0, x, y, PLAYER_ON_GOAL);
                        setChar(0, _playerX, _playerY, GOAL_WITHOUT_STAR);

                        return true;
                    } else {
                        return false;
                    }
            }
            break;
    }
}

bool Level::moveStar(int x, int y, int x2, int y2) {

    if (getCharType(x2, y2) == WALL || getCharType(x2, y2) == STAR || getCharType(x2, y2) == GOAL_WITH_STAR) {
        return false;
    }

    switch (getCharType(x2, y2)) {

        case FLOOR:
            setChar(0, x2, y2, STAR);
            return true;

        case GOAL_WITHOUT_STAR:
            setChar(0, x2, y2, GOAL_WITH_STAR);
            return true;
    }
}
