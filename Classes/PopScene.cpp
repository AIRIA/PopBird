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
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_asset/Character_RETINA.plist");
    
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
        bird->setTouchBeganHandler([](Bird *bird)->void{
            bird->setSelect(true);
        });
        birdVec.pushBack(bird);
        birdWrapperNode->addChild(bird);
    }
    birdWrapperNode->setPosition(Point::ZERO);
    addChild(birdWrapperNode);
    birdWrapperNode->setPositionY(-800);
    auto moveAct = MoveTo::create(0.5f, Point::ZERO);
    birdWrapperNode->runAction(Sequence::create(DelayTime::create(0.4f),moveAct, NULL));
}