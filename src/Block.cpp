#include "../include/Blocks/Block.h"

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
    setLocation(getLocation().getX(), getLocation().getY() - getTexture()->getHeight());
}

void Block::moveDown() {
    setLocation(getLocation().getX(), getLocation().getY() + getTexture()->getHeight());
}

void Block::moveLeft() {
    setLocation(getLocation().getX() - getTexture()->getWidth(), getLocation().getY());
}

void Block::moveRight() {
    setLocation(getLocation().getX() + getTexture()->getWidth(), getLocation().getY());
}