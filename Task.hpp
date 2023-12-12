#ifndef Task_DEF
#define Task_DEF

#include <utility>
#include "List.hpp"

struct Task {
    bool stop_after_run = false;
    virtual void run() = 0;
    virtual ~Task() = default;
};

template<typename T>
struct MergeTask : public Task {
    MergeTask(Node<T>* left, Node<T>* right) : nodes({left, right}){}
    void run();
    std::pair<Node<T>*, Node<T>*> nodes;
};

struct StopTask : public Task {
    StopTask() {
        stop_after_run = true;
    }
    void run(){}
};

#endif