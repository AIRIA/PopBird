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

#define SPRITE(url) Sprite::createWithSpriteFrameName(url)

#define BOX_WIDTH 62
#define BOX_HEIGHT 65
#define ROW 10
#define COL 10

#define EVENT_PAUSE_GAME "event_pause_game"
#define EVENT_RESTART_GAME "event_restart_game"

#endif
