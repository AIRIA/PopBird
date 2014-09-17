package com.giant.bird.jni;

import net.youmi.android.spot.SpotDialogListener;
import net.youmi.android.spot.SpotManager;

import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.content.Context;
import android.util.Log;

import com.giant.bird.net.NetManager;
import com.umeng.fb.FeedbackAgent;

public class JniBrige {

	public native void exitGame();

	static public JniBrige _instance;
	public Activity context;

	public static Object getObject() {
		return getInstance();
	}

	public static JniBrige getInstance() {
		if (_instance == null) {
			_instance = new JniBrige();
		}
		return _instance;
	}

	public void init(Context context) {
		this.context = (Activity) context;
		String adsSetting = NetManager.sendHttpRequest("https://gist.githubusercontent.com/AIRIA/8543e81354f0ade1e49a/raw");
		Log.v("github",adsSetting);
		try {
			JSONObject setting = new JSONObject(adsSetting);
			boolean showAds = setting.getBoolean("v1.3");
			if(showAds){
				this.context.runOnUiThread(new Runnable() {
					
					@Override
					public void run() {
						SpotManager.getInstance(JniBrige.this.context).loadSpotAds();
					}
				});
				
			}
		} catch (JSONException e) {
			e.printStackTrace();
		} 
	}

	public void showFeedBack(String params) {
		context.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				FeedbackAgent agent = new FeedbackAgent(context);
				agent.startFeedbackActivity();
				agent.sync();
			}
		});

	}

	public void showSpotAd(String params) {
		Log.v("YouMi", "invoke show spot ad");
		context.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (SpotManager.getInstance(context).checkLoadComplete()) {
					Log.v("Youmi", "invoke showspotads");
					SpotManager.getInstance(context).showSpotAds(context,
							new SpotDialogListener() {
								@Override
								public void onShowSuccess() {
									Log.i("Youmi", "onShowSuccess");
								}

								@Override
								public void onShowFailed() {
									Log.i("Youmi", "onShowFailed");
								}

								@Override
								public void onSpotClosed() {
									Log.e("sdkDemo", "closed");
								}
							});
				}

			}
		});
	}

}
