//
//  PauseLayer.h
//  PopBird
//
//  Created by AIRIA on 14-9-5.
//
//

#ifndef __PopBird__PauseLayer__
#define __PopBird__PauseLayer__

#include "Headers.h"

class PauseLayer:public Layer
{
public:
    virtual void onExit();
    virtual bool init();
    CREATE_FUNC(PauseLayer);
    void show();
    void hide();
protected:
    LayerColor *bgLayer;
    Node *wrapperNode;
};

#endif /* defined(__PopBird__PauseLayer__) */
