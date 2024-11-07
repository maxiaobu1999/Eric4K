//
// Created by 马庆龙 on 2024/11/7.
//
#include <mutex>
#include <stdio.h>
//#include <libavformat/avformat.h>
//#include <libavcodec/avcodec.h>
//#include <libavutil/log.h>
#ifndef ERIC4K_MYFFMPEG_H
#define ERIC4K_MYFFMPEG_H


#ifdef __cplusplus
extern "C" {
#endif
#include <libavformat/avformat.h>

using namespace std;


class MyFfmpeg {
    MyFfmpeg();

    ~MyFfmpeg();
public:
    static MyFfmpeg *GetInstance();
    static void sample();

private:
    static MyFfmpeg *m_pContext;
    static mutex m_Mutex;

};

#ifdef __cplusplus
}
#endif



#endif //ERIC4K_MYFFMPEG_H
