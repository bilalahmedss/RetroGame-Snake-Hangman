// DoublyLinkedList.hpp
#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

class Node {
public:
    int x, y;
    Node *prev, *next;

    Node(int x, int y) : x(x), y(y), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
public:
    Node *head, *tail;
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    ~DoublyLinkedList();

    void push_front(const Node& node);
    void push_back(const Node& node);
    void pop_back();;
    bool empty() const;
    Node& front() const;
    Node& back() const;
    void clear();
};

#endif // DOUBLY_LINKED_LIST_HPP
