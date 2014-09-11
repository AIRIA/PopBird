//
//  PauseLayer.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-5.
//
//

#include "PauseLayer.h"

#define ANIMATE_TIME 0.3f

bool PauseLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    getEventDispatcher()->addCustomEventListener(EVENT_PAUSE_GAME, [this](EventCustom *)->void{
        this->show();
    });
    
    return true;
}

void PauseLayer::onExit()
{
    getEventDispatcher()->removeEventListenersForTarget(this);
    Layer::onExit();
}

void PauseLayer::show()
{
    auto winSize = Director::getInstance()->getWinSize();
    bgLayer = LayerColor::create(Color4B::BLACK, winSize.width , winSize.height);
    bgLayer->setOpacity(0);
    bgLayer->runAction(FadeTo::create(ANIMATE_TIME, 128));
    auto forbiddenEvent = EventListenerTouchOneByOne::create();
    forbiddenEvent->setSwallowTouches(true);
    forbiddenEvent->onTouchBegan = [](Touch *touch,Event *event)->bool{
        return true;
    };
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(forbiddenEvent, bgLayer);
    addChild(bgLayer);
    
    wrapperNode = Node::create();
    auto menuBg = SPRITE("paused_bg.png");
    menuBg->setAnchorPoint(Point::ZERO);
//    auto quitItem = MenuItemSprite::create(SPRITE("paused_quit_normal.png"),SPRITE("paused_quit_push.png"));
    auto restartItem = MenuItemSprite::create(SPRITE("paused_restart_normal_china.png"),SPRITE("paused_restart_push_china.png"));
    auto resumeItem = MenuItemSprite::create(SPRITE("paused_resume_normal_china.png"),SPRITE("paused_resume_push_china.png"));
    auto saveItem = MenuItemSprite::create(SPRITE("paused_savequit_normal_china.png"),SPRITE("paused_savequit_push_china.png"));
    auto soundItem = MenuItemSprite::create(SPRITE("paused_sound_off.png"), SPRITE("paused_sound_on.png"));
    
    auto pauseMenu = Menu::create(restartItem,resumeItem,saveItem,soundItem,nullptr);
    resumeItem->setPosition(Point(380,280));
    restartItem->setPosition(Point(380,180));
    saveItem->setPosition(Point(380,80));
    soundItem->setPosition(Point(65,230));
    pauseMenu->setPosition(Point::ZERO);
    
    resumeItem->setCallback([&](Ref *pSender)->void{
        this->hide();
    });
    
    restartItem->setCallback([&](Ref *pSender)->void{
        this->hide();
        getEventDispatcher()->dispatchCustomEvent(EVENT_RESTART_GAME);
    });
    
    wrapperNode->addChild(menuBg);
    wrapperNode->addChild(pauseMenu);
    
    addChild(wrapperNode);
    wrapperNode->setPositionY(-463);
    wrapperNode->runAction(MoveTo::create(ANIMATE_TIME, Point::ZERO));
}

void PauseLayer::hide()
{
    auto moveTo = MoveTo::create(ANIMATE_TIME, Point(0,-463));
    auto fadeOut = FadeOut::create(ANIMATE_TIME);
    
    wrapperNode->runAction(Sequence::create(moveTo,CCCallFunc::create(CC_CALLBACK_0(Node::removeFromParent, wrapperNode)), nullptr));
    bgLayer->runAction(Sequence::create(fadeOut,CCCallFunc::create(CC_CALLBACK_0(Node::removeFromParent, bgLayer)), nullptr));
}