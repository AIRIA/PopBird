//
//  PauseSprite.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-5.
//
//

#include "PauseSprite.h"

PauseSprite *PauseSprite::create()
{
    auto pauseSpr = new PauseSprite();
    if(pauseSpr && pauseSpr->initWithFile("game_asset/stage_dimm2_RETINA.png"))
    {
        pauseSpr->autorelease();
        pauseSpr->__initEventListener();
        return pauseSpr;
    }
    CC_SAFE_DELETE(pauseSpr);
    return nullptr;
}

void PauseSprite::onEnter()
{
    BaseSprite::onEnter();
    setTouchEndedHandler([](BaseSprite *sprite)->void{
        sprite->getEventDispatcher()->dispatchCustomEvent(EVENT_PAUSE_GAME);
    });
}