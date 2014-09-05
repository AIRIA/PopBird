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
        bird->__initEventListener();
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
    setTouchEndedHandler([](BaseSprite *bird)->void{
        auto demoBird = static_cast<DemoBird*>(bird);
        demoBird->shake();
        demoBird->getEventDispatcher()->removeEventListenersForTarget(demoBird);
    });
}

void DemoBird::shake()
{
    this->m_iShakeTimes++;
    if(m_iShakeTimes==10)
    {
        bomb();
        return;
    }
    auto posX = rand()%3-3;
    auto posY = rand()%3-3;
    auto moveBy = MoveBy::create(rand()%1/20+0.05, Point(posX,posY));
    auto moveBack = moveBy->reverse();
    auto moveCallback = CCCallFunc::create(CC_CALLBACK_0(DemoBird::shake, this));
    runAction(Sequence::create(moveBy,moveBack,moveCallback,nullptr));
}










