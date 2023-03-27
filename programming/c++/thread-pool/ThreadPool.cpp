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

ThreadPool::ThreadPool(queue<Thread *> *tasks, vector<thread *> *threads) {
    this->tasks = tasks;
    this->threads = threads;
    this->runing = true;
}

ThreadPool::~ThreadPool() {
    this->shutdown();
}

shared_ptr<ThreadPool> ThreadPool::init() {
    vector<thread *> *threads = new vector<thread *>;
    queue<Thread *> *tasks = new queue<Thread *>;
    shared_ptr<ThreadPool> pool = make_shared<ThreadPool>(tasks, threads);

    // CPU 的核心数 - 主线程 = 线程池的线程数
    long cpuCores = sysconf(_SC_NPROCESSORS_ONLN);
    cpuCores = (cpuCores << 1);
    cpuCores = cpuCores > MIN_WORK_THREAD ? cpuCores : MIN_WORK_THREAD;
    std::cout << "Number of working threads: " << cpuCores << std::endl;
    // 主线程也包括在内
    cpuCores -= 1;

    // 创建工作线程
    for (int i = 0; i < cpuCores; i++) {
        threads->push_back(new thread(ThreadPool::run, pool));
    }
    return pool;
}

void ThreadPool::run(shared_ptr<ThreadPool> pool) {
    while (pool->runing) {
        Thread *task;
        {
            // 10 个任务只能获取到 4 个
            unique_lock<mutex> qlock(pool->lock);
            while (pool->tasks->empty()) {
                pool->ready.wait(qlock);
                thread::id tid = this_thread::get_id();
                std::cout << tid << std::endl;
            }
            task = pool->tasks->front();
            pool->tasks->pop();
        }
        try {
            task->run();
        } catch (exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
}

void ThreadPool::pushTask(Thread *task) {
    // 给整个函数上线程锁，函数退出时自动解锁
    unique_lock<mutex> qlock(this->lock);
    this->tasks->emplace(task);
    // 通知工作线程有任务需要执行
    this->ready.notify_one();
}

void ThreadPool::shutdown() {
    this->runing = false;
    this->ready.notify_all();
    // 清理还没有执行的任务
    while (this->tasks->size()) {
        Thread *iterm = this->tasks->front();
        delete iterm;
        this->tasks->pop();
    }
    delete this->tasks;
    // 关闭线程
    for (auto iterm = this->threads->begin(); iterm != this->threads->end(); iterm++) {
        if ((*iterm)->joinable())(*iterm)->join();
        delete *iterm;
    }
    delete this->threads;
}
