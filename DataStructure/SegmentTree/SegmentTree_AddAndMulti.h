//
// Created by Rainy Memory on 2021/3/31.
//

#ifndef ARCHIVES_SEGMENTTREE_ADDANDMULTI_H
#define ARCHIVES_SEGMENTTREE_ADDANDMULTI_H

template<class T>
class SegmentTree {
private:
    T *tree;
    int size;
    T mod;
    T *addTag;
    T *multiTag;
    
    inline void _multi(T &original, T delta) {
        original = (original * delta) % mod;
    }
    
    inline void _add(T &original, T delta) {
        original = (original + delta) % mod;
    }
    
    inline void push_up(int p) {
        tree[p] = (tree[p << 1] + tree[p << 1 | 1]) % mod;
    }
    
    inline void push_down(int p, int s, int t) {
        if (multiTag[p] != 1) {
            _multi(multiTag[p << 1], multiTag[p]);
            _multi(multiTag[p << 1 | 1], multiTag[p]);
            _multi(addTag[p << 1], multiTag[p]);
            _multi(addTag[p << 1 | 1], multiTag[p]);
            _multi(tree[p << 1], multiTag[p]);
            _multi(tree[p << 1 | 1], multiTag[p]);
            multiTag[p] = 1;
        }
        if (addTag[p] != 0) {
            int m = (s + t) >> 1;
            _add(addTag[p << 1], addTag[p]);
            _add(addTag[p << 1 | 1], addTag[p]);
            _add(tree[p << 1], addTag[p] * (m - s + 1));
            _add(tree[p << 1 | 1], addTag[p] * (t - m));
            addTag[p] = 0;
        }
    }
    
    void inner_build(T *a, int s, int t, int p) {
        addTag[p] = 0, multiTag[p] = 1;
        if (s == t) {
            tree[p] = a[s];
            return;
        }
        int m = (s + t) >> 1;
        inner_build(a, s, m, p << 1);
        inner_build(a, m + 1, t, p << 1 | 1);
        push_up(p);
    }
    
    void inner_add(int l, int r, int s, int t, int p, T v) {
        if (l <= s && t <= r) {
            _add(addTag[p], v);
            _add(tree[p], v * (t - s + 1));
            return;
        }
        int m = (s + t) >> 1;
        if (addTag[p] != 0 || multiTag[p] != 1)push_down(p, s, t);
        if (l <= m)inner_add(l, r, s, m, p << 1, v);
        if (m < r)inner_add(l, r, m + 1, t, p << 1 | 1, v);
        push_up(p);
    }
    
    void inner_multi(int l, int r, int s, int t, int p, T v) {
        if (l <= s && t <= r) {
            _multi(multiTag[p], v);
            _multi(addTag[p], v);
            _multi(tree[p], v);
            return;
        }
        int m = (s + t) >> 1;
        if (addTag[p] != 0 || multiTag[p] != 1)push_down(p, s, t);
        if (l <= m)inner_multi(l, r, s, m, p << 1, v);
        if (m < r)inner_multi(l, r, m + 1, t, p << 1 | 1, v);
        push_up(p);
    }
    
    T inner_sum(int l, int r, int s, int t, int p) {
        if (l <= s && t <= r)return tree[p] % mod;
        T ret(0);
        int m = (s + t) >> 1;
        if (addTag[p] != 0 || multiTag[p] != 1)push_down(p, s, t);
        if (l <= m)_add(ret, inner_sum(l, r, s, m, p << 1));
        if (m < r)_add(ret, inner_sum(l, r, m + 1, t, p << 1 | 1));
        return ret;
    }

public:
    SegmentTree(T *a, int n, T p) : size(n), mod(p) {
        tree = new T[size << 2];
        addTag = new T[size << 2];
        multiTag = new T[size << 2];
        inner_build(a, 1, size, 1);
    }
    
    void rangeAdd(int l, int r, T v) {
        inner_add(l, r, 1, size, 1, v);
    }
    
    void rangeMulti(int l, int r, T v) {
        inner_multi(l, r, 1, size, 1, v);
    }
    
    T querySum(int l, int r) {
        return inner_sum(l, r, 1, size, 1);
    }
};

#endif //ARCHIVES_SEGMENTTREE_ADDANDMULTI_H
