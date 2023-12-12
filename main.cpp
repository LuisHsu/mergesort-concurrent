#include <fstream>
#include <iostream>
#include <string>

#include "List.hpp"
#include "Thread.hpp"

int main(int argc, char const* argv[]){
    // Load data
    List<uint32_t> list;
    std::ifstream input(argv[1]);
    for(std::string line = ""; !input.eof();){
        auto ch = input.get();
        if(ch == '\n'){
            list.emplace_back(std::stoul(line));
            line.clear();
        }else{
            line += ch;
        }
    }
    input.close();

    // Create threads
    Thread threads[4];

    // Dispatch merge tasks
    for(auto it = list.begin(); it != list.end(); ++it){
        Thread* thread = Thread::get_idle();
        thread->task.store((Task*) new MergeTask<uint32_t>(it.cur, (++it).cur));
        thread->task.notify_all();
    }

    // Join threads
    for(int i = 0; i < 4; ++i){
        Thread* thread = Thread::get_idle();
        thread->task.store((Task*) new StopTask());
        thread->task.notify_all();
        thread->join();
    }
    return 0;
}