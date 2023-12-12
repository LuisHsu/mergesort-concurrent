#ifndef LIST_DEF
#define LIST_DEF

#include <iostream>
#include <memory>
#include <iterator>

template<typename T>
struct Node {
    Node(T data) : data(data){}
    T data;
    std::atomic<Node*> next = nullptr;
};

template<typename T>
struct List {

    using node_type = std::atomic<Node<T>*>;

    struct iterator {
        Node<T>* cur;
        iterator(Node<T>* node = nullptr) : cur(node){}
        T& operator*(){
            return *cur;
        }
        bool operator==(iterator& it){
            return it.cur == cur;
        }
        iterator operator++(){
            if(cur){
                cur = cur->next.load();
            }
            return *this;
        }
    };

    node_type head = nullptr;
    node_type tail = nullptr;

    iterator begin(){
        return iterator(head ? head.load() : nullptr);
    }
    iterator end(){
        return iterator(nullptr);
    }
    void emplace_back(T arg) {
        Node<T>* node = new Node<T>(arg);
        if(head.load() == nullptr){
            head.store(node);
            tail.store(node);
            head.notify_all();
            tail.notify_all();
        }else{
            Node<T>* tail_node = tail.load();
            tail_node->next.store(node);
            tail_node->next.notify_all();
            tail.store(node);
            tail.notify_all();
        }
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, List<T>& list){
    for(Node<T>* cur = list.head.load(); cur != nullptr; cur = cur->next.load()){
        os << cur->data << std::endl;
    }
    return os;
}

#endif