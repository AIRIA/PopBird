package com.giant.bird.jni;

import android.content.Context;

import com.umeng.fb.FeedbackAgent;

public class JniBrige {

	public native void exitGame();
	
	static public JniBrige _instance;
	public Context context;

	public static Object getObject() {
		return getInstance();
	}

	public static JniBrige getInstance() {
		if (_instance == null) {
			_instance = new JniBrige();
		}
		return _instance;
	}
	
	public void init(Context context){
		this.context = context;
	}
	
	public void feedBack(String params)
	{
		FeedbackAgent agent = new FeedbackAgent(context);
	    agent.startFeedbackActivity();
	    agent.sync();
	}
	
}
