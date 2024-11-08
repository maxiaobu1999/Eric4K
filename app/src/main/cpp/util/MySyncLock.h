

#ifndef AVM_SYNCLOCK_H
#define AVM_SYNCLOCK_H

#include <pthread.h>

class MySyncLock {
public:
    MySyncLock() {
        pthread_mutexattr_init(&m_attr);
        pthread_mutexattr_settype(&m_attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&m_mutex, &m_attr);
    }

    ~MySyncLock(void) {
        pthread_mutex_destroy(&m_mutex);
        pthread_mutexattr_destroy(&m_attr);
    }

    int Lock() {

        return pthread_mutex_lock(&m_mutex);
    }

    int UnLock() {

        return pthread_mutex_unlock(&m_mutex);
    }

    int TryLock() {
        return pthread_mutex_trylock(&m_mutex);
    }

private:
    pthread_mutex_t m_mutex;
    pthread_mutexattr_t m_attr;

};

class ScopedSyncLock {
public:
    ScopedSyncLock(MySyncLock *pLock) :
            m_pLock(pLock) {
        if (pLock != NULL)
            m_pLock->Lock();
    }

    ~ScopedSyncLock() {
        if (m_pLock != NULL)
            m_pLock->UnLock();
    }

private:
    MySyncLock *m_pLock;
};

#endif
