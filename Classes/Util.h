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
#if (CC_PLATFORM_ANDROID==CC_TARGET_PLATFORM)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

#endif
enum Method
{
	kMethodShowBannerAd,
	kMethodShowSpotAd,
	kMethodHideBannerAd,
	kMethodHideSpotAd
};

class Util
{
public:

#if (CC_PLATFORM_ANDROID==CC_TARGET_PLATFORM)
	static JniMethodInfo sm_methodInfo;
	static jobject m_obj;
#endif

	static void invokeNativeMethod(Method method,std::string param="");

    static void playEffect(std::string filePath,bool repeate=false);
    static void playSound(std::string filePath,bool repeate=false);
    static void init();

};



#endif /* defined(__PopBird__Util__) */
