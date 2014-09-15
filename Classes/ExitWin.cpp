//
//  ExitWin.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-5.
//
//

#include "ExitWin.h"

#define MOVE_GAP 300
#define EXIT_ANIMATE_TIME 0.3f

enum EXIT_TAG
{
    kExitPanelBg,
    kExitMenu
};

bool ExitWin::init()
{
    if(!Layer::init())
    {
        return false;
    }
    show();
    return true;
}

void ExitWin::show()
{
    auto winSize = Director::getInstance()->getWinSize();
    bgLayer = LayerColor::create(Color4B::BLACK, winSize.width, winSize.height);
    bgLayer->setOpacity(0);
    auto forbiddenEvent = EventListenerTouchOneByOne::create();
    forbiddenEvent->setSwallowTouches(true);
    forbiddenEvent->onTouchBegan = [](Touch *touch,Event *event)->bool{
        return true;
    };
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(forbiddenEvent, bgLayer);
    auto fadeTo = FadeTo::create(EXIT_ANIMATE_TIME, 128);
    addChild(bgLayer);
    bgLayer->runAction(fadeTo);
    
    auto exitPanelBg = Sprite::create("exit/exit_bg.png");
    exitPanelBg->setPosition(VisibleRect::center());
    exitPanelBg->setOpacity(0);
    exitPanelBg->setTag(kExitPanelBg);
    exitPanelBg->setScale(0);
    exitPanelBg->runAction(Spawn::create(FadeIn::create(EXIT_ANIMATE_TIME),EaseBackOut::create(ScaleTo::create(EXIT_ANIMATE_TIME, 1.0f)), nullptr));
    addChild(exitPanelBg);
    
    exitItem = MenuItemSprite::create(Sprite::create("exit/exit_yes_normal.png"), Sprite::create("exit/exit_yes_push.png"));
    cancleItem = MenuItemSprite::create(Sprite::create("exit/exit_no_normal.png"), Sprite::create("exit/exit_no_push.png"));
    
    exitItem->setPosition(VisibleRect::center()-Point(95,70)-Point(MOVE_GAP,0));
    cancleItem->setPosition(VisibleRect::center()+Point(95,-70)+Point(MOVE_GAP,0));
    exitItem->setOpacity(0);
    cancleItem->setOpacity(0);
    
    exitItem->runAction(Spawn::create(FadeIn::create(EXIT_ANIMATE_TIME),MoveBy::create(EXIT_ANIMATE_TIME, Point(MOVE_GAP,0)), nullptr));
    cancleItem->runAction(Spawn::create(FadeIn::create(EXIT_ANIMATE_TIME),MoveBy::create(EXIT_ANIMATE_TIME, Point(-MOVE_GAP,0)), nullptr));
    
    exitItem->setCallback([](Ref *pSender)->void{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
        exit(0);
#else
        Director::getInstance()->end();
#endif
    });
    
    cancleItem->setCallback([&](Ref *pSender)->void{
        this->hide();
    });
    
    auto exitMenu = Menu::create(exitItem,cancleItem,nullptr);
    exitMenu->setPosition(Point::ZERO);
    addChild(exitMenu);
    
    Director::getInstance()->getRunningScene()->addChild(this, 99999);
    
}

void ExitWin::hide()
{
    bgLayer->runAction(FadeOut::create(EXIT_ANIMATE_TIME));
    auto exitPanelBg = getChildByTag(kExitPanelBg);
    exitPanelBg->runAction(Spawn::create(FadeOut::create(EXIT_ANIMATE_TIME),EaseBackIn::create(ScaleTo::create(EXIT_ANIMATE_TIME, 0)), nullptr));
    exitItem->runAction(Spawn::create(FadeOut::create(EXIT_ANIMATE_TIME),MoveBy::create(EXIT_ANIMATE_TIME, Point(-MOVE_GAP,0)), nullptr));
    cancleItem->runAction(Spawn::create(FadeOut::create(EXIT_ANIMATE_TIME),MoveBy::create(EXIT_ANIMATE_TIME, Point(MOVE_GAP,0)), nullptr));
    runAction(Sequence::create(DelayTime::create(EXIT_ANIMATE_TIME),CCCallFuncN::create([](Node *obj)->void{
        obj->removeFromParent();
        isShowExit = false;
    }), nullptr));
}