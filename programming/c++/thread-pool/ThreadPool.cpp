#include <unistd.h>
#include <cstring>
#include <iostream>

#include "ThreadPool.h"

#define  MIN_WORK_THREAD 4
#define PTHREAD_ERROR(expr) { \
        int code = expr; \
        if (code) { \
            throw MailException(strerror(code), __FILE_NAME__, __LINE__); \
        } \
    }

using namespace std;

queue<Thread *> ThreadPool::tasks;
thread **ThreadPool::threads;
int ThreadPool::threadsSize;
mutex ThreadPool::mlock;
condition_variable ThreadPool::ready;
bool ThreadPool::runing;

void ThreadPool::init() {
    // CPU 的核心数 - 主线程 = 线程池的线程数
    long cpuCores = sysconf(_SC_NPROCESSORS_ONLN);
    cpuCores = (cpuCores << 1);
    cpuCores = cpuCores > MIN_WORK_THREAD ? cpuCores : MIN_WORK_THREAD;
    std::cout << "Number of working threads: " << cpuCores << std::endl;
    // 主线程也包括在内
    cpuCores -= 1;

    // 创建工作线程
    threads = new thread*[cpuCores];
    threadsSize = cpuCores;
    for (int i = 0; i < cpuCores; i++) {
        threads[i] = new thread(ThreadPool::start);
    }
    runing = true;
}

void ThreadPool::pushTask(Thread *task) {
    // 给整个函数上线程锁，函数退出时自动解锁
    unique_lock<mutex> qlock(mlock);
    tasks.push(task);
    // 通知工作线程有任务需要执行
    ready.notify_all();
}

void ThreadPool::start() {
    Thread *t;

    while (runing) {
        try {
            t = popTask();
            // 执行任务
            if (t) t->run();
        } catch (exception &e) {
            std::cout << e.what() << std::endl;
        }
        delete t;
    }
}

void ThreadPool::shutdown() {
    if (!runing) return;
    runing = false;
    ready.notify_all();
    for (int i = 0; i < threadsSize; i++) threads[i]->join();
    for (int i = 0; i < threadsSize; i++) delete threads[i];
    delete [] threads;
}

Thread *ThreadPool::popTask() {
    Thread *t;
    unique_lock<mutex> qlock(mlock);

    if (tasks.size() == 0) {
        // 没有需要执行的任务，等待 ready 信号，并释放锁，ready 信号到达时会重新获取锁
        ready.wait(qlock);
    }
    // 获取并删除第一个元素
    t = tasks.front();
    tasks.pop();
    return t;
}
