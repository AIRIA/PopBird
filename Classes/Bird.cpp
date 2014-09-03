//
//  Bird.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-3.
//
//

#include "Bird.h"

void Bird::onEnter()
{
    Sprite::onEnter();
    setPosition(Point(getCol()*BOX_WIDTH,getRow()*BOX_HEIGHT));
    setScale(0.8);
}

Bird *Bird::create(int type)
{
    auto bird = new Bird();
    char fileName[50];
    sprintf(fileName,"box0%d_normal_02@2x.png", type);
    
    if (bird&&bird->initWithSpriteFrameName(fileName)) {
        bird->autorelease();
        bird->setBirdType(type);
        bird->__initEventListener();
        return bird;
    }
    
    CC_SAFE_DELETE(bird);
    return nullptr;
}

void Bird::setSelect(bool isSelect)
{
    char selectFileName[50];
    sprintf(selectFileName, "box0%d_normal_00@2x.png",m_iBirdType);
    setSpriteFrame(selectFileName);
}

void Bird::bomb()
{
    
}

void Bird::__initEventListener()
{
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->setSwallowTouches(true);
    eventListener->onTouchBegan = [](Touch *touch,Event *event)->bool{
        auto target = static_cast<Bird*>(event->getCurrentTarget());
        auto locationNode = target->convertToNodeSpace(touch->getLocation());
        auto size = target->getContentSize();
        auto rect = Rect(0, 0, size.width, size.height);
        if (rect.containsPoint(locationNode)) {
            if(target->touchBeganHandler)
            {
                target->touchBeganHandler(target);
            }
            return true;
        }
        return false;
    };
    
    eventListener->onTouchEnded = [](Touch *touch,Event *event)->void{
        auto target = static_cast<Bird*>(event->getCurrentTarget());
        if(target->touchEndedHandler)
        {
            target->touchEndedHandler(target);
        }
    };
    
    eventListener->onTouchMoved = [](Touch *touch,Event *event)->void{
        auto target = static_cast<Bird*>(event->getCurrentTarget());
        if(target->touchMovedHandler)
        {
            target->touchMovedHandler(target);
        }
    };
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void Bird::setTouchBeganHandler(std::function<void (Bird *)> handler)
{
    this->touchBeganHandler = handler;
}

void Bird::setTouchMovedHandler(std::function<void (Bird *)> handler)
{
    this->touchMovedHandler = handler;
}

void Bird::setTouchEndedHandler(std::function<void (Bird *)> handler)
{
    this->touchEndedHandler = handler;
}

