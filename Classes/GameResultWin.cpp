//
//  GameResultWin.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-11.
//
//

#include "GameResultWin.h"
#include "HomeScene.h"

GameResultWin *GameResultWin::create(int level, std::string playTime, int birdDestroy, int score)
{
    auto resultWin = new GameResultWin();
    if (resultWin&&resultWin->init())
    {
        resultWin->autorelease();
        resultWin->m_iLevel = level;
        resultWin->m_sPlayTime = playTime;
        resultWin->m_iScore = score;
        resultWin->m_iBirdDestroy = birdDestroy;
        resultWin->__show();
        Director::getInstance()->getRunningScene()->addChild(resultWin);
        return resultWin;
    }
    
    CC_SAFE_DELETE(resultWin);
    return nullptr;
}

void GameResultWin::__show()
{
    auto winSize = Director::getInstance()->getWinSize();
    auto bg = LayerColor::create(Color4B::BLACK,winSize.width,winSize.height);
    bg->setOpacity(0);
    auto fadeToAct = FadeTo::create(0.3f, 128);
    bg->runAction(fadeToAct);
    addChild(bg);
    
    auto wrapper = Node::create();
    wrapper->setPosition(VisibleRect::center()+Point(0,600));
    addChild(wrapper);
    
    
    auto addLabelFunc = [&](int labelContent,Point pos)->void{
        auto label = Label::createWithBMFont("fonts/font_01.fnt", __String::createWithFormat("%d",labelContent)->getCString());
        label->setPosition(pos);
        label->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        wrapper->addChild(label);
    };
    
    auto windowBg = Sprite::createWithSpriteFrameName("stage_gameover_bg_china@2x.png");
    auto playTime = Label::createWithBMFont("fonts/font_01.fnt", m_sPlayTime);
    playTime->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    playTime->setPosition(Point(200,140));
    wrapper->addChild(windowBg);
    wrapper->addChild(playTime);
    
    addLabelFunc(m_iLevel,Point(200,200));
    addLabelFunc(m_iBirdDestroy,Point(200,83));
    addLabelFunc(m_iScore,Point(200,20));
    
    auto quitNormal = SPRITE("stage_gameover_quit_china@2x.png");
    quitNormal->setOpacity(0);
    
    auto restartNormal = SPRITE("stage_gameover_restart_china@2x.png");
    restartNormal->setOpacity(0);
    auto quitItem = MenuItemSprite::create(quitNormal, SPRITE("stage_gameover_quit_china@2x.png"));
    auto restartItem = MenuItemSprite::create(restartNormal, SPRITE("stage_gameover_restart_china@2x.png"));
    auto menu = Menu::create(quitItem,restartItem, nullptr);
    quitItem->setPosition(Point(-123,-242));
    quitItem->setCallback([](Ref *pSender)->void{
        HomeScene::create()->run();
    });
    restartItem->setPosition(Point(123,-242));
    restartItem->setCallback([&,wrapper,bg](Ref *pSender)->void{
        wrapper->runAction(EaseBackIn::create(MoveBy::create(0.3f, Point(0,900))));
        bg->runAction(Sequence::create(FadeOut::create(0.3f),CallFunc::create([&]()->void{
            getEventDispatcher()->dispatchCustomEvent(EVENT_RESTART_GAME);
        }), nullptr));
    });
    menu->setPosition(Point::ZERO);
    wrapper->addChild(menu);
    wrapper->runAction(EaseBackOut::create(MoveTo::create(0.3f, VisibleRect::center())));
    
    /* 储存分数前五名 */
    std::vector<int> records;
    for(auto i=0;i<5;i++)
    {
        char key[50];
        sprintf(key, "record_%d",i);
        auto record = SharePreference->getIntegerForKey(key, -1);
        if (record!=-1)
        {
            records.push_back(record);
        }
    }
    
    records.push_back(m_iScore);
    
    std::sort(records.begin(), records.end(), [](const int &a,const int &b)->bool{
        return a>b;
    });
    
    auto recordsNum = records.size();
    auto lenght = recordsNum>5?5:recordsNum;
    
    for (auto i=0; i<lenght; i++)
    {
        char key[50];
        sprintf(key, "record_%d",i);
        SharePreference->setIntegerForKey(key, records.at(i));
    }
    SharePreference->flush();
    Util::invokeNativeMethod(kMethodShowSpotAd);
}