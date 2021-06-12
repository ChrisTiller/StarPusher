#include "../include/Level.h"
#include "../include/Game.h"

#include <iostream>
#include <algorithm>

Level::Level(const std::string fileName) {
    _fileName = fileName;
    _EOF = false;

    _levels = 0;
    _currentLevel = -1;
}

Level::~Level() {
    if (_inFile.is_open()){
        _inFile.close();
    }
}

void Level::setGame(Game* game) {
    _game = game;
}

bool Level::levelCompleted() {

    for ( int i = 0; i < _currentBoard.size(); i++) {
        for ( int j = 0; j < _currentBoard.at(i).size(); j++) {
            if (_currentBoard.at(i).at(j) == '.' || _currentBoard.at(i).at(j) == '$') {
                return false;
            }
        }
    }

    return true;
}

void Level::loadLevels() {

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

    std::vector<char> floorRow;
    std::vector<std::vector<char> > floorMultiRow;

    Point2D star;
    Point2D goal;

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


            }
        } else {
            if (floorMultiRow.size() > 0) {

                _board.push_back(floorMultiRow);

                _levels++;

                fixLengths(_levels - 1);

                placeFloorTexture(_levels - 1, _playerX, _playerY);

                placeGrass(_levels - 1);

                *getChar(_levels - 1, _playerX, _playerY) = '@';

                for (int i = 0; i < _goals.size(); i++) {
                    Point2D p = _goals.at(i);
                    if (p.x == _playerX && p.y == _playerY) {
                        *getChar(_levels - 1, p.x, p.y) = '+';
                    } else {
                        *getChar(_levels - 1, p.x, p.y) = '.';
                    }
                }

                for (int i = 0; i < _stars.size(); i++) {
                    Point2D p = _stars.at(i);

                    if ( *(getChar(_levels - 1, p.x, p.y)) == '.') {
                        *getChar(_levels - 1, p.x, p.y) = '*';
                    } else {
                        *getChar(_levels - 1, p.x, p.y) = '$';
                    }
                }

                for ( int i = 0; i < _board.at(_levels - 1).size(); i++) {
                    for ( int j = 0; j < _board.at(_levels - 1).at(i).size(); j++) {

                        //std::cout << _board.at(_levels - 1).at(i).at(j);
                    }
                    //std:: cout << std::endl;

                }

                floorMultiRow.clear();
                _goals.clear();
                _stars.clear();

                lineNumber = 0;

            }
        }
    }

}

void Level::gotoNextLevel() {

    if (++_currentLevel >= _levels) {
        _currentLevel = _levels - 1;
        return;
    }

    _currentBoard = _board.at(_currentLevel);

    getPlayerPos();
}

void Level::gotoPrevLevel() {

    if (--_currentLevel <= 0) {
        _currentLevel = 0;
        return;
    }

    _currentBoard = _board.at(_currentLevel);

    getPlayerPos();
}

void Level::resetLevel() {
    _currentBoard = _board.at(_currentLevel);

    getPlayerPos();
}

void Level::fixLengths(int level) {

    int biggestNum = 0;

    for (int i = 0; i < _board.at(level).size(); i++) {

        if (_board.at(level).at(i).size() > biggestNum) {
            biggestNum = _board.at(level).at(i).size();
        }
    }

    for (int i = 0; i < _board.at(level).size(); i++) {

        while (_board.at(level).at(i).size() < biggestNum) {
            _board.at(level).at(i).push_back(' ');
        }
    }
}

void Level::placeFloorTexture(int level, int startX, int startY) {

    char *temp;

    if (startX >= _board.at(level).at(0).size() || startY >= _board.at(level).size()) {
        return;
    }

    if (startX < 0 || startY < 0) {
        return;
    }

    if (*(temp = &_board.at(level).at(startY).at(startX)) == ' ') {

        *temp = 'F';

        placeFloorTexture(level, startX - 1, startY);
        placeFloorTexture(level, startX, startY - 1);
        placeFloorTexture(level, startX + 1, startY);
        placeFloorTexture(level, startX, startY + 1);
    }
}

void Level::placeGrass(int level) {

    char *temp;

    for ( int i = 0; i < _board.at(level).size(); i++) {
        for ( int j = 0; j < _board.at(level).at(i).size(); j++) {

            if ( *( temp = &_board.at(level).at(i).at(j) ) == ' ') {
                *temp = 'G';
            }
        }
    }
}

void Level::renderLevel() {

    int tileWidth = 50;
    int tileHeight = 40;

    int boardWidth = _currentBoard.at(0).size() * tileWidth;
    int boardHeight = _currentBoard.size() * tileHeight;

    int startX = ( _game->getWindowPtr()->getWidth() / 2 ) - ( boardWidth / 2 );
    int startY = ( _game->getWindowPtr()->getHeight() / 2 ) - ( boardHeight / 2 );

    int xOffset = 0;
    int yOffset = 0;

    Texture* currentTexture;

    int cameraX = _game->getCamera().getXPos();
    int cameraY = _game->getCamera().getYPos();

    for (int i = 0; i < _currentBoard.size(); i++) {

        xOffset = 0;

        for ( int j = 0; j < _currentBoard.at(i).size(); j++) {

            int xPos = startX + xOffset - cameraX;
            int yPos = startY + yOffset - cameraY;

            if ( ( xPos + tileWidth > 0 && xPos < _game->getWindowPtr()->getWidth() ) || ( yPos + tileHeight > 0 && yPos < _game->getWindowPtr()->getHeight() ) ) {

                switch (_currentBoard.at(i).at(j)) {

                    case 'G':
                            currentTexture = _game->getResourceManager()->getTexture("Grass_Block.png");
                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                        break;
                    case 'F':
                            currentTexture = _game->getResourceManager()->getTexture("Plain_Block.png");
                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                        break;
                    case '#':

                            if (getCharType(j + 1, i) == CHAR_TYPE::WALL && getCharType(j, i - 1) == CHAR_TYPE::WALL) {
                                currentTexture = _game->getResourceManager()->getTexture("Wall_Block_Tall.png");
                            } else if (getCharType(j - 1, i) == CHAR_TYPE::WALL && getCharType(j, i - 1) == CHAR_TYPE::WALL) {
                                currentTexture = _game->getResourceManager()->getTexture("Wall_Block_Tall.png");
                            } else if (getCharType(j + 1, i) == CHAR_TYPE::WALL && getCharType(j, i + 1) == CHAR_TYPE::WALL) {
                                currentTexture = _game->getResourceManager()->getTexture("Wall_Block_Tall.png");
                            } else if (getCharType(j - 1, i) == CHAR_TYPE::WALL && getCharType(j, i + 1) == CHAR_TYPE::WALL) {
                                currentTexture = _game->getResourceManager()->getTexture("Wall_Block_Tall.png");
                            } else {
                                currentTexture = _game->getResourceManager()->getTexture("Wood_Block_Tall.png");
                            }

                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                            break;
                    case '.':
                            currentTexture = _game->getResourceManager()->getTexture("Plain_Block.png");
                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                            currentTexture = _game->getResourceManager()->getTexture("RedSelector.png");
                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                            break;
                    case '$':
                            currentTexture = _game->getResourceManager()->getTexture("Plain_Block.png");
                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                            currentTexture = _game->getResourceManager()->getTexture("Star.png");
                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                            break;
                    case '@':
                            currentTexture = _game->getResourceManager()->getTexture("Plain_Block.png");
                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                            currentTexture = _game->getResourceManager()->getTexture("boy.png");
                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                            break;
                    case '*':
                            currentTexture = _game->getResourceManager()->getTexture("Plain_Block.png");
                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                            currentTexture = _game->getResourceManager()->getTexture("Selector.png");
                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                            currentTexture = _game->getResourceManager()->getTexture("Star.png");
                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                        break;
                    case '+':
                            currentTexture = _game->getResourceManager()->getTexture("Plain_Block.png");
                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                            currentTexture = _game->getResourceManager()->getTexture("RedSelector.png");
                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                            currentTexture = _game->getResourceManager()->getTexture("boy.png");
                            _game->getWindowPtr()->placeTexture(currentTexture, xPos, yPos);
                        break;
                }
            }
            xOffset += tileWidth;
        }
        yOffset += tileHeight;
    }
}

void Level::movePlayer(DIRECTION dir) {

    switch (dir) {

        case UP:

          if (movePlayer(_playerX, _playerY - 1, _playerX, _playerY - 2)) {
              updatePlayerPos(dir);
          }
          break;

        case DOWN:

          if (movePlayer(_playerX, _playerY + 1, _playerX, _playerY + 2)) {
              updatePlayerPos(dir);
          }
          break;

        case LEFT:

          if (movePlayer(_playerX - 1, _playerY, _playerX - 2, _playerY)) {
              updatePlayerPos(dir);
          }
          break;

        case RIGHT:

          if (movePlayer(_playerX + 1, _playerY, _playerX + 2, _playerY)) {
              updatePlayerPos(dir);
          }
          break;
    }
}

char* Level::getChar(int board, int x, int y) {
    return &_board.at(board).at(y).at(x);
}

char* Level::getChar(int x, int y) {
    return &_currentBoard.at(y).at(x);
}

void Level::setChar(int x, int y, CHAR_TYPE type) {

    if (x < 0 || y < 0 || x >= _currentBoard.at(0).size() || y >= _currentBoard.size()) {
        return;
    }

    switch (type)  {
        case CHAR_TYPE::WALL:
            _currentBoard.at(y).at(x) = '#';
            return;
        case CHAR_TYPE::PLAYER:
            _currentBoard.at(y).at(x) = '@';
            return;
        case CHAR_TYPE::STAR:
            _currentBoard.at(y).at(x) = '$';
            return;
        case CHAR_TYPE::GOAL_WITHOUT_STAR:
            _currentBoard.at(y).at(x) = '.';
            return;
        case GOAL_WITH_STAR:
            _currentBoard.at(y).at(x) = '*';
            return;
        case CHAR_TYPE::PLAYER_ON_GOAL:
            _currentBoard.at(y).at(x) = '+';
            return;
        case CHAR_TYPE::FLOOR:
            _currentBoard.at(y).at(x) = 'F';
            return;
        case CHAR_TYPE::GRASS:
            _currentBoard.at(y).at(x) = 'G';
            return;
        case CHAR_TYPE::NONE:
            _currentBoard.at(y).at(x) = ' ';
            return;
    }
}

void Level::getPlayerPos() {

    for ( int i = 0; i < _currentBoard.size(); i++) {
        for ( int j = 0; j < _currentBoard.at(i).size(); j++) {

            if (_currentBoard.at(i).at(j) == '@') {
                _playerX = j;
                _playerY = i;
            }
        }
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

    if (x < 0 || y < 0 || x >= _currentBoard.at(0).size() || y >= _currentBoard.size()) {
        return CHAR_TYPE::NONE;
    }

    switch (*getChar(x, y)) {

        case '#':
            return CHAR_TYPE::WALL;
        case ' ':
            return CHAR_TYPE::NONE;
        case 'G':
            return CHAR_TYPE::GRASS;
        case '@':
            return CHAR_TYPE::PLAYER;
        case '$':
            return CHAR_TYPE::STAR;
        case '.':
            return CHAR_TYPE::GOAL_WITHOUT_STAR;
        case '*':
            return CHAR_TYPE::GOAL_WITH_STAR;
        case '+':
            return CHAR_TYPE::PLAYER_ON_GOAL;
        case 'F':
            return CHAR_TYPE::FLOOR;
    }

    return CHAR_TYPE::NONE;
}

bool Level::movePlayer(int x, int y, int x2, int y2) {

    if (getCharType(x, y) == CHAR_TYPE::WALL) {
        return false;
    }

    switch (getCharType(_playerX, _playerY)) {

        case CHAR_TYPE::PLAYER:

            switch (getCharType(x, y)) {

                case CHAR_TYPE::FLOOR:
                    setChar(x, y, CHAR_TYPE::PLAYER);
                    setChar(_playerX, _playerY, CHAR_TYPE::FLOOR);
                    return true;

                case CHAR_TYPE::STAR:

                    if (moveStar(x2, y2)) {
                        setChar(x, y, CHAR_TYPE::PLAYER);
                        setChar(_playerX, _playerY, CHAR_TYPE::FLOOR);
                        return true;
                    } else {
                        return false;
                    }

                case GOAL_WITH_STAR:

                    if (moveStar(x2, y2)) {

                        setChar(x, y, PLAYER_ON_GOAL);
                        setChar(_playerX, _playerY, CHAR_TYPE::FLOOR);

                        return true;
                    } else {
                        return false;
                    }

                case GOAL_WITHOUT_STAR:

                    setChar(x, y, PLAYER_ON_GOAL);
                    setChar(_playerX, _playerY, CHAR_TYPE::FLOOR);

                    return true;

            }

            break;

        case PLAYER_ON_GOAL:

            switch (getCharType(x, y)) {

                case CHAR_TYPE::FLOOR:

                    setChar(x, y, CHAR_TYPE::PLAYER);
                    setChar(_playerX, _playerY, GOAL_WITHOUT_STAR);

                    return true;

                case CHAR_TYPE::STAR:

                    if (moveStar(x2, y2)) {

                        setChar(x, y, CHAR_TYPE::PLAYER);
                        setChar(_playerX, _playerY, GOAL_WITHOUT_STAR);

                        return true;
                    } else {
                        return false;
                    }

                case GOAL_WITHOUT_STAR:

                    setChar(x, y, PLAYER_ON_GOAL);
                    setChar(_playerX, _playerY, GOAL_WITHOUT_STAR);

                    return true;

                case GOAL_WITH_STAR:

                    if (moveStar(x2, y2)) {

                        setChar(x, y, PLAYER_ON_GOAL);
                        setChar(_playerX, _playerY, GOAL_WITHOUT_STAR);

                        return true;
                    } else {
                        return false;
                    }
            }
            break;
    }

    return false;
}

bool Level::moveStar(int x2, int y2) {

    if (getCharType(x2, y2) == CHAR_TYPE::WALL || getCharType(x2, y2) == CHAR_TYPE::STAR || getCharType(x2, y2) == CHAR_TYPE::GOAL_WITH_STAR) {
        return false;
    }

    switch (getCharType(x2, y2)) {

        case CHAR_TYPE::FLOOR:
            setChar(x2, y2, CHAR_TYPE::STAR);
            return true;

        case GOAL_WITHOUT_STAR:
            setChar(x2, y2, GOAL_WITH_STAR);
            return true;
    }

    return false;
}
