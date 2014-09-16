//
//  Util.cpp
//  PopBird
//
//  Created by AIRIA on 14-9-12.
//
//

#include "Util.h"

#define JNI_CLASS "com/giant/bird/jni/JniBrige"

#if (CC_PLATFORM_ANDROID==CC_TARGET_PLATFORM)

JniMethodInfo Util::sm_methodInfo;
jobject Util::m_obj;

#endif

void Util::init()
{
	auto exist = SharePreference->isXMLFileExist();
	if (!exist)
	{
		SharePreference->setBoolForKey(KEY_SOUND_ENABLE, true);
		SharePreference->setBoolForKey(KEY_VIBRATION_ENABLE, false);
	}

	/**
	 * 初始化JNI对象
	 */
#if (CC_PLATFORM_ANDROID==CC_TARGET_PLATFORM)
	auto isHave = JniHelper::getStaticMethodInfo(sm_methodInfo,JNI_CLASS,"getObject","()Ljava/lang/Object;");
	if(isHave)
	{
		m_obj = sm_methodInfo.env->CallStaticObjectMethod(sm_methodInfo.classID, sm_methodInfo.methodID);
	}
	else
	{
		MessageBox("Jni 初始化失败 ","ERROR");
	}

#endif

}

void Util::playEffect(std::string filePath, bool repeate)
{
	if (SharePreference->getBoolForKey(KEY_SOUND_ENABLE))
	{
		SimpleAudioEngine::getInstance()->playEffect(filePath.c_str(),repeate);
	}
}

void Util::playSound(std::string filePath, bool repeate)
{
	if (SharePreference->getBoolForKey(KEY_SOUND_ENABLE))
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(filePath.c_str(),repeate);
	}
    
}

void Util::invokeNativeMethod(Method method, std::string param)
{

#if (CC_PLATFORM_ANDROID==CC_TARGET_PLATFORM)

	std::string methodName = "";
	switch (method) {
	case kMethodShowBannerAd:
		methodName = "showBannerAd";
		break;
	case kMethodHideBannerAd:
		methodName = "hideBannerAd";
		break;
	case kMethodShowSpotAd:
		methodName = "showSpotAd";
		break;
	case kMethodHideSpotAd:
		methodName = "hideSpotAd";
		break;
    case kMethodShowFeedBack:
        methodName = "showFeedBack";
        break;
	default:
		MessageBox("调用的方法没找到","ERROR");
		break;
	}

	auto isHave = JniHelper::getMethodInfo(sm_methodInfo,JNI_CLASS,methodName.c_str(),"(Ljava/lang/String;)V");
	jstring paramStr = sm_methodInfo.env->NewStringUTF(param.c_str());
	sm_methodInfo.env->CallVoidMethod(m_obj,sm_methodInfo.methodID,sm_methodInfo);

#endif

}

#if (CC_PLATFORM_ANDROID==CC_TARGET_PLATFORM)

extern "C"
{
	JNIEXPORT void JNICALL Java_com_giant_bird_jni_JniBrige_exitGame(JNIEnv *env,jobject thiz)
	{
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_SHOW_EXIT);
	}
}

#endif
