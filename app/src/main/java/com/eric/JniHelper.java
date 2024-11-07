package com.eric;

public class JniHelper {
    //加载动态库到系统内存
    static {
        System.loadLibrary("native-render");
    }
    private JniHelper() {

    }

    private static class SingletonInstance {
        private static final JniHelper INSTANCE = new JniHelper();
    }

    public static JniHelper getInstance() {
        return SingletonInstance.INSTANCE;
    }



    public native void nSample();
}
