//
//  BaseLayer.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-2.
//
//

#include "BaseLayer.h"

bool BaseLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    m_winSize = Director::getInstance()->getWinSize();
    return true;
}