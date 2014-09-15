//
//  Headers.h
//  PopBird
//
//  Created by AIRIA on 14-9-2.
//
//

#ifndef PopBird_Headers_h
#define PopBird_Headers_h

#include "cocos2d.h"
#include "VisibleRect.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

extern bool isShowExit;

#define SPRITE(url) Sprite::createWithSpriteFrameName(url)

#define BOX_WIDTH 62
#define BOX_HEIGHT 65
#define ROW 10
#define COL 10

#define EVENT_PAUSE_GAME "event_pause_game"
#define EVENT_RESTART_GAME "event_restart_game"
#define EVENT_SHOW_EXIT "event_show_exit"

#define KEY_SOUND_ENABLE "sound_enable"
#define KEY_VIBRATION_ENABLE "vibration_enable"

#define SharePreference UserDefault::getInstance()

#endif
