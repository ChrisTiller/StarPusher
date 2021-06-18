#ifndef LEVELEX_H
#define LEVELEX_H

#include <tuple>
#include <vector>
#include "Block.h"

class LevelEx {

public:

    LevelEx();
    LevelEx(std::vector<std::vector<Graphics::Block> >, std::vector<Graphics::Block>, std::vector<Graphics::Block>, Graphics::Block, int, int);

    std::vector<Graphics::Block*> getVisibleBlocks(const SDL_Rect&);

    int getWidth() const;
    int getHeight() const;

    bool isCompleted() const;

    void movePlayerUp();
    void movePlayerDown();
    void movePlayerLeft();
    void movePlayerRight();

    void undoLastMove();

private:

    std::vector<Graphics::Block*> getBlocksAtLocation(const Point&);

    bool performMoveOperation(void (Graphics::Block::*)(), void (Graphics::Block::*)());

    void checkForStarsOnGoals();

    std::string _name;

    int _width;
    int _height;

    int _stepCounter;

    bool _completed;

    Graphics::Block _character;

    std::vector<Graphics::Block> _stars;
    std::vector<Graphics::Block> _goals;

    std::vector<std::vector<Graphics::Block> > _board;

    std::vector<std::tuple<Graphics::Block*, Graphics::Block*, void (Graphics::Block::*)()> > _moveStack;
};

#endif