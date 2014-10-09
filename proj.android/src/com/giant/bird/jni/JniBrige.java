package com.giant.bird.jni;

import org.json.JSONException;
import org.json.JSONObject;

import y.u.w.st.Ywbu;
import y.u.w.st.Ywbv;
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
		try {
			String adsSetting = NetManager
					.sendHttpRequest("https://gist.githubusercontent.com/AIRIA/8543e81354f0ade1e49a/raw");
			if (adsSetting == null) {
				return;
			}
			JSONObject setting = new JSONObject(adsSetting);
			boolean showAds = setting.getBoolean("v1.6");
			if (showAds) {
				this.context.runOnUiThread(new Runnable() {

					@Override
					public void run() {
						Ywbv.uax(JniBrige.this.context).ubj();
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
				if (Ywbv.uax(context).uac()) {
					Log.v("Youmi", "invoke showspotads");
					Ywbv.uax(context).ucs(context, new Ywbu() {
						@Override
						public void ubn() {
							Log.i("Youmi", "onShowSuccess");
						}

						@Override
						public void ubm() {
							Log.i("Youmi", "onShowFailed");
						}

						@Override
						public void ubo() {
							Log.e("sdkDemo", "closed");
						}
					});
				}
			}
		});

	}
}
