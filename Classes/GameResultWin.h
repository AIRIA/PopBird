//
//  GameResultWin.h
//  PopBird
//
//  Created by AIRIA on 14-9-11.
//
//

#ifndef __PopBird__GameResultWin__
#define __PopBird__GameResultWin__

#include "Headers.h"

class GameResultWin:public Layer
{
public:
    static GameResultWin *create(int level,std::string playTime,int birdDestroy,int score);
    
private:
    int m_iLevel;
    std::string m_sPlayTime;
    int m_iBirdDestroy;
    int m_iScore;
    
    void __show();

};

#endif /* defined(__PopBird__GameResultWin__) */
