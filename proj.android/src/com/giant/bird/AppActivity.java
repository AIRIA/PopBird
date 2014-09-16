/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package com.giant.bird;

import net.youmi.android.AdManager;
import net.youmi.android.spot.SpotDialogListener;
import net.youmi.android.spot.SpotManager;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;

import com.giant.bird.jni.JniBrige;
import com.umeng.analytics.MobclickAgent;
import com.umeng.message.PushAgent;
import com.umeng.update.UmengUpdateAgent;

public class AppActivity extends Cocos2dxActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		UmengUpdateAgent.silentUpdate(this);
		MobclickAgent.updateOnlineConfig(this);
		PushAgent mPushAgent = PushAgent.getInstance(this);
		mPushAgent.enable();
		mPushAgent.onAppStart();
		
		JniBrige.getInstance().init(this);
		AdManager.getInstance(this).init("330725f16188979b", "5b4ceb56ea751654", false);
		SpotManager.getInstance(this).loadSpotAds();
//		SpotManager.getInstance(this).checkSDKProcess("330725f16188979b", "5b4ceb56ea751654");
		super.onCreate(savedInstanceState);
	}

	@Override
	public boolean onKeyUp(int keyCode, KeyEvent event) {
		if (KeyEvent.KEYCODE_BACK == keyCode) {
			JniBrige.getInstance().exitGame();
		}
		return super.onKeyUp(keyCode, event);
	}

	@Override
	public void onBackPressed() {
		if (!SpotManager.getInstance(this).disMiss(true)) {
			super.onBackPressed();
		}
	}

	@Override
	protected void onStop() {
		// 如果不调用此方法，则按home键的时候会出现图标无法显示的情况。
		SpotManager.getInstance(this).disMiss(false);
		super.onStop();
	}

	@Override
	public void onResume() {
		super.onResume();
		MobclickAgent.onResume(this);
	}

	@Override
	public void onPause() {
		super.onPause();
		MobclickAgent.onPause(this);
	}

	@Override
	protected void onDestroy() {
		SpotManager.getInstance(this).unregisterSceenReceiver();
		super.onDestroy();
	}

}
