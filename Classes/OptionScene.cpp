//
//  OptionScene.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-12.
//
//

#include "OptionScene.h"
#include "HomeScene.h"

bool OptionScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }
    
    auto bg = Sprite::create("option/option_bg_RETINA.png");
    bg->setPosition(VisibleRect::center());
    addChild(bg);
    
    auto homeButton = MenuItemSprite::create(SPRITE("scores_home@2x.png"), SPRITE("scores_home@2x.png"));
    homeButton->setPosition(VisibleRect::rightBottom()-Point(68,-68));
    homeButton->setCallback([](Ref *pSender)->void{
        HomeScene::create()->run();
    });
    
    auto soundItem = MenuItemToggle::createWithCallback([](Ref *pSender)->void{}, MenuItemSprite::create(SPRITE("option_button_on@2x.png"), SPRITE("option_button_on@2x.png")), MenuItemSprite::create(SPRITE("option_button_off@2x.png"), SPRITE("option_button_off@2x.png")), nullptr);
    soundItem->setPosition(Point(500,800));
    
    auto vibrateItem = MenuItemToggle::createWithCallback([](Ref *pSender)->void{}, MenuItemSprite::create(SPRITE("option_button_on@2x.png"), SPRITE("option_button_on@2x.png")), MenuItemSprite::create(SPRITE("option_button_off@2x.png"), SPRITE("option_button_off@2x.png")), nullptr);
    vibrateItem->setPosition(Point(500,750));
    
    soundItem->setCallback([](Ref *pSender)->void{
        auto item = static_cast<MenuItemToggle*>(pSender);
        auto res = item->getSelectedIndex()==0?true:false;
        SharePreference->setBoolForKey(KEY_SOUND_ENABLE, res);
        SharePreference->flush();
    });
    
    vibrateItem->setCallback([](Ref *pSender)->void{
        auto item = static_cast<MenuItemToggle*>(pSender);
        auto res = item->getSelectedIndex()==0?true:false;
        SharePreference->setBoolForKey(KEY_VIBRATION_ENABLE, res);
        SharePreference->flush();
    });
    
    
    
    auto menu = Menu::create(homeButton,soundItem,vibrateItem,nullptr);
    menu->setPosition(Point::ZERO);
    addChild(menu);
    
    
    auto soundAndVibrate = SPRITE("option_soundandvibration_china@2x.png");
    soundAndVibrate->setPosition(VisibleRect::top()-Point(0,100));
    addChild(soundAndVibrate);
    
    auto sound = SPRITE("option_sound_china@2x.png");
    sound->setPosition(Point(100,800));
    addChild(sound);
    
    auto vibrate = SPRITE("option_vibration_china@2x.png");
    vibrate->setPosition(Point(100,750));
    addChild(vibrate);
    
    auto soundSelectIdx = SharePreference->getBoolForKey(KEY_SOUND_ENABLE)?0:1;
    soundItem->setSelectedIndex(soundSelectIdx);
    
    auto vibrationSelectIdx = SharePreference->getBoolForKey(KEY_VIBRATION_ENABLE)?0:1;
    vibrateItem->setSelectedIndex(vibrationSelectIdx);
    
    return true;
}