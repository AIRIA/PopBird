//
//  PopScene.h
//  PopBird
//
//  Created by AIRIA on 14-9-3.
//
//

#ifndef __PopBird__PopScene__
#define __PopBird__PopScene__

#include "BaseScene.h"
#include "Bird.h"

class PopScene:public BaseScene
{
public:
    virtual bool init();
    CREATE_FUNC(PopScene);
    
protected:
    Vector<Bird*> m_vDashList;
    void _birdTouchHandler(Bird *bird);
    void _updateBirdsPosition();
private:
    Vector<Bird*> birdVec;
    void __initBackground();
    void __initBirds();
};

#endif /* defined(__PopBird__PopScene__) */
