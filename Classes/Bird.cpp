//
//  Bird.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-3.
//
//

#include "Bird.h"

void Bird::onEnter()
{
    Sprite::onEnter();
    setPosition(Point(getCol()*BOX_WIDTH,getRow()*BOX_HEIGHT));
    setScale(0.8);
}

Bird *Bird::create(int type)
{
    auto bird = new Bird();
    char fileName[50];
    sprintf(fileName,"box0%d_normal_02@2x.png", type);
    
    if (bird&&bird->initWithSpriteFrameName(fileName)) {
        bird->autorelease();
        bird->setBirdType(type);
        bird->__initEventListener();
        return bird;
    }
    
    CC_SAFE_DELETE(bird);
    return nullptr;
}

void Bird::setSelect(bool isSelect)
{
    m_bIsSelect = isSelect;
    char selectFileName[50];
    if(isSelect)
    {
        sprintf(selectFileName, "box0%d_normal_00@2x.png",m_iBirdType);
    }
    else
    {
        sprintf(selectFileName, "box0%d_normal_02@2x.png",m_iBirdType);
    }
    setSpriteFrame(selectFileName);
}

bool Bird::getSelect()
{
    return m_bIsSelect;
}

void Bird::bomb()
{
    
    char feather[50];
    sprintf(feather, "box0%d_feather@2x.png",m_iBirdType);
    
    auto featherNum = rand()%6+6;
    for (auto i=0; i<featherNum; i++) {
        auto featherSpr = SPRITE(feather);
        auto randomDegree = rand()%360;
        auto randomX = rand()%200-100;
        auto randomY = rand()%200-100;
        /**
         * 1.移动到指定的位置
         * 2.旋转到0度
         * 3.开始左右摇摆
         * 4.同时慢慢下落 透明度开始降低 
         * 5.完全不透明后 移除场景
         */
        auto moveBy = MoveBy::create(0.1f, Point(randomX,randomY)); // step 1
        auto rotateTo = RotateTo::create(rand()%2/10+0.2, 0); //step 2
        auto randomRotateDirection = rand()%2==0?1:-1;
        auto randomLeftDeg = randomRotateDirection*rand()%60;
        auto randomRightDeg = -randomLeftDeg;
        auto randomRotateDuration = rand()%2/10+0.2;
        auto rotateLeft = RotateBy::create(randomRotateDuration, randomLeftDeg);
        auto rotateRight = RotateBy::create(randomRotateDuration, randomRightDeg);
        
        auto rotateSeq = Sequence::create(rotateTo,rotateLeft,rotateLeft->reverse(),rotateRight, rotateRight->reverse(),rotateLeft,rotateLeft->reverse(),rotateRight, rotateRight->reverse(),nullptr);
        auto moveDown = MoveBy::create(2.0f, Point(0,-rand()%100)); //step3
        auto fadeOut = FadeOut::create(2.0f);
        auto spawn = Spawn::create(moveDown,fadeOut,rotateSeq, nullptr);
        auto featherSeq = Sequence::create(moveBy,spawn,CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, featherSpr)), nullptr);
        auto size = getContentSize()*getScale();
        auto offsetX = (0.5-getAnchorPoint().x)*size.width;
        auto offsetY = (0.5-getAnchorPoint().y)*size.height;
        featherSpr->setPosition(getPosition()+Point(offsetX,offsetY));
        featherSpr->setRotation(randomDegree);
        featherSpr->runAction(featherSeq);
        getParent()->addChild(featherSpr);
    }
    this->removeFromParent();
    
}

void Bird::__initEventListener()
{
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->setSwallowTouches(true);
    eventListener->onTouchBegan = [](Touch *touch,Event *event)->bool{
        auto target = static_cast<Bird*>(event->getCurrentTarget());
        auto locationNode = target->convertToNodeSpace(touch->getLocation());
        auto size = target->getContentSize();
        auto rect = Rect(0, 0, size.width, size.height);
        if (rect.containsPoint(locationNode)) {
            if(target->touchBeganHandler)
            {
                target->touchBeganHandler(target);
            }
            return true;
        }
        return false;
    };
    
    eventListener->onTouchEnded = [](Touch *touch,Event *event)->void{
        auto target = static_cast<Bird*>(event->getCurrentTarget());
        if(target->touchEndedHandler)
        {
            target->touchEndedHandler(target);
        }
    };
    
    eventListener->onTouchMoved = [](Touch *touch,Event *event)->void{
        auto target = static_cast<Bird*>(event->getCurrentTarget());
        if(target->touchMovedHandler)
        {
            target->touchMovedHandler(target);
        }
    };
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void Bird::setTouchBeganHandler(std::function<void (Bird *)> handler)
{
    this->touchBeganHandler = handler;
}

void Bird::setTouchMovedHandler(std::function<void (Bird *)> handler)
{
    this->touchMovedHandler = handler;
}

void Bird::setTouchEndedHandler(std::function<void (Bird *)> handler)
{
    this->touchEndedHandler = handler;
}

