//
// Created by Rainy Memory on 2021/3/1.
//

#ifndef ARCHIVES_DOUBLYLINKEDLIST_H
#define ARCHIVES_DOUBLYLINKEDLIST_H

template<class T>
class DoublyLinkedList {
private:
    class Node {
    public:
        T value = 0;
        Node *next = nullptr;
        Node *pre = nullptr;
        
        Node() = default;
        
        explicit Node(const T &o) : value(o) {}
        
        ~Node() = default;
    };
    
    Node *head = nullptr;
    Node *tail = nullptr;
    int len = 0;

public:
    DoublyLinkedList() {
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->pre = head;
    }
    
    ~DoublyLinkedList() {
        Node *temp = head;
        while (head != nullptr) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }
    
    void push_front(const T &o) {
        len++;
        Node *temp = new Node(o);
        temp->next = head->next;
        head->next->pre = temp;
        head->next = temp;
        temp->pre = head;
    }
    
    void push_back(const T &o) {
        len++;
        Node *temp = new Node(o);
        temp->next = tail;
        temp->pre = tail->pre;
        tail->pre->next = temp;
        tail->pre = temp;
        len++;
    }
    
    void pop_front() {
        len--;
        Node *temp = head->next;
        head->next = head->next->next;
        head->next->pre = head;
        delete temp;
    }
    
    void pop_back() {
        len--;
        Node *temp = tail->pre;
        tail->pre = tail->pre->pre;
        tail->pre->next = tail;
        delete temp;
    }
    
    Node *findNode(int index) {
        if (index < len / 2) {
            Node *temp = head;
            for (int i = 0; i < index; i++)temp = temp->next;
            return temp;
        }
        else {
            Node *temp = tail;
            for (int i = 0; i < (len + 1 - index); i++)temp = temp->pre;
            return temp;
        }
    }
    
    void insert(int index, const T &o) {
        //insert after index
        Node *temp = findNode(index);
        Node *newNode = new Node(o);
        newNode->next = temp->next;
        newNode->pre = temp;
        temp->next->pre = newNode;
        temp->next = newNode;
        len++;
    }
    
    void erase(int index) {
        Node *eraseNode = findNode(index);
        eraseNode->next->pre = eraseNode->pre;
        eraseNode->pre->next = eraseNode->next;
        delete eraseNode;
        len--;
    }
};

#endif //ARCHIVES_DOUBLYLINKEDLIST_H
