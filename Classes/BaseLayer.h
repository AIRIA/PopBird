//
//  BaseLayer.h
//  PopBird
//
//  Created by AIRIA on 14-9-2.
//
//

#ifndef __PopBird__BaseLayer__
#define __PopBird__BaseLayer__

#include "Headers.h"

class BaseLayer:public Layer
{
public:
    Size m_winSize;
    virtual bool init();
    CREATE_FUNC(BaseLayer);
};

#endif /* defined(__PopBird__BaseLayer__) */
