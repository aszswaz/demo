#ifndef MAIL_THREAD_H
#define MAIL_THREAD_H

class Thread {
    public:
        virtual void run() = 0;
        virtual ~Thread() {};
};

#endif
