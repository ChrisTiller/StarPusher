#include "../include/LevelEx.h"
#include "../include/ResourceManager.h"

LevelEx::LevelEx() {

}

LevelEx::LevelEx(std::vector<std::vector<Graphics::Block> > board, std::vector<Graphics::Block> stars, std::vector<Graphics::Block> goals, Graphics::Block player, int width, int height) {
    _board = board;
    _stars = stars;
    _goals = goals;
    _character = player;
    _width = width;
    _height = height;
    _completed = false;
    _stepCounter = 0;
}

std::vector<Graphics::Block*> LevelEx::getVisibleBlocks(SDL_Rect rect) {

    std::vector<Graphics::Block*> result;

    for (auto &outer : _board) {

        for (auto &inner : outer) {

            if (inner.getBlockType() != Graphics::BlockTypes::NONE) {
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
    if (performMoveOperation(&Graphics::Block::moveUp, &Graphics::Block::moveDown)) {
        _stepCounter++;
        checkForStarsOnGoals();
    }
}

void LevelEx::movePlayerDown() {
    if (performMoveOperation(&Graphics::Block::moveDown, &Graphics::Block::moveUp)) {
        _stepCounter++;
        checkForStarsOnGoals();
    }
}

void LevelEx::movePlayerLeft() {  
    if (performMoveOperation(&Graphics::Block::moveLeft, &Graphics::Block::moveRight)) {
        _stepCounter++;
        checkForStarsOnGoals();
    }
}

void LevelEx::movePlayerRight() {
    if (performMoveOperation(&Graphics::Block::moveRight, &Graphics::Block::moveLeft)) {
        _stepCounter++;
        checkForStarsOnGoals();
    }
}

bool LevelEx::isCompleted() const {
    return _completed;
}

std::vector<Graphics::Block*> LevelEx::getBlocksAtLocation(Graphics::Point p) {

    std::vector<Graphics::Block*> result;

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

bool LevelEx::performMoveOperation(void (Graphics::Block::*actionToPerform)(), void (Graphics::Block::*actionToUndo)()) {

    (_character.*actionToPerform)();

    _moveStack.push_back(std::make_tuple(&_character, nullptr, actionToUndo));

    for (auto &block : getBlocksAtLocation(_character.getLocation())) {

        if (block->getBlockType() == Graphics::BlockTypes::WALL) {
            (_character.*actionToUndo)();

            _moveStack.pop_back();

            return false;

        } else if (block->getBlockType() == Graphics::BlockTypes::STAR) {
            ((*block).*actionToPerform)();

            _moveStack.pop_back();

            _moveStack.push_back(std::make_tuple(&_character, block, actionToUndo));

            for (auto &block2 : getBlocksAtLocation(block->getLocation())) {

                if (block2->getBlockType() == Graphics::BlockTypes::WALL || (block2->getBlockType() == Graphics::BlockTypes::STAR && block2 != block)) {
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

        goal = Graphics::Block(Graphics::BlockTypes::GOAL, ResourceManager::getInstance()->getTexture("RedSelector.png"), goal.getLocation());

        for (auto &block : getBlocksAtLocation(goal.getLocation())) {

            if (block->getBlockType() == Graphics::BlockTypes::STAR) {
                goal = Graphics::Block(Graphics::BlockTypes::GOAL, ResourceManager::getInstance()->getTexture("Selector.png"), goal.getLocation());

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

        std::tuple<Graphics::Block*, Graphics::Block*, void (Graphics::Block::*)()> lastMove = _moveStack.at(_moveStack.size() - 1);

        (*(Graphics::Block*)std::get<0>(lastMove).*(std::get<2>(lastMove)))();

        if ((Graphics::Block*)std::get<1>(lastMove)) {
            (*(Graphics::Block*)std::get<1>(lastMove).*(std::get<2>(lastMove)))();
            
            checkForStarsOnGoals();

        }

        _stepCounter--;

        _moveStack.pop_back();

    }

}