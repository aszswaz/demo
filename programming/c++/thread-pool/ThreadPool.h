#ifndef MAIL_THREAD_POOL_H
#define MAIL_THREAD_POOL_H

#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Thread.h"

using namespace std;

class ThreadPool {
    private:
        // 待执行的任务队列
        static queue<Thread *> tasks;
        // 线程池中的工作线程
        static thread **threads;
        static int threadsSize;
        // 任务队列线程锁
        static mutex mlock;
        // 任务队列准备就绪信号
        static condition_variable ready;
        static bool runing;
    public:
        static void init();
        static void shutdown();
        static void pushTask(Thread *task);
    private:
        static void start();
        static Thread *popTask();
};

#endif
