//
//  main.cpp
//  17_IteratorStack2
//
//  Created by Sathya Babu on 23/06/22.
//
#include <iostream>
#include <memory>

template<class T>
class Node {
private:
    T data = 0;
    std::shared_ptr<Node<T>> next_node = nullptr;

public:
    Node(T data = 0, std::shared_ptr<Node<T>> next_node = nullptr)
        : data(data), next_node(next_node)
    {
        std::cout << "created node["  << data  << "]\n";
    }

    ~Node() {
        std::cout << "deleted node["  << data <<  "]\n";
    }

    // getters and setters

    T getData() const {
        return this->data;
    }

    std::shared_ptr<Node< T >> getNextNode() const {
        return this->next_node;
    }

    void setData(T value) {
        this->data = value;
    }

    void setNextNode(std::shared_ptr<Node<T>> node) {
        this->next_node = node;
    }
};

template<class T>std::ostream& operator<<(std::ostream& o, const std::shared_ptr<Node<T>> node) {
    return o << "node["<< node->getData() <<"]-> ";
}

template<class T>
class Stack {
private:
    std::shared_ptr<Node<T>> top = nullptr;

public:
    Stack()
        : top(nullptr)
    { /* empty */ }

    ~Stack() { /* empty */ }

    void push(T value) {
        if(!top) {
            top = std::shared_ptr<Node<T>> (new Node<T>(value));
        } else {
            top = std::shared_ptr<Node<T>> (new Node<T>(value, top));
        }
    }

    void display() {
        if(!top) {
            std::cout << "display::The stack is empty.\n";
        } else {
            std::shared_ptr<Node<T>> p = top;

            while(p) {
                std::cout << p;
                p = p->getNextNode();
            }

            std::cout << "\n";
        }
    }

    class Iterator {
    private:
        std::shared_ptr<Node<T>> node;

    public:
        Iterator(std::shared_ptr<Node<T>> node)
            : node(node)
        { /* empty */ }

        bool haxNext() {
            return node != nullptr;
        }

        Iterator getNext() {
            return Iterator(node->getNextNode());
        }

        T getData() {
            return node->getData();
        }
    };

    Iterator begin() const {
        return Iterator(top);
    }

    Iterator getIterator() {
        Iterator it = Iterator(top);

        return it;
    }
};

int main() {
    Stack<char> stack;

    for(char i = 'a'; i < 'f'; ++i) {
        stack.push(i);
    }

    Stack<char>::Iterator it = stack.begin();
   
    while(it.haxNext()) {
        std::cout << it.getData() << "->";
        it = it.getNext();
    }

    std::cout << "\n";

    return 0;
}
/*
 
 created node[a]
 created node[b]
 created node[c]
 created node[d]
 created node[e]
 e->d->c->b->a->
 deleted node[e]
 deleted node[d]
 deleted node[c]
 deleted node[b]
 deleted node[a]
 Program ended with exit code: 0
 */
