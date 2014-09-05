//
//  Bird.h
//  PopBird
//
//  Created by AIRIA on 14-9-3.
//
//

#ifndef __PopBird__Bird__
#define __PopBird__Bird__

#include "BaseSprite.h"

class Bird:public BaseSprite
{
public:
    virtual void onEnter();
    static Bird *create(int type);
    void setSelect(bool isSelect);
    bool getSelect();
    void bomb();
    
    
    CC_SYNTHESIZE(int, m_iBirdType, BirdType);
    CC_SYNTHESIZE(int, m_iRow, Row);
    CC_SYNTHESIZE(int, m_iCol, Col);
    CC_SYNTHESIZE(bool,m_bIsDestroy,IsDestroy);
    
private:
    bool m_bIsSelect;
};

#endif /* defined(__PopBird__Bird__) */
