//
//  PopScene.h
//  PopBird
//
//  Created by AIRIA on 14-9-3.
//
//

#ifndef __PopBird__PopScene__
#define __PopBird__PopScene__

#include "BaseScene.h"
#include "Bird.h"

class PopScene:public BaseScene
{
public:
    virtual bool init();
    CREATE_FUNC(PopScene);
    
protected:
    Vector<Bird*> m_vDashList;
    void _birdTouchHandler(BaseSprite *bird);
    void _updateBirdsPosition();
    
private:
    Vector<Bird*> birdVec;
    Label *currentScoreLabel;
    Label *targetScoreLabel;
    Node *birdWrapperNode;
    int currentScore; //当前的分数
    int prevScore; //预得分数
    int reward; //奖励分数
    
    int targetScore = 1000; //通关分数
    bool isLevelClear;//是否通关
    int level = 1;
    
    void __initBackground();
    void __initBirds();
    void __initPauseButton();
    /**
     * 游戏开始的时候 提示目标分数 和等级
     */
    void __gameStart();
    /**
     * 选中小鸟后 显示即将得到的分数
     */
    void __showPrevScore(int birdNum);
    void __hidePrevScore();
    void __movePrevScore();
    void __showGameReward();
    
};

#endif /* defined(__PopBird__PopScene__) */
