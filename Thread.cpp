#include "Thread.hpp"

#include <iostream>

List<Thread*> Thread::idle_queue;

Thread::Thread() : std::thread(Thread::run, this), task(nullptr){
    static size_t uid = 0;
    id = uid++;
}

Thread* Thread::get_idle(){
    idle_queue.head.wait(nullptr);
    Node<Thread*>* idle_node = Thread::idle_queue.head.load();
    Thread::idle_queue.head.store(idle_node->next);
    Thread* thread = idle_node->data;
    delete idle_node;
    return thread;
}

void Thread::run(Thread* th){
    Thread::idle_queue.emplace_back(th);
    while(true){
        th->task.wait(nullptr);
        Task* task = th->task.load();
        th->task.store(nullptr);
        task->run();
        bool stopped = task->stop_after_run;
        delete task;
        if(stopped){
            std::cout << th->id << " stop" << std::endl;
            break;
        }else{
            std::cout << th->id << " idle" << std::endl;
            Thread::idle_queue.emplace_back(th);
        }
    }
}