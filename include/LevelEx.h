#ifndef LEVELEX_H
#define LEVELEX_H

#include <vector>
#include "Blocks/Block.h"

using namespace Graphics;
using std::vector;

class LevelEx {

public:

    LevelEx();

private:

    std::string _name;

    int _width;
    int _height;

    Block _character;

    vector<Block> _stars;
    vector<Block> _goals;

    vector<Block> _allBlocks;

    vector<vector<vector<Block> > > _board;
};

#endif