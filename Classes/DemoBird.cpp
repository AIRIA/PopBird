//
//  DemoBird.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-3.
//
//

#include "DemoBird.h"

DemoBird *DemoBird::create(std::string fileName)
{
    auto bird = new DemoBird();
    if(bird&&bird->initWithSpriteFrameName(fileName))
    {
        bird->autorelease();
        return bird;
    }
    
    CC_SAFE_DELETE(bird);
    
    return nullptr;
}

void DemoBird::onEnter()
{
    Sprite::onEnter();
    auto randomDirection = rand()%2;
    if(randomDirection==0)
    {
        randomDirection = -1;
    }
    else
    {
        randomDirection = 1;
    }
    
    auto randomDuration = rand()%3+3;
    auto randomInstance = rand()%20+4;
    
    auto moveBy = MoveBy::create(randomDuration, Point(0,randomDirection*randomInstance));
    auto moveBack = moveBy->reverse();
    auto moveSeq = Sequence::create(moveBy,moveBack, nullptr);
    auto moveRepeat = RepeatForever::create(moveSeq);
    runAction(moveRepeat);
}
