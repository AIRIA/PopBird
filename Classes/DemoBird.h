//
//  DemoBird.h
//  PopBird
//
//  Created by AIRIA on 14-9-3.
//
//

#ifndef __PopBird__DemoBird__
#define __PopBird__DemoBird__

#include "Bird.h"

class DemoBird:public Bird
{
public:
    virtual void onEnter();
    static DemoBird *create(std::string fileName);
    void shake();
private:
    int m_iShakeTimes = 0;
};

#endif /* defined(__PopBird__DemoBird__) */
