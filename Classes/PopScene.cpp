//
//  PopScene.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-3.
//
//

#include "PopScene.h"
#include "PauseSprite.h"
#include "PauseLayer.h"
#include "GameResultWin.h"

enum PopSceneTAG
{
    kTagPrevLabel,
    kTagPrevLabelMark,
    kTagRewardLabel,
    kTagRewardWrapper
};

bool PopScene::init()
{
    if(!BaseScene::init())
    {
        return false;
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_asset/stage_CN_RETINA.plist");
    
    __initBackground();
    __initBirds();
    __initPauseButton();
    addChild(PauseLayer::create(),99999);
    scheduleUpdate();
    return true;
}

void PopScene::update(float delta)
{
    playTime += delta;
}

void PopScene::__initBackground()
{
    auto bg = Sprite::create("game_asset/stage_bg_RETINA.png");
    bg->setAnchorPoint(Point::ZERO);
    addChild(bg);
    
    auto backboard = Sprite::create("game_asset/stage_tree_RETINA.png");
    backboard->setAnchorPoint(Point::ZERO);
    addChild(backboard);
    auto targetPos = -backboard->getContentSize().height;
    backboard->setPositionY(targetPos);
    auto moveAct = MoveTo::create(0.5, Point(0,0));
    backboard->runAction(moveAct);
    
    auto targetScoreText = Label::createWithSystemFont("目标分数", "Arial", 24);
    targetScoreText->setPosition(VisibleRect::rightTop()-Point(80,33));
    addChild(targetScoreText);
    
    targetScoreLabel = Label::createWithSystemFont("1000", "Arial", 26);
    targetScoreLabel->setPosition(targetScoreText->getPosition()-Point(0,33));
    addChild(targetScoreLabel);
    
    currentScoreLabel = Label::createWithSystemFont("当前分数:0", "Arial", 26);
    currentScoreLabel->setAnchorPoint(Point::ZERO);
    currentScoreLabel->setPosition(Point(20,720));
    addChild(currentScoreLabel);
   
}

void PopScene::__initBirds()
{
    isTest = false;
    birdWrapperNode = Node::create();
    for (auto i=0; i<ROW*COL; i++) {
        auto bird = Bird::create(rand()%2);
        auto row = i/COL;
        auto col = i%COL;
        bird->setAnchorPoint(Point::ZERO);
        bird->setRow(row);
        bird->setCol(col);
        bird->setTouchBeganHandler(std::bind(&PopScene::_birdTouchHandler,this,std::placeholders::_1));
        birdVec.pushBack(bird);
        birdWrapperNode->addChild(bird);
    }
    birdWrapperNode->setPosition(Point::ZERO);
    addChild(birdWrapperNode);
    birdWrapperNode->setPositionY(-800);
    auto moveAct = MoveTo::create(0.5f, Point::ZERO);
    birdWrapperNode->runAction(Sequence::create(DelayTime::create(0.4f),moveAct, nullptr));
}

void PopScene::__initPauseButton()
{
    auto pauseSpr = PauseSprite::create();
    pauseSpr->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    pauseSpr->setPosition(VisibleRect::leftTop()+Point(18,-18));
    pauseSpr->setOpacity(0);
    addChild(pauseSpr);
}

void PopScene::_birdTouchHandler(BaseSprite *sprite)
{
    /**
     * 1.检查是否有可以消除的小鸟 没有则清除掉选择
     * 2.消除掉小鸟 然后增加分数
     */
    auto bird = static_cast<Bird*>(sprite);
    if (m_vDashList.size()!=0) {
        
        /* 判断点击的小鸟是不是在这个范围内 */
        auto it = m_vDashList.begin();
        if(m_vDashList.contains(bird))
        {
            
            while (it!=m_vDashList.end())
            {
                auto bird = *it;
                bird->setIsDestroy(true);
                bird->bomb();
                it++;
            }
            
            /* 根据消除的数量 播放不同的音效 */
            auto listSize = m_vDashList.size();
            birdDestroy += listSize;
            if(listSize>6)
            {
                auto size = (listSize-6)>9?9:listSize-6;
                char effectName[50];
                sprintf(effectName, "sounds/effects/%ld.mp3",size);
                SimpleAudioEngine::getInstance()->playEffect(effectName);
                std::string labelName = "";
                switch (size) {
                    case 1:
                        labelName = "第一滴血";
                        break;
                    case 2:
                        labelName = "大消特消";
                        break;
                    case 3:
                        labelName = "主宰比赛";
                        break;
                    case 4:
                        labelName = "消除如麻";
                        break;
                    case 5:
                        labelName = "无人能挡";
                        break;
                    case 6:
                        labelName = "变态的消除";
                        break;
                    case 7:
                        labelName = "如同神一般";
                        break;
                    case 8:
                        labelName = "超神了~";
                        break;
                    case 9:
                        labelName = "超神了~";
                        break;
                    default:
                        break;
                }
                
                auto label = Label::createWithBMFont("fonts/font_01.fnt", labelName);
                label->setPosition(VisibleRect::center());
                label->setScale(0);
                label->setOpacity(0);
                label->runAction(Sequence::create(Spawn::create(FadeIn::create(0.3f),EaseBackOut::create(ScaleTo::create(0.3f, 1.0f)), nullptr),DelayTime::create(0.5f),Spawn::create(FadeOut::create(0.3f),EaseBackOut::create(ScaleTo::create(0.3f, 2.0f)), nullptr),CallFuncN::create([](Node *node)->void{
                    node->removeFromParent();
                }), nullptr));
                addChild(label);
            }
            
            m_vDashList.clear();
            __movePrevScore();
            _updateBirdsPosition();
            
            return;
        }
        else
        {
            while (it!=m_vDashList.end())
            {
                auto bird = *it;
                bird->setIsDestroy(false);
                bird->setSelect(false);
                it++;
            }
            m_vDashList.clear();
        }
        
    }
    
    
    
    Vector<Bird*> selectBirdVec;
    selectBirdVec.pushBack(bird);
    m_vDashList.pushBack(bird);
    bird->setSelect(true);
    while (selectBirdVec.size()!=0)
    {
        auto bird = selectBirdVec.at(0);
        Bird *selectBird = bird;
        auto row = bird->getRow();
        auto col = bird->getCol();
        
        for(auto i=row-1;i<=row+1;i++)
        {
            if(i<0 || i>=ROW) //检测是不是到了边界范围
            {
                continue;
            }
            for (auto j=col-1; j<=col+1; j++)
            {
                if((i!=row && j!=col )||j<0||j>=COL) //确定不是边界 并且在同一行或者同一列才继续
                {
                    continue;
                }
                auto idx = i*COL+j;
                auto neighbor = birdVec.at(idx);
                if (neighbor!=selectBird && neighbor->getBirdType()==bird->getBirdType()) //不对选中的小鸟进行监测 并且鸟的类型要一致
                {
                    if (neighbor->getSelect()) //已经选中的 不重复监测
                    {
                        continue;
                    }
                    else
                    {
                        neighbor->setSelect(true);
                        selectBirdVec.pushBack(neighbor);
                        m_vDashList.pushBack(neighbor);
                    }
                }
            }
        }
        selectBirdVec.eraseObject(selectBird);
    }
    
    if(m_vDashList.size()<2) //如果相邻类型的小鸟数量小于2的话 则清空已经选中的小鸟
    {
        bird->setSelect(false);
        selectBirdVec.clear();
        m_vDashList.clear();
        __hidePrevScore();
        return;
    }
    __showPrevScore(m_vDashList.size());
}


void PopScene::_updateBirdsPosition()
{
    auto j=0;
    for(auto col=0;col<COL;col++)
    {
        auto i=0;
        
        for (auto row=0; row<ROW; )
        {
            auto idx = row*COL+col;
            row++;
            auto bird = birdVec.at(idx);
            if (bird->getIsDestroy())
            {
                i++;
            }
            else if(i>0 || j>0)
            {
                auto distance = i*BOX_HEIGHT;
                auto moveX = 0;
                if (j>0 && col !=0)
                {
                    moveX = j*BOX_WIDTH;
                }
                auto moveBy = MoveBy::create(0.25f, Point(-moveX,-distance));
                bird->setRow(bird->getRow()-i);
                bird->setCol(bird->getCol()-j);
                bird->runAction(moveBy);
                
                auto targetIdx = bird->getRow()*COL+bird->getCol();
                auto targetBird = birdVec.at(targetIdx);
                
                birdVec.swap(targetBird, bird);
            }
        }
        if (i==ROW) {
            j++;
        }
    }

    /* 更新完之后需要 判断是不是有继续可以消除的 没有则结束游戏 */
    isTest = true;
    auto it = birdVec.begin();
    while (it!=birdVec.end()) {
        auto bird = *it;
        if(bird->getIsDestroy())
        {
            it++;
            continue;
        }
        _birdTouchHandler(bird);
        if (m_vDashList.size()>0) {
            auto birdIt = m_vDashList.begin();
            while (birdIt!=m_vDashList.end()) {
                (*birdIt)->setIsDestroy(false);
                (*birdIt)->setSelect(false);
                birdIt++;
            }
            m_vDashList.clear();
            isTest = false;
            return;
        }
        it++;
    }
    
    /* 如果没有可以消除的小鸟后 就自动消除 最后一排全部消除 奖励2000 每剩余一个 扣除奖励50 */
    auto delay = 0.5f;
    for (auto row=ROW-1; row>=0; row--) {
        for (auto col=0; col<COL; col++) {
            auto idx = row*COL+col;
            auto bird = birdVec.at(idx);
            if (bird->getIsDestroy()) {
                continue;
            }
            
            if(row>0)
            {
                delay = delay+0.4f;
            }
            auto delayTime = delay;
            if(row==0)
            {
                delayTime = delay+0.4;
            }
            bird->runAction(Sequence::create(DelayTime::create(delayTime),CallFuncN::create([&](Node *node)->void{
                auto bird = static_cast<Bird*>(node);
                bird->bomb();
                auto label = static_cast<Label*>(this->getChildByTag(kTagRewardWrapper)->getChildByTag(kTagRewardLabel));
                reward -= 50;
                char rewardStr[50];
                sprintf(rewardStr,"奖励:%d",reward);
                label->setString(rewardStr);
            }), nullptr));
            
        }
    }
    
    runAction(Sequence::create(DelayTime::create(delay+1),CallFunc::create([&]()->void{
        auto fadeOutAct = FadeOut::create(0.3f);
        auto scaleOutAct = ScaleTo::create(0.3f, 0.2f);
        auto moveToAct = MoveTo::create(0.3f, Point(50,720));
        
        getChildByTag(kTagRewardWrapper)->runAction(Sequence::create(Spawn::create(fadeOutAct,scaleOutAct,moveToAct, nullptr),CallFuncN::create([&](Node *node)->void{
            node->removeFromParent();
            currentScore += reward;
            char scoreLabel[50];
            sprintf(scoreLabel, "当前分数:%d",currentScore);
            currentScoreLabel->setString(scoreLabel);
            /* 判断是否通关了 */
            if (currentScore<targetScore)
            {
                auto time = int(playTime);
                char timeStr[50];
                sprintf(timeStr, "%d秒",time);
                GameResultWin::create(level,timeStr, birdDestroy, currentScore);
                return;
            }
            
            /* 显示下次通关的分数 */
            isLevelClear = false;
            level++;
            auto sum = 0;
            for (auto i=1; i<=level; i++) {
                sum += i;
            }
            targetScore = sum*1000;
            targetScoreLabel->setString(__String::createWithFormat("%d",targetScore)->getCString());
            /* 提示通关分数 */
            auto passScoreLabel = Label::createWithBMFont("fonts/font_01.fnt", __String::createWithFormat("通关分数:%d",targetScore)->getCString());
            passScoreLabel->setPosition(VisibleRect::right()+Point(200,0));
            addChild(passScoreLabel);
            auto moveToCenter = MoveTo::create(0.3f, VisibleRect::center());
            auto moveOut = MoveTo::create(0.3f, VisibleRect::left()-Point(200,0));
            auto showSeq = Sequence::create(EaseBackOut::create(moveToCenter),DelayTime::create(1.5f),EaseBackIn::create(moveOut),CallFuncN::create([&](Node *node)->void{
                node->removeFromParent();
                /* 开始重新生成小鸟 */
                this->birdVec.clear();
                this->birdWrapperNode->removeFromParent();
                this->__initBirds();
            }),nullptr);
            passScoreLabel->runAction(showSeq);
            
        }), nullptr));
    }), nullptr));
    
    __showGameReward();
}

void PopScene::__showGameReward()
{
    /* 显示游戏奖励 */
    reward = 2000;
    auto wrapperNode = Node::create();
    auto label = Label::createWithBMFont("fonts/font_01.fnt", "奖励:2000");
    label->setScale(0);
    label->setTag(kTagRewardLabel);
    label->runAction(EaseBackOut::create(ScaleTo::create(0.3f, 1.0f)));
    wrapperNode->addChild(label);
    wrapperNode->setPosition(VisibleRect::center());
    wrapperNode->setTag(kTagRewardWrapper);
    addChild(wrapperNode);
}

void PopScene::__showPrevScore(int birdNum)
{
    if(isTest)
    {
        return;
    }
    __hidePrevScore();
    prevScore = ((birdNum-2)*5+10)*birdNum;
    char scoreStr[50];
    sprintf(scoreStr, "%dBirds+%d",birdNum,prevScore);
    auto selectBirds = Label::createWithBMFont("fonts/number_01.fnt", scoreStr);
    selectBirds->setPosition(VisibleRect::top()-Point(0,130)-Point(0,200));
    selectBirds->setOpacity(0);
    addChild(selectBirds);
    
    auto moveUpAct = MoveBy::create(0.2f, Point(0,200));
    auto fadeInAct = FadeIn::create(0.2f);
    auto spawnAct = Spawn::create(moveUpAct,fadeInAct, nullptr);
    selectBirds->runAction(spawnAct);
    selectBirds->setTag(kTagPrevLabel);
}

void PopScene::__hidePrevScore()
{
    auto prevLabel = getChildByTag(kTagPrevLabel);
    if (prevLabel)
    {
        prevLabel->removeFromParent();
    }
}

void PopScene::__movePrevScore()
{
    auto prevLabel = getChildByTag(kTagPrevLabel);
    if(prevLabel)
    {
        prevLabel->setTag(kTagPrevLabelMark);
        auto fadeOutAct = FadeOut::create(0.2f);
        auto scaleOutAct = ScaleTo::create(0.2f, 0.2f);
        auto moveToAct = MoveTo::create(0.2f, Point(50,720));
        auto spawnAct = Spawn::create(fadeOutAct,scaleOutAct,moveToAct, nullptr);
        prevLabel->runAction(Sequence::create(spawnAct,CallFuncN::create([](Node *node)->void{
            node->removeFromParent();
        }),nullptr));
        currentScore += prevScore;
        char scoreLabel[50];
        sprintf(scoreLabel, "当前分数:%d",currentScore);
        currentScoreLabel->setString(scoreLabel);
        if(currentScore>=targetScore && isLevelClear==false) //确保每一关只提示一次
        {
            isLevelClear = true;
            /* 通知通关 */
            auto bg = SPRITE("stage_level_bg@2x.png");
            bg->setPosition(VisibleRect::center());
            auto bgSize = bg->getContentSize();
            auto label = Label::createWithBMFont("fonts/font_01.fnt", "恭喜通关~");
            label->setPosition(Point(bgSize.width/2,bgSize.height/2));
            bg->addChild(label);
            addChild(bg);
            bg->setScale(3);
            bg->setOpacity(0);
            auto scaleIn = ScaleTo::create(0.3f, 1.0f);
            auto fadeIn = FadeIn::create(0.3f);
            auto scaleInEase = EaseBackOut::create(scaleIn);
            auto spawnIn = Spawn::create(fadeIn,scaleInEase, nullptr);
            
            auto scaleOutEase = EaseBackIn::create(MoveBy::create(0.3f, Point(0,700)));
            auto fadeOut = FadeOut::create(0.3f);
            auto callback = CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, bg));
            auto spawnOut = Spawn::create(fadeOut,scaleOutEase, nullptr);
            bg->runAction(Sequence::create(spawnIn,DelayTime::create(0.5f), spawnOut,callback, nullptr));
        }
    }
}

void PopScene::onEnter()
{
    BaseScene::onEnter();
    
    getEventDispatcher()->addCustomEventListener(EVENT_RESTART_GAME, [&](EventCustom *custom)->void{
        this->level = 1;
        this->targetScore = 1000;
        this->playTime = 0;
        this->birdDestroy = 0;
        this->currentScore = 0;
        this->reward = 0;
        this->isLevelClear = false;
        this->birdVec.clear();
        this->birdWrapperNode->removeFromParent();
        this->__initBirds();
        this->isTest = false;
        char scoreLabel[50];
        sprintf(scoreLabel, "当前分数:%d",currentScore);
        currentScoreLabel->setString(scoreLabel);
        targetScoreLabel->setString(__String::createWithFormat("%d",targetScore)->getCString());
    });
    
}

void PopScene::onExit()
{
    BaseScene::onExit();
    getEventDispatcher()->removeEventListenersForTarget(this);
}

void PopScene::__gameStart()
{
    auto animate_time = 0.2f;
    auto label = Label::createWithBMFont("fonts/number_01.fnt", "7 Birds");
    label->setOpacity(0);
    label->setPosition(VisibleRect::top());
    auto moveTo = MoveTo::create(animate_time, VisibleRect::center());
    auto fadeIn = FadeIn::create(animate_time);
    auto fadeOut = FadeOut::create(animate_time);
    auto scaleTo = ScaleTo::create(animate_time, 3.0f);
    auto seqAct = Sequence::create(DelayTime::create(1.0f),Spawn::create(EaseBackOut::create(moveTo),fadeIn, nullptr),DelayTime::create(1.0f),Spawn::create(fadeOut,EaseBackIn::create(scaleTo), nullptr), nullptr);
    addChild(label);
    label->runAction(seqAct);
    
}

