//
// Created by 马庆龙 on 2024/11/7.
//
#include <mutex>

#ifndef ERIC4K_MYFFMPEG_H
#define ERIC4K_MYFFMPEG_H
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


#endif //ERIC4K_MYFFMPEG_H
