#include "Task.hpp"

#include <iostream>

template<>
void MergeTask<uint32_t>::run(){
    std::cout << "Left: " << nodes.first->data;
    if(nodes.second){
        std::cout << ", Right: "<< nodes.second->data;
    }
    std::cout << std::endl;
}