//
//  Util.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-12.
//
//

#include "Util.h"



void Util::init()
{
    auto exist = SharePreference->isXMLFileExist();
    if (!exist)
    {
        SharePreference->setBoolForKey(KEY_SOUND_ENABLE, true);
        SharePreference->setBoolForKey(KEY_VIBRATION_ENABLE, false);
    }
}

void Util::playEffect(std::string filePath,bool repeate)
{
    if (SharePreference->getBoolForKey(KEY_SOUND_ENABLE))
    {
        SimpleAudioEngine::getInstance()->playEffect(filePath.c_str(),repeate);
    }
}

void Util::playSound(std::string filePath,bool repeate)
{
    if (SharePreference->getBoolForKey(KEY_SOUND_ENABLE))
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(filePath.c_str(),repeate);
    }
}