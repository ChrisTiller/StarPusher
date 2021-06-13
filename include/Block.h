#ifndef BLOCK_H
#define BLOCK_H

#include "GameObject.h"
#include "BlockTypes.h"

namespace Graphics {

    class Block : public GameObject {

    public:

        Block();
        Block(BlockTypes, Texture*);
        Block(BlockTypes, Texture*, Point);
        Block(BlockTypes, Texture*, int, int);

        BlockTypes getBlockType();
        
        virtual void moveUp();
        virtual void moveDown();
        virtual void moveLeft();
        virtual void moveRight();

    protected:

        BlockTypes _blockType;

    private:
            

    };

}

#endif
