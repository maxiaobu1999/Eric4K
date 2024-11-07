//
// Created by 马庆龙 on 2024/11/7.
//

#include "MyFfmpeg.h"
#include "LogUtil.h"
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
    LOGCATD("MyFfmpeg::sample");

}
