//
//  BaseSprite.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-5.
//
//

#include "BaseSprite.h"

BaseSprite *BaseSprite::create(std::string fileName)
{
    auto sprite = new BaseSprite();
    if (sprite&&sprite->initWithFile(fileName)) {
        sprite->autorelease();
        sprite->__initEventListener();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void BaseSprite::__initEventListener()
{
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->setSwallowTouches(true);
    eventListener->onTouchBegan = [](Touch *touch,Event *event)->bool{
        auto target = static_cast<BaseSprite*>(event->getCurrentTarget());
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
        auto target = static_cast<BaseSprite*>(event->getCurrentTarget());
        if(target->touchEndedHandler)
        {
            target->touchEndedHandler(target);
        }
    };
    
    eventListener->onTouchMoved = [](Touch *touch,Event *event)->void{
        auto target = static_cast<BaseSprite*>(event->getCurrentTarget());
        if(target->touchMovedHandler)
        {
            target->touchMovedHandler(target);
        }
    };
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void BaseSprite::setTouchBeganHandler(std::function<void (BaseSprite *)> handler)
{
    this->touchBeganHandler = handler;
}

void BaseSprite::setTouchMovedHandler(std::function<void (BaseSprite *)> handler)
{
    this->touchMovedHandler = handler;
}

void BaseSprite::setTouchEndedHandler(std::function<void (BaseSprite *)> handler)
{
    this->touchEndedHandler = handler;
}

