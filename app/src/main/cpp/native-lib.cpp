#include <jni.h>
#include <string>
#include <LogUtil.h>
#include "MyFfmpeg.h"


#ifdef __cplusplus
extern "C" {
#endif
#include <libavformat/avformat.h>

JNIEXPORT void JNICALL
Java_com_eric_JniHelper_nSample(JNIEnv *env, __unused jobject
) {

    MyFfmpeg::GetInstance()->sample();
    avformat_alloc_context();
    LOGCATE("Java_com_eric_JniHelper_nSample:%s",
            "123");
}

#ifdef __cplusplus
}
#endif
