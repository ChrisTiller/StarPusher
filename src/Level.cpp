#include "../include/Level.h"
#include "../include/Game.h"

Level::Level(const std::string fileName) {
    _fileName = fileName;
    _EOF = false;
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


    std::vector<char> floorRow;
    std::vector<char> starRow;
    std::vector<std::vector<char> > floorMultiRow;
    std::vector<std::vector<char> > starMultiRow;

    while ( getline (_inFile, line) ) {

        if (line.length() != 0) {

            if (line[0] != ';') {


                for (int i = 0; i < line.length() ; i++) {

                    /*Texture temp;
                    Texture starTemp;

                    switch (line[i]) {

                        case ' ':
                            temp.loadTexture("");
                            floorRow.push_back(temp);
                            starTemp.setTextureType(NONE);
                            starRow.push_back(starTemp);
                            break;
                        case '#':
                            starTemp.loadTexture("");
                            starTemp.setTextureType(NONE);
                            temp.loadTexture("Wood_Block_Tall.png");
                            temp.setTextureType(WALL);

                            floorRow.push_back(temp);
                            starRow.push_back(starTemp);

                            break;

                        case '$':
                            temp.loadTexture("");
                            temp.setTextureType(NONE);
                            floorRow.push_back(temp);

                            starTemp.loadTexture("Star.png");
                            starTemp.setTextureType(STAR);
                            starRow.push_back(starTemp);

                            break;

                        case '.':
                            temp.loadTexture("");
                            temp.setTextureType(NONE);
                            floorRow.push_back(temp);

                            starTemp.loadTexture("RedSelector.png");
                            starTemp.setTextureType(OFFGOAL);
                            starRow.push_back(starTemp);

                            break;

                        case '@':
                            _playerX = i;
                            _playerY = lineNumber;

                            temp.loadTexture("");
                            temp.setTextureType(NONE);
                            floorRow.push_back(temp);

                            starTemp.loadTexture("boy.png");
                            starTemp.setTextureType(PLAYER);
                            starRow.push_back(starTemp);

                            break;

                    }*/

                    switch (line[i]) {

                        case ' ':
                        case '#':
                            floorRow.push_back(line[i]);
                            starRow.push_back(' ');
                            break;
                        case '$':
                        case '.':
                            floorRow.push_back(' ');
                            starRow.push_back(line[i]);
                            break;
                        case '@':
                            floorRow.push_back(' ');
                            starRow.push_back(line[i]);
                            _playerX = i;
                            _playerY = lineNumber;
                            break;


                    }

                }

                floorMultiRow.push_back(floorRow);
                starMultiRow.push_back(starRow);

                floorRow.clear();
                starRow.clear();

                lineNumber++;

            } else {

                if (floorMultiRow.size() > 0) {

                    _board.push_back(floorMultiRow);
                    _board.push_back(starMultiRow);

                    _width = floorMultiRow.at(0).size();
                    _height = floorMultiRow.size();

                }

            }

        } else {
            if (_board.size() > 0) {
                fixLengths();

                _width = _board.at(0).at(0).size();
                _height = _board.at(0).size();

                placeFloorTexture(_playerX, _playerY);

                placeGrass();

                for (int i = 0; i < _board.at(0).size(); i++) {
                    for (int j = 0; j < _board.at(0).at(i).size(); j++) {
                        printf("%c", *getChar(0, j, i));
                    }
                    printf(" %i\n",  _board.at(0).at(i).size());
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

        while (_board.at(1).at(i).size() < biggestNum) {
            _board.at(1).at(i).push_back(' ');
        }

    }



}

void Level::placeFloorTexture(int startX, int startY) {

    char *temp;

    if (startX >= _width || startY >= _height) {
        return;
    }

    if ( *( temp = &_board.at(0).at(startY).at(startX) ) == ' ' ) {
        *temp = 'F';

        placeFloorTexture(startX - 1, startY);
        placeFloorTexture(startX, startY - 1);
        placeFloorTexture(startX + 1, startY);
        placeFloorTexture(startX, startY + 1);

    } else {
        return;
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
    int tileHeight = 41;

    int boardWidth = _board.at(0).at(0).size() * tileWidth;
    int boardHeight = _board.at(0).size() * tileHeight;

    int startX = ( _game->getWindowPtr()->getWidth() / 2 ) - ( boardWidth / 2 );
    int startY = ( _game->getWindowPtr()->getHeight() / 2 ) - ( boardHeight / 2 );

    int xOffset = 0;
    int yOffset = 0;

    std::vector<std::vector<char> > floorMap = _board.at(0);
    std::vector<std::vector<char> > playerMap = _board.at(1);

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

            }

            switch (playerMap.at(i).at(j)) {

                case '.':
                        currentTexture.loadTexture("RedSelector.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                    break;
                case '$':
                        currentTexture.loadTexture("Star.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                    break;
                case '@':
                        currentTexture.loadTexture("boy.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                    break;
                case '*':
                        currentTexture.loadTexture("Selector.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                        currentTexture.loadTexture("Star.png");
                        _game->getWindowPtr()->placeTexture(&currentTexture, startX + xOffset - cameraX, startY + yOffset - cameraY);
                    break;
                case '+':
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

    if (*getChar(0, x, y) == '#') {
        return;
    }

    if (*getChar(1, _playerX, _playerY) == '+') {

        if (*getChar(1, x, y) == ' ') {
            *getChar(1, x, y ) = '@';
            *getChar(1, _playerX, _playerY) = '.';

            movePlayerPos(dir);
        }

        if (*getChar(1, x, y) == '*') {

            if (*getChar(1, x2, y2) == '#') {
              return;
            }

            if (*getChar(1, x2, y2) == '*') {
              return;
            }

            if (*getChar(1, x2, y2) == '$') {
              return;
            }

            if (*getChar(1, x2, y2) == ' ') {

                *getChar(1, x2, y2) == '$';
                *getChar(1, x, y) == '+';
                *getChar(1, _playerX, _playerY) == '.';

                movePlayerPos(dir);

            }

        }

        if (*getChar(1, x, y) == '$') {

            if (*getChar(0, x2, y2) == '#') {
              return;
            }

            if (*getChar(1, x2, y2) == '$') {
              return;
            }

            if (*getChar(1, x2, y2) == ' ') {
                *getChar(1, x2, y2) = '$';
                *getChar(1, x, y) = '@';
                *getChar(1, _playerX, _playerY) = '.';

                movePlayerPos(dir);
            }

            if (*getChar(1, x2, y2) == '.') {
              *getChar(1, x2, y2) == '*';
              *getChar(1, x, y) == '@';
              *getChar(1, _playerX, _playerY) = '.';

              movePlayerPos(dir);
            }



        }

    }

    if (*(getChar(1, x, y )) == ' ') {
        *getChar(1, x, y ) = '@';
        *getChar(1, _playerX, _playerY) = ' ';
        movePlayerPos(dir);
        return;
    }

    if (*(getChar(1, x, y )) == '.') {
        *getChar(1, x, y ) = '+';
        *getChar(1, _playerX, _playerY) = ' ';
        movePlayerPos(dir);
        return;
    }

    if (*getChar(1, x, y) == '*') {

      if (*getChar(0, x2, y2) == '#') {
        return;
      }

      if (*getChar(1, x2, y2) == ' ') {
        *getChar(1, x2, y2) = '$';
        *getChar(1, x, y) = '+';
        *getChar(1, _playerX, _playerY) = ' ';

        movePlayerPos(dir);
      }

    }

    if (*(getChar(1, x, y )) == '$') {

        if (*getChar(0, x2, y2) == '#') {
            return;
        }

        if (*getChar(1, x2, y2) == '$') {
          return;
        }

        if (*(getChar(1, x2, y2)) == ' ') {
            *getChar(1, x2, y2) = '$';
            *getChar(1, x, y) = '@';

            *getChar(1, _playerX, _playerY) = ' ';

            movePlayerPos(dir);

            return;

        } else if (*(getChar(1, x2, y2)) == '.') {
            *getChar(1, x2, y2) = '*';
            *getChar(1, x, y) = '@';

            *getChar(1, _playerX, _playerY) = ' ';

            movePlayerPos(dir);

            return;
        }
    }
}

char* Level::getChar(int board, int x, int y) {
    return &_board.at(board).at(y).at(x);
}

void Level::movePlayerPos(DIRECTION dir) {

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
