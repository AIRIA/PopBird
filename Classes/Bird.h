//
//  Bird.h
//  PopBird
//
//  Created by AIRIA on 14-9-3.
//
//

#ifndef __PopBird__Bird__
#define __PopBird__Bird__

#include "Headers.h"

class Bird:public Sprite
{
public:
    virtual void onEnter();
    static Bird *create(int type);
    void setSelect(bool isSelect);
    bool getSelect();
    void bomb();
    
    void setTouchEndedHandler(std::function<void(Bird*)> handler);
    void setTouchMovedHandler(std::function<void(Bird*)> handler);
    void setTouchBeganHandler(std::function<void(Bird*)> handler);
    
protected:
    std::function<void(Bird*)> touchEndedHandler;
    std::function<void(Bird*)> touchMovedHandler;
    std::function<void(Bird*)> touchBeganHandler;
    void __initEventListener();
    
    CC_SYNTHESIZE(int, m_iBirdType, BirdType);
    CC_SYNTHESIZE(int, m_iRow, Row);
    CC_SYNTHESIZE(int, m_iCol, Col);
    CC_SYNTHESIZE(bool,m_bIsDestroy,IsDestroy);
    
private:
    bool m_bIsSelect;
};

#endif /* defined(__PopBird__Bird__) */
