#include <unistd.h>
#include <iostream>

#include "ThreadPool.h"

class DemoThread : public Thread {
    public:
        ~DemoThread() {}
        void run() {
            std::cout << "aa" << std::endl;
            while (true) {}
        }
};

int main() {
    shared_ptr<ThreadPool> pool = ThreadPool::init();

    sleep(2);
    for (int i = 0; i < 10; i++) {
        pool->pushTask(new DemoThread());
    }

    pool->shutdown();
    return 0;
}
