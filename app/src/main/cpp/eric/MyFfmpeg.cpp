//
// Created by 马庆龙 on 2024/11/7.
//

#include "MyFfmpeg.h"
#include "LogUtil.h"

#include <mutex>
#include <stdio.h>

MyFfmpeg *MyFfmpeg::m_pContext = nullptr;
mutex MyFfmpeg::m_Mutex;

MyFfmpeg::MyFfmpeg() {

}

MyFfmpeg::~MyFfmpeg() {

}

MyFfmpeg *MyFfmpeg::GetInstance() {
    LOGCATD("MyFfmpeg::GetInstance");
    if (m_pContext == nullptr) {
        unique_lock<mutex> lock(m_Mutex);
        if (m_pContext == nullptr) {
            m_pContext = new MyFfmpeg();
        }
    }
    return m_pContext;
}

void MyFfmpeg::sample() {
    avformat_alloc_context();

    LOGCATD("MyFfmpeg::sample");
    av_log_set_level(AV_LOG_DEBUG);
    av_log(NULL, AV_LOG_ERROR, "hello world!\n");
}
