//
// Created by Rainy Memory on 2021/3/4.
//

#ifndef ARCHIVES_BINARYINDEXTREE_H
#define ARCHIVES_BINARYINDEXTREE_H

class BinaryIndexTree {
private:
    int *tree;
    int len;
    
    inline int lowbit(int x) {
        return x & -x;
    }

public:
    BinaryIndexTree(int *arr, int _len) : len(_len) {
        tree = new int[len + 1]();
        for (int i = 1; i <= len; i++) {
            tree[i] += arr[i - 1];
            int j = i + lowbit(i);
            if (j <= len)tree[j] += tree[i];
        }
    }
    
    ~BinaryIndexTree() {
        delete[]tree;
    }
    
    void update(int index, int value) {
        index++;
        while (index <= len) {
            tree[index] += value;
            index += lowbit(index);
        }
    }
    
    int prefixSum(int index) {
        index++;
        int result = 0;
        while (index > 0) {
            result += tree[index];
            index -= lowbit(index);
        }
        return result;
    }
    
    int rangeSum(int l, int r) {
        //return range [l, r] sum
        return prefixSum(r) - prefixSum(l - 1);
    }
};

#endif //ARCHIVES_BINARYINDEXTREE_H
