#include <jni.h>
#include <string>
#include <LogUtil.h>
#include "MyFfmpeg.h"

extern "C" JNIEXPORT jstring JNICALL
Java_c_d_e_Ma_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_eric_JniHelper_nSample(JNIEnv *env, __unused jobject
) {
    LOGCATE("Java_com_eric_JniHelper_nSample:%s",
            "123");
    MyFfmpeg::GetInstance()->sample();

}
