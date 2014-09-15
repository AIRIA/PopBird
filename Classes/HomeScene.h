//
//  HomeScene.h
//  PopBird
//
//  Created by AIRIA on 14-9-2.
//
//

#ifndef __PopBird__HomeScene__
#define __PopBird__HomeScene__

#include "BaseScene.h"
#include "ExitWin.h"

class HomeScene:public BaseScene
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual bool init();
    CREATE_FUNC(HomeScene);
    
private:
    ExitWin *exitWin;
    
    void __initBackground();
    void __addBottomMenu();
    void __addMainMenu();
    void __addColorBirds();
    void __showExit(float delta);
};

#endif /* defined(__PopBird__HomeScene__) */
