#ifndef Thread_DEF
#define Thread_DEF

#include <thread>
#include <memory>
#include "List.hpp"
#include "Task.hpp"

struct Thread : public std::thread {
    Thread();
    static void run(Thread*);

    static List<Thread*> idle_queue;
    static Thread* get_idle();

    size_t id;
    std::atomic<Task*> task;
};

#endif