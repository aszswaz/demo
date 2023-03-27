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
        queue<Thread *> *tasks;
        // 线程池中的工作线程
        vector<thread *> *threads;
        // 任务队列线程锁
        mutex lock;
        // 任务队列准备就绪信号
        condition_variable ready;
        bool runing;
    public:
        ThreadPool(queue<Thread *> *tasks, vector<thread *> *threads);
        ~ThreadPool();
        static shared_ptr<ThreadPool> init();
        void pushTask(Thread *task);
        void shutdown();
    private:
        static void run(shared_ptr<ThreadPool> pool);
};

#endif
