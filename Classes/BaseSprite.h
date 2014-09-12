//
//  BaseSprite.h
//  PopBird
//
//  Created by AIRIA on 14-9-5.
//
//

#ifndef __PopBird__BaseSprite__
#define __PopBird__BaseSprite__

#include "Headers.h"

class BaseSprite:public Sprite
{
public:
    
    void setTouchEndedHandler(std::function<void(BaseSprite*)> handler);
    void setTouchMovedHandler(std::function<void(BaseSprite*)> handler);
    void setTouchBeganHandler(std::function<void(BaseSprite*)> handler);
    
protected:
    std::function<void(BaseSprite*)> touchEndedHandler;
    std::function<void(BaseSprite*)> touchMovedHandler;
    std::function<void(BaseSprite*)> touchBeganHandler;

    void __initEventListener();
    
};

#endif /* defined(__PopBird__BaseSprite__) */
