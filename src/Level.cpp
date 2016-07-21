#include "../include/Level.h"
#include "../include/Game.h"

Level::Level(Game* game, const std::string fileName) {
    _game = game;
    _fileName = fileName;
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

    while ( getline (_inFile, line) ) {

        if (line.length() != 0) {

            if (line[0] != ';') {

                for (int i = 0; i < line.length() ; i++) {

                    switch (line[i]) {

                        case ' ':
                            
                            break;

                    }

                }

            }

        }

    }


}