//
//  PopScene.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-3.
//
//

#include "PopScene.h"

bool PopScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_asset/stage_CN_RETINA.plist");
    
    __initBackground();
    __initBirds();
    return true;
}

void PopScene::__initBackground()
{
    auto bg = Sprite::create("game_asset/stage_bg_RETINA.png");
    bg->setAnchorPoint(Point::ZERO);
    addChild(bg);
    
    auto backboard = Sprite::create("game_asset/stage_tree_RETINA.png");
    backboard->setAnchorPoint(Point::ZERO);
    addChild(backboard);
    auto targetPos = -backboard->getContentSize().height;
    backboard->setPositionY(targetPos);
    auto moveAct = MoveTo::create(0.5, Point(0,0));
    backboard->runAction(moveAct);
}

void PopScene::__initBirds()
{
    auto birdWrapperNode = Node::create();
    for (auto i=0; i<ROW*COL; i++) {
        auto bird = Bird::create(rand()%8);
        auto row = i/COL;
        auto col = i%COL;
        bird->setAnchorPoint(Point::ZERO);
        bird->setRow(row);
        bird->setCol(col);
        bird->setTouchBeganHandler(std::bind(&PopScene::_birdTouchHandler,this,std::placeholders::_1));
        birdVec.pushBack(bird);
        birdWrapperNode->addChild(bird);
    }
    birdWrapperNode->setPosition(Point::ZERO);
    addChild(birdWrapperNode);
    birdWrapperNode->setPositionY(-800);
    auto moveAct = MoveTo::create(0.5f, Point::ZERO);
    birdWrapperNode->runAction(Sequence::create(DelayTime::create(0.4f),moveAct, NULL));
}

void PopScene::_birdTouchHandler(Bird *bird)
{
    if (m_vCloseList.size()!=0) {
        auto it = m_vCloseList.begin();
        while (it!=m_vCloseList.end()) {
            (*it)->bomb();
            it++;
        }
        m_vCloseList.clear();
        return;
    }
    
    Vector<Bird*> selectBirdVec;
    selectBirdVec.pushBack(bird);
    m_vCloseList.pushBack(bird);
    bird->setSelect(true);
    while (selectBirdVec.size()!=0)
    {
        auto bird = selectBirdVec.at(0);
        Bird *selectBird = bird;
        auto row = bird->getRow();
        auto col = bird->getCol();
        
        for(auto i=row-1;i<=row+1;i++)
        {
            if(i<0 || i>=ROW)
            {
                continue;
            }
            for (auto j=col-1; j<=col+1; j++)
            {
                if((i!=row && j!=col )||j<0||j>=COL)
                {
                    continue;
                }
                auto idx = i*COL+j;
                auto neighbor = birdVec.at(idx);
                if (neighbor!=selectBird && neighbor->getBirdType()==bird->getBirdType())
                {
                    if (neighbor->getSelect())
                    {
                        continue;
                    }
                    else
                    {
                        neighbor->setSelect(true);
                        selectBirdVec.pushBack(neighbor);
                    }
                    m_vCloseList.pushBack(neighbor);
                }
            }
        }
        selectBirdVec.eraseObject(selectBird);
    }
}





