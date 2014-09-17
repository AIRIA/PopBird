//
//  PauseLayer.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-5.
//
//

#include "PauseLayer.h"
#include "HomeScene.h"
#include "BaseSprite.h"

#define ANIMATE_TIME 0.3f

bool PauseLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    getEventDispatcher()->addCustomEventListener(EVENT_PAUSE_GAME, [&](EventCustom *)->void{
        this->show();
    });
    
    return true;
}

void PauseLayer::onExit()
{
    getEventDispatcher()->removeEventListenersForTarget(this);
    getEventDispatcher()->removeCustomEventListeners(EVENT_PAUSE_GAME);
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
    
    auto soundToogleItem = MenuItemToggle::createWithCallback([](Ref *pSender)->void{}, MenuItemSprite::create(SPRITE("paused_sound_on.png"), SPRITE("paused_sound_on.png")),MenuItemSprite::create(SPRITE("paused_sound_off.png"), SPRITE("paused_sound_off.png")),nullptr);
    

    
    soundToogleItem->setCallback([](Ref *pSender)->void{
        auto toogleItem = static_cast<MenuItemToggle*>(pSender);
        auto idx = toogleItem->getSelectedIndex();
        if (idx==0)
        {
            SharePreference->setBoolForKey(KEY_SOUND_ENABLE, true);
        }
        else
        {
            SharePreference->setBoolForKey(KEY_SOUND_ENABLE, false);
        }
        
        SharePreference->flush();
    });
    
    auto pauseMenu = Menu::create(restartItem,resumeItem,saveItem,soundToogleItem,nullptr);
    resumeItem->setPosition(Point(380,280));
    restartItem->setPosition(Point(380,180));
    saveItem->setPosition(Point(380,80));
    soundToogleItem->setPosition(Point(65,230));
    pauseMenu->setPosition(Point::ZERO);
    
    saveItem->setCallback([](Ref *pSender)->void{
        HomeScene::create()->run();
    });
    
    resumeItem->setCallback([&](Ref *pSender)->void{
        this->hide();
    });
    
    restartItem->setCallback([&](Ref *pSender)->void{
        this->hide();
        getEventDispatcher()->dispatchCustomEvent(EVENT_RESTART_GAME);
    });
    
    auto help = BaseSprite::create("game_asset/stage_dimm2_RETINA.png");
    help->setTouchEndedHandler([](BaseSprite*)->void{
        Util::invokeNativeMethod(kMethodShowFeedBack);
    });
    help->setPosition(Point(70,100));
    help->setOpacity(0);
    
    wrapperNode->addChild(menuBg);
    wrapperNode->addChild(pauseMenu);
    wrapperNode->addChild(help);
    addChild(wrapperNode);
    wrapperNode->setPositionY(-463);
    wrapperNode->runAction(MoveTo::create(ANIMATE_TIME, Point::ZERO));
    
    auto soundSelectIdx = SharePreference->getBoolForKey(KEY_SOUND_ENABLE)?0:1;
    soundToogleItem->setSelectedIndex(soundSelectIdx);
    
}

void PauseLayer::hide()
{
    auto moveTo = MoveTo::create(ANIMATE_TIME, Point(0,-463));
    auto fadeOut = FadeOut::create(ANIMATE_TIME);
    
    wrapperNode->runAction(Sequence::create(moveTo,CCCallFunc::create(CC_CALLBACK_0(Node::removeFromParent, wrapperNode)), nullptr));
    bgLayer->runAction(Sequence::create(fadeOut,CCCallFunc::create(CC_CALLBACK_0(Node::removeFromParent, bgLayer)), nullptr));
}

