#include "../include/Level.h"
#include "../include/Game.h"

Level::Level(const std::string fileName) {
    _fileName = fileName;
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

    std::vector<Texture> floorRow;
    std::vector<Texture> starRow;
    std::vector<std::vector<Texture> > floorMultiRow;
    std::vector<std::vector<Texture> > starMultiRow;

    while ( getline (_inFile, line) ) {

        if (line.length() != 0) {

            if (line[0] != ';') {

                for (int i = 0; i < line.length() ; i++) {

                    Texture temp;
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

        } 

    }

    _inFile.close();

    placeFloorTexture(_playerX, _playerY);
    placeGrass();

}

void Level::placeFloorTexture(int startX, int startY) {

    Texture *temp;

    if (startX >= _width || startY >= _height) {
        return;
    }

    if ( ( temp = &_board.at(0).at(startY).at(startX) )->getTextureType() == NONE ) {
        temp->setTextureType(FLOOR);
        temp->loadTexture("Plain_Block.png");

        placeFloorTexture(startX - 1, startY);
        placeFloorTexture(startX, startY - 1);
        placeFloorTexture(startX + 1, startY);
        placeFloorTexture(startX, startY + 1);

    } else {
        return;
    }

}

void Level::placeGrass() {

    Texture *temp;


    for ( int i = 0; i < _height; i++) {
        for ( int j = 0; j < _width; j++) {

            printf("%i, %i\n", j, i);

            if ( ( temp = &_board.at(0).at(i).at(j) )->getTextureType() == NONE) {
                temp->setTextureType(GRASS);
                temp->loadTexture("Grass_Block.png");
            }

        }
    }

}

void Level::renderLevel() {

    int tileWidth = _board.at(0).at(0).at(0).getWidth();
    //int tileHeight = _board.at(0).at(0).at(0).getHeight();
    int tileHeight = 40;

    int boardWidth = _board.at(0).at(0).size() * tileWidth;
    int boardHeight = _board.at(0).size() * tileHeight;

    int startX = ( _game->getWindowPtr()->getWidth() / 2 ) - ( boardWidth / 2 );
    int startY = ( _game->getWindowPtr()->getHeight() / 2 ) - ( boardHeight / 2 );

    int xOffset = 0;
    int yOffset = 0;

    std::vector<std::vector<Texture> > floorMap = _board.at(0);
    std::vector<std::vector<Texture> > playerMap = _board.at(1);

    Texture *currentTexture;

    for (int i = 0; i < floorMap.size(); i++) {

        xOffset = 0;

        for ( int j = 0; j < floorMap.at(0).size(); j++) {

            if ( ( currentTexture = &floorMap.at(i).at(j) )->getTextureType() != NONE) {

                _game->getWindowPtr()->placeTexture(currentTexture, startX + xOffset, startY + yOffset);

            }

            if ( ( currentTexture = &playerMap.at(i).at(j) )->getTextureType() != NONE) {

                _game->getWindowPtr()->placeTexture(currentTexture, startX + xOffset, startY + yOffset);

            }

            xOffset += tileWidth;
        }

        yOffset += tileHeight;

    }


}