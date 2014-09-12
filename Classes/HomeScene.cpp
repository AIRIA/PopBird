//
//  HomeScene.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-2.
//
//

#include "HomeScene.h"
#include "PopScene.h"
#include "DemoBird.h"
#include "ExitWin.h"
#include "GameResultWin.h"
#include "OptionScene.h"
#include "RankScene.h"

bool HomeScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main_menu/main_bg_a_RETINA.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main_menu/main_bg_b_RETINA.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main_menu/mainmenu_a_CN_RETINA.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main_menu/mainmenu_a_RETINA.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main_menu/mainmenu_b_CN_RETINA.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_asset/Character_RETINA.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_asset/trophy_RETINA.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pause/paused_RETINA.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pause/paused_CN_RETINA.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fonts/stage_RETINA.plist");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("option/option_CN_RETINA.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("option/option_RETINA.plist");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_over/gameover_CN_RETINA.plist");
    
    
    /* preload sounds */
    
    for(auto idx=1;idx<10;idx++)
    {
        char name[50];
        sprintf(name, "sounds/effects/%d.mp3",idx);
        SimpleAudioEngine::getInstance()->preloadEffect(name);
    }
    
    __initBackground();
    __addBottomMenu();
    __addColorBirds();
    
    return true;
}

void HomeScene::__initBackground()
{
    auto createSpriteFun = [](std::string sprName,Point anchorPos,Point sprPos,Node *parent,bool isDemoBird=false,int type=0)->Sprite*
    {
        Sprite  *spr = nullptr;
        if (isDemoBird)
        {
            auto bird = DemoBird::create(sprName);
            bird->setBirdType(type);
            spr = bird;
        }
        else
        {
            spr = SPRITE(sprName);
        }
        spr->setAnchorPoint(anchorPos);
        spr->setPosition(sprPos);
        parent->addChild(spr);
        return spr;
    };
    
    createSpriteFun("main_bg_c@2x.png",Point::ANCHOR_MIDDLE_TOP,VisibleRect::top(),this);
    createSpriteFun("main_trees_b@2x.png",Point::ANCHOR_TOP_RIGHT,VisibleRect::rightTop(),this);
    createSpriteFun("main_trees_a@2x.png",Point::ANCHOR_TOP_LEFT,VisibleRect::leftTop(),this);

    for(auto i=0;i<6;i++)
    {
        /* 旋转的光 */
        auto light = createSpriteFun("main_bg_light@2x.png",Point::ANCHOR_MIDDLE,VisibleRect::center()+Point(0,100),this);
        light->setScale(2);
        light->setRotation(30*i);
        
        BlendFunc cbl = {GL_DST_COLOR, GL_ONE};
        light->setBlendFunc(cbl);
        auto rotateAction = RotateBy::create(1, 30);
        light->runAction(RepeatForever::create(rotateAction));
    }
    createSpriteFun("main_bg_b@2x.png",Point::ANCHOR_MIDDLE_BOTTOM,Point(m_winSize.width/2,94),this);
    __addMainMenu();
    createSpriteFun("main_bg_a@2x.png",Point::ANCHOR_MIDDLE_BOTTOM,VisibleRect::bottom(),this);
    /* 添加彩色小鸟 */
    
    createSpriteFun("main_cha_white@2x.png",Point::ANCHOR_MIDDLE,Point(165,550),this,true,6);
    createSpriteFun("main_cha_blue@2x.png",Point::ANCHOR_MIDDLE,Point(130,420),this,true,0);
    createSpriteFun("main_cha_orange@2x.png",Point::ANCHOR_MIDDLE,Point(70,300),this,true,2);
    createSpriteFun("main_cha_pink@2x.png",Point::ANCHOR_MIDDLE,Point(210,450),this,true,3);
    createSpriteFun("main_cha_red@2x.png",Point::ANCHOR_MIDDLE,Point(180,300),this,true,5);
    createSpriteFun("main_cha_purple@2x.png",Point::ANCHOR_MIDDLE,Point(100,200),this,true,4);
    createSpriteFun("main_cha_yellow@2x.png",Point::ANCHOR_MIDDLE,Point(560,100),this,true,7);
}

void HomeScene::__addBottomMenu()
{
    auto settingMenu = MenuItemSprite::create(SPRITE("main_option_china@2x.png"), SPRITE("main_option_push_china@2x.png"));
    settingMenu->setCallback([](Ref *pSender)->void{
        OptionScene::create()->run();
    });
    
    auto rankMenu = MenuItemSprite::create(SPRITE("main_rank_china@2x.png"), SPRITE("main_rank_push_china@2x.png"));
    
    rankMenu->setCallback([](Ref *pSender)->void{
        RankScene::create()->run();
    });
    auto bottomMenu = Menu::create(settingMenu,rankMenu, nullptr);
    bottomMenu->setPosition(Point::ZERO);
    settingMenu->setPosition(Point(65,120));
    rankMenu->setPosition(Point(195,120));
    addChild(bottomMenu);
}

void HomeScene::__addMainMenu()
{
    auto degree = -5;
    auto wrapperNode = Node::create();
    auto menuBg = Sprite::createWithSpriteFrameName("main_menu_bg@2x.png");
    menuBg->setRotation(degree);
    menuBg->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    wrapperNode->addChild(menuBg);
    menuBg->setPosition(Point(m_winSize.width-180,80));
    this->addChild(wrapperNode);
    
    auto createMenu = [](Sprite *normal,Sprite *push,float rotation,Point pos)->MenuItemSprite*{
        auto menu = MenuItemSprite::create(normal,push);
        menu->setPosition(pos);
        menu->setRotation(rotation);
        return menu;
    };
    
    auto menu1 = createMenu(SPRITE("main_menu_classic_china@2x.png"),SPRITE("main_menu_classic_push_china@2x.png"),degree,Point(m_winSize.width-210,500));
    auto menu2 = createMenu(SPRITE("main_menu_icebreak_china@2x.png"),SPRITE("main_menu_icebreak_push_china@2x.png"),degree,Point(m_winSize.width-200,360));
    auto menu3 = createMenu(SPRITE("main_menu_pandora_china@2x.png"),SPRITE("main_menu_pandora_push_china@2x.png"),degree,Point(m_winSize.width-180,220));
    /* 进入消消乐模式 */
    menu1->setCallback([](Ref *pSender)->void{
        PopScene::create()->run();
    });
    
    menu2->setCallback([](Ref *pSender)->void{
        ExitWin::create();
    });
    
    menu3->setCallback([](Ref *pSender)->void{
        GameResultWin::create(1,"12:32", 234, 6700);
    });
    
    
    
    auto mainMenu = Menu::create(menu1,menu2,menu3,nullptr);
    mainMenu->setPosition(Point::ZERO);
    wrapperNode->addChild(mainMenu);
}

void HomeScene::__addColorBirds()
{
    
}
