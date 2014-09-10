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

enum PopSceneTAG
{
    kTagPrevLabel,
    kTagPrevLabelMark,
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

    return true;
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
    auto birdWrapperNode = Node::create();
    for (auto i=0; i<ROW*COL; i++) {
        auto bird = Bird::create(rand()%4);
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
//    return;
    /* 更新完之后需要 判断是不是有继续可以消除的 没有则结束游戏 */
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
            return;
        }
        it++;
    }

    MessageBox("NO DASH BIRD", "TITLE");
}

void PopScene::__showPrevScore(int birdNum)
{
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
    if (prevLabel) {
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
        if(currentScore>=targetScore)
        {
//            MessageBox("Stage Clear", "TITLE");
        }
    }
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

