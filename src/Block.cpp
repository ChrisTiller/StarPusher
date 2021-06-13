#include "../include/Block.h"

using namespace Graphics;

Block::Block() {
    _blockType = NONE;
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
    setLocation(getLocation().getX(), getLocation().getY() - 40);
}

void Block::moveDown() {
    setLocation(getLocation().getX(), getLocation().getY() + 40);
}

void Block::moveLeft() {
    setLocation(getLocation().getX() - getTexture()->getWidth(), getLocation().getY());
}

void Block::moveRight() {
    setLocation(getLocation().getX() + getTexture()->getWidth(), getLocation().getY());
}

BlockTypes Block::getBlockType() {
    return _blockType;
}