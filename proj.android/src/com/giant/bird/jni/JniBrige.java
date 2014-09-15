package com.giant.bird.jni;

public class JniBrige {

	public native void exitGame();
	
	static public JniBrige _instance;

	public static Object getObject() {
		return getInstance();
	}

	public static JniBrige getInstance() {
		if (_instance == null) {
			_instance = new JniBrige();
		}
		return _instance;
	}
	

}
