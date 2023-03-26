#include <unistd.h>

#include "ThreadPool.h"

class DemoThread : public Thread {
    public:
        ~DemoThread() {}
        void run() {
            while (true) {}
        }
};

int main() {
    ThreadPool::init();

    for (int i = 0; i < 10; i++) {
        ThreadPool::pushTask(new DemoThread());
    }

    sleep(5);
    ThreadPool::shutdown();
    return 0;
}
