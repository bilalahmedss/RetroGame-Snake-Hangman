// DoublyLinkedList.cpp
#include "DoublyLinkedList.hpp"

DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

void DoublyLinkedList::push_front(const Node& node) {
    Node* newNode = new Node(node.x, node.y);
    newNode->next = head;
    if (head) {
        head->prev = newNode;
    } else {
        tail = newNode;
    }
    head = newNode;
}

void DoublyLinkedList::push_back(const Node& node) {
    Node* newNode = new Node(node.x, node.y);
    newNode->prev = tail;
    if (tail) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
}

void DoublyLinkedList::pop_back() {
    if (!tail) {
        return;
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
}

bool DoublyLinkedList::empty() const {
    return head == nullptr;
}

Node& DoublyLinkedList::front() const {
    return *head;
}

Node& DoublyLinkedList::back() const {
    return *tail;
}

void DoublyLinkedList::clear() {
    while (!empty()) {
        pop_back();
    }
}




