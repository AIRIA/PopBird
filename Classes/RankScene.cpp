//
//  RankScene.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-12.
//
//

#include "RankScene.h"
#include "HomeScene.h"

bool RankScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("rank/highscore_RETINA.plist");
    
    auto bgColor = LayerColor::create(Color4B::WHITE, m_winSize.width, m_winSize.height);
    addChild(bgColor);
    
    auto bg = Sprite::create("rank/highscore_bg_RETINA.png");
    bg->setPosition(VisibleRect::center());
    addChild(bg);
    
    
    auto homeItem = MenuItemSprite::create(SPRITE("score_home_normal@2x.png"), SPRITE("score_home_push@2x.png"));
    homeItem->setCallback([](Ref *pSender)->void{
        HomeScene::create()->run();
    });
    auto menu = Menu::create(homeItem,nullptr);
    homeItem->setPosition(Point(500,115));
    menu->setPosition(Point::ZERO);
    addChild(menu);
    
    for (auto i=0; i<5; i++) {
        auto record = SPRITE("score_board_bar@2x.png");
        record->setPosition(Point(m_winSize.width/2,750-i*125));
        auto label = Label::createWithTTF(__String::createWithFormat("%d",i+1)->getCString(),"fonts/SAF.otf", 34);
        label->setAnchorPoint(Point::ZERO);
        label->setPosition(Point(30,10));
        record->addChild(label);
        addChild(record);
    }
    
    return true;
}