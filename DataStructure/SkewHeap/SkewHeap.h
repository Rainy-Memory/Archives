//
// Created by Rainy Memory on 2021/2/25.
//

#ifndef ARCHIVES_SKEWHEAP_H
#define ARCHIVES_SKEWHEAP_H

class skewHeap {
private:
    class Node {
    public:
        T *value = nullptr;
        Node *leftChild = nullptr;
        Node *rightChild = nullptr;
        
        Node() = default;
        
        Node(const Node &o) {
            value = new T(*(o.value));
        }
        
        explicit Node(const T &o) {
            value = new T(o);
        }
        
        ~Node() {
            delete value;
        }
        
        void swap() {
            Node *temp = leftChild;
            leftChild = rightChild;
            rightChild = temp;
        }
    };
    
    Node *root = nullptr;
    size_t nodeNum = 0;
    
    void constructHeap(Node *src, Node *&target) {
        if (src == nullptr)return;
        target = new Node(*(src->value));
        constructHeap(src->leftChild, target->leftChild);
        constructHeap(src->rightChild, target->rightChild);
    }
    
    void destructHeap(Node *now) {
        if (now == nullptr)return;
        destructHeap(now->leftChild);
        destructHeap(now->rightChild);
        delete now;
    }
    
    Node *mergeHeap(Node *h1, Node *h2) {
        if (h1 == nullptr)return h2;
        if (h2 == nullptr)return h1;
        Compare cmp;
        if (cmp(*h1->value, *h2->value)) {
            Node *temp = h1;
            h1 = h2;
            h2 = temp;
        }
        h1->rightChild = mergeHeap(h1->rightChild, h2);
        h1->swap();
        return h1;
    }

public:
    
    skewHeap() = default;
    
    skewHeap(const skewHeap &o) : nodeNum(o.nodeNum) {
        constructHeap(o.root, root);
    }
    
    skewHeap &operator=(const skewHeap &o) {
        if (this == &o)return *this;
        clear();
        root = nullptr;
        nodeNum = o.nodeNum;
        constructHeap(o.root, root);
        return *this;
    }
    
    ~skewHeap() {
        destructHeap(root);
    }
    
    void clear() {
        destructHeap(root);
        nodeNum = 0;
    }
    
    void push(const T &o) {
        Node *h = new Node(o);
        root = mergeHeap(root, h);
        nodeNum++;
    }
    
    void pop() {
        Node *temp = root;
        root = mergeHeap(root->leftChild, root->rightChild);
        delete temp;
        nodeNum--;
    }
    
    void merge(skewHeap &o) {
        nodeNum += o.nodeNum;
        root = mergeHeap(root, o.root);
        o.root = nullptr;
        o.nodeNum = 0;
    }
    
    const T &top() const {
        return *(root->value);
    }
    
    size_t size() const {
        return nodeNum;
    }
};

#endif //ARCHIVES_SKEWHEAP_H
