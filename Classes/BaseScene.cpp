//
//  BaseScene.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-2.
//
//

#include "BaseScene.h"

void BaseScene::run()
{
    auto scene = Scene::create();
    scene->addChild(this);
    auto runningScene = Director::getInstance()->getRunningScene();
    if(runningScene==nullptr)
    {
        Director::getInstance()->runWithScene(scene);
    }
    else
    {
        Director::getInstance()->replaceScene(scene);
    }
}