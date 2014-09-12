//
//  Util.h
//  PopBird
//
//  Created by AIRIA on 14-9-12.
//
//

#ifndef __PopBird__Util__
#define __PopBird__Util__

#include "Headers.h"

class Util
{
public:
    static void playEffect(std::string filePath,bool repeate=false);
    static void playSound(std::string filePath,bool repeate=false);
    static void init();
};

#endif /* defined(__PopBird__Util__) */
