//
//  PauseSprite.h
//  PopBird
//
//  Created by AIRIA on 14-9-5.
//
//

#ifndef __PopBird__PauseSprite__
#define __PopBird__PauseSprite__

#include "BaseSprite.h"

class PauseSprite:public BaseSprite
{
public:
    virtual void onEnter();
    static PauseSprite *create();
};

#endif /* defined(__PopBird__PauseSprite__) */
