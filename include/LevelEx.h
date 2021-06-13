#ifndef LEVELEX_H
#define LEVELEX_H

#include <vector>
#include "Block.h"

using namespace Graphics;
using std::vector;

class ResourceManager;

class LevelEx {

public:

    LevelEx();
    LevelEx(vector<vector<Block> >, vector<Block>, vector<Block>, Block, int, int, ResourceManager*);

    vector<Block*> getVisibleBlocks(SDL_Rect);

    int getWidth() const;
    int getHeight() const;

    bool isCompleted() const;

    void movePlayerUp();
    void movePlayerDown();
    void movePlayerLeft();
    void movePlayerRight();

private:

    vector<Block*> getBlocksAtLocation(Point);

    bool performMoveOperation(void (Block::*)(), void (Block::*)());

    void checkForStarsOnGoals();

    std::string _name;

    int _width;
    int _height;

    bool _completed;

    Block _character;

    vector<Block> _stars;
    vector<Block> _goals;

    vector<vector<Block> > _board;

    ResourceManager* _resourceManager;
};

#endif