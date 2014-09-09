//
//  ExitWin.h
//  PopBird
//
//  Created by AIRIA on 14-9-5.
//
//

#ifndef __PopBird__ExitWin__
#define __PopBird__ExitWin__

#include "Headers.h"

class ExitWin:public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(ExitWin);
    void show();
    void hide();
private:
    LayerColor *bgLayer;
    MenuItemSprite *cancleItem;
    MenuItemSprite *exitItem;
};

#endif /* defined(__PopBird__ExitWin__) */
