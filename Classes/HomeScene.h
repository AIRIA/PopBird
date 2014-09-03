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

class HomeScene:public BaseScene
{
public:
    virtual bool init();
    CREATE_FUNC(HomeScene);
    
private:
    void __initBackground();
    void __addBottomMenu();
    void __addMainMenu();
    void __addColorBirds();
};

#endif /* defined(__PopBird__HomeScene__) */
