#include "../include/LevelEx.h"
#include "../include/ResourceManager.h"

LevelEx::LevelEx() {

}

LevelEx::LevelEx(vector<vector<Block> > board, vector<Block> stars, vector<Block> goals, Block player, int width, int height) {
    _board = board;
    _stars = stars;
    _goals = goals;
    _character = player;
    _width = width;
    _height = height;
    _completed = false;
    _stepCounter = 0;
}

vector<Block*> LevelEx::getVisibleBlocks(SDL_Rect rect) {

    vector<Block*> result;

    for (auto &outer : _board) {

        for (auto &inner : outer) {

            if (inner.getBlockType() != BlockTypes::NONE) {
                if (inner.intersects(rect)) {
                    
                    result.push_back(&inner);

                    for (auto &goalsIs : _goals) {
                        if (goalsIs.getLocation() == inner.getLocation()) {
                            result.push_back(&goalsIs);
                        }
                    }

                    for (auto &starsIt : _stars) {
                        if (starsIt.getLocation() == inner.getLocation()) {
                            result.push_back(&starsIt);
                        }
                    }

                    if (_character.getLocation() == inner.getLocation()) {
                        result.push_back(&_character);
                    }
                }
            }           
        }

    }

    return result;
}

int LevelEx::getWidth() const {
    return _width;
}

int LevelEx::getHeight() const {
    return _height;
}

void LevelEx::movePlayerUp() {
    if (performMoveOperation(&Block::moveUp, &Block::moveDown)) {
        _stepCounter++;
        checkForStarsOnGoals();
    }
}

void LevelEx::movePlayerDown() {
    if (performMoveOperation(&Block::moveDown, &Block::moveUp)) {
        _stepCounter++;
        checkForStarsOnGoals();
    }
}

void LevelEx::movePlayerLeft() {  
    if (performMoveOperation(&Block::moveLeft, &Block::moveRight)) {
        _stepCounter++;
        checkForStarsOnGoals();
    }
}

void LevelEx::movePlayerRight() {
    if (performMoveOperation(&Block::moveRight, &Block::moveLeft)) {
        _stepCounter++;
        checkForStarsOnGoals();
    }
}

bool LevelEx::isCompleted() const {
    return _completed;
}

vector<Block*> LevelEx::getBlocksAtLocation(Point p) {

    vector<Block*> result;

    for (auto &outer : _board) {
        for (auto &inner : outer) {
            if (inner.getLocation() == p) {
                result.push_back(&inner);
            }
        }
    }

    for (auto &star : _stars) {
        if (star.getLocation() == p) {
            result.push_back(&star);
        }
    }

    return result;
}

bool LevelEx::performMoveOperation(void (Block::*actionToPerform)(), void (Block::*actionToUndo)()) {

    (_character.*actionToPerform)();

    _moveStack.push_back(std::make_tuple(&_character, nullptr, actionToUndo));

    for (auto &block : getBlocksAtLocation(_character.getLocation())) {

        if (block->getBlockType() == BlockTypes::WALL) {
            (_character.*actionToUndo)();

            _moveStack.pop_back();

            return false;

        } else if (block->getBlockType() == BlockTypes::STAR) {
            ((*block).*actionToPerform)();

            _moveStack.pop_back();

            _moveStack.push_back(std::make_tuple(&_character, block, actionToUndo));

            for (auto &block2 : getBlocksAtLocation(block->getLocation())) {

                if (block2->getBlockType() == BlockTypes::WALL || (block2->getBlockType() == BlockTypes::STAR && block2 != block)) {
                    (_character.*actionToUndo)();
                    ((*block).*actionToUndo)();

                    _moveStack.pop_back();

                    return false;
                }

            }

        }

    }

    return true;
}

void LevelEx::checkForStarsOnGoals() {

    int starsOnGoalsCounter = 0;

    for (auto &goal : _goals) {

        goal = Block(BlockTypes::GOAL, ResourceManager::getInstance()->getTexture("RedSelector.png"), goal.getLocation());

        for (auto &block : getBlocksAtLocation(goal.getLocation())) {

            if (block->getBlockType() == BlockTypes::STAR) {
                goal = Block(BlockTypes::GOAL, ResourceManager::getInstance()->getTexture("Selector.png"), goal.getLocation());

                starsOnGoalsCounter++;
            }

        }

    }

    if (starsOnGoalsCounter == _goals.size()) {
        _completed = true;
    } else {
        _completed = false;
    }

}

void LevelEx::undoLastMove() {

    if (!_moveStack.empty()) {

        std::tuple<Block*, Block*, void (Block::*)()> lastMove = _moveStack.at(_moveStack.size() - 1);

        (*(Block*)std::get<0>(lastMove).*(std::get<2>(lastMove)))();

        if ((Block*)std::get<1>(lastMove)) {
            (*(Block*)std::get<1>(lastMove).*(std::get<2>(lastMove)))();
            
            checkForStarsOnGoals();

        }

        _stepCounter--;

        _moveStack.pop_back();

    }

}