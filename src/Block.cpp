#include "../include/Block.h"

using namespace Graphics;

Block::Block() {
    _blockType = kNone;
}

Block::Block(BlockTypes blockType, Texture* texture) : GameObject(texture) {
    _blockType = blockType;
}

Block::Block(BlockTypes blockType, Texture* texture, Point location) : GameObject(texture, location) {
    _blockType = blockType;
}

Block::Block(BlockTypes blockType, Texture* texture, int x, int y) : GameObject(texture, x, y) {
    _blockType = blockType;
}

void Block::moveUp() {
    location_.y -= 40;
}

void Block::moveDown() {
    location_.y += 40;
}

void Block::moveLeft() {
    location_.x -= getTexture()->getWidth();
}

void Block::moveRight() {
    location_.x += getTexture()->getWidth();
}

BlockTypes Block::getBlockType() {
    return _blockType;
}