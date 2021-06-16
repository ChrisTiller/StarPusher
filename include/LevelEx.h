#ifndef LEVELEX_H
#define LEVELEX_H

#include <tuple>
#include <vector>
#include "Block.h"

using namespace Graphics;
using std::vector;

class LevelEx {

public:

    LevelEx();
    LevelEx(vector<vector<Block> >, vector<Block>, vector<Block>, Block, int, int);

    vector<Block*> getVisibleBlocks(SDL_Rect);

    int getWidth() const;
    int getHeight() const;

    bool isCompleted() const;

    void movePlayerUp();
    void movePlayerDown();
    void movePlayerLeft();
    void movePlayerRight();

    void undoLastMove();

private:

    vector<Block*> getBlocksAtLocation(Point);

    bool performMoveOperation(void (Block::*)(), void (Block::*)());

    void checkForStarsOnGoals();

    std::string _name;

    int _width;
    int _height;

    int _stepCounter;

    bool _completed;

    Block _character;

    vector<Block> _stars;
    vector<Block> _goals;

    vector<vector<Block> > _board;

    vector<std::tuple<Block*, Block*, void (Block::*)()> > _moveStack;
};

#endif