#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

#define INIT_LEN 10

namespace sjtu {
    template<typename T>
    class vector {
    private:
        T *store;
        size_t tail;
        size_t length;
        
        void double_space() {
            length *= 2;
            T *temp = (T *) ::operator new(sizeof(T) * length);
            for (int i = 0; i < tail; i++) memcpy(temp + i, store + i, sizeof(T));
            for (T *p = store; p != store + tail; p++) p->~T();
            operator delete(store);
            store = temp;
        }
        
        void halve_space() {
            if (length > INIT_LEN) {
                length = (length / 2 < INIT_LEN ? INIT_LEN : length / 2);
                T *temp = (T *) ::operator new(sizeof(T) * length);
                for (int i = 0; i < tail; i++) memcpy(temp + i, store + i, sizeof(T));
                for (T *p = store; p != store + tail; p++)p->~T();
                operator delete(store);
                store = temp;
            }
        }
    
    public:
        class const_iterator;
        
        class iterator {
            friend class vector;
        
        private:
            vector<T> *vec;
            int pos;
        public:
            iterator(vector<T> *v, int p) : vec(v), pos(p) {}
            
            iterator(const iterator &other) : vec(other.vec), pos(other.pos) {}
            
            iterator operator+(const int &n) const {
                if (pos + n > vec->size())throw invalid_iterator();
                iterator temp(*this);
                temp.pos += n;
                return temp;
            }
            
            iterator operator-(const int &n) const {
                if (pos < n)throw invalid_iterator();
                iterator temp(*this);
                temp.pos -= n;
                return temp;
            }
            
            int operator-(const iterator &rhs) const {
                if (vec != rhs.vec)throw invalid_iterator();
                return pos - rhs.pos;
            }
            
            iterator &operator+=(const int &n) {
                if (pos + n > vec->size())throw invalid_iterator();
                pos += n;
                return *this;
            }
            
            iterator &operator-=(const int &n) {
                if (pos < n)throw invalid_iterator();
                pos -= n;
                return *this;
            }
            
            iterator operator++(int) {
                if (pos + 1 > vec->size())throw invalid_iterator();
                iterator temp(*this);
                pos++;
                return temp;
            }
            
            iterator &operator++() {
                if (pos + 1 > vec->size())throw invalid_iterator();
                pos++;
                return *this;
            }
            
            iterator operator--(int) {
                if (pos < 1)throw invalid_iterator();
                iterator temp(*this);
                pos--;
                return temp;
            }
            
            iterator &operator--() {
                if (pos < 1)throw invalid_iterator();
                pos--;
                return *this;
            }
            
            T &operator*() const {
                return vec->store[pos];
            }
            
            bool operator==(const iterator &rhs) const {
                if (vec == rhs.vec && pos == rhs.pos)return true;
                else return false;
            }
            
            bool operator==(const const_iterator &rhs) const {
                if (vec == rhs.vec && pos == rhs.pos)return true;
                else return false;
            }
            
            bool operator!=(const iterator &rhs) const {
                return !(*this == rhs);
            }
            
            bool operator!=(const const_iterator &rhs) const {
                return !(*this == rhs);
            }
        };
        
        class const_iterator {
            friend class vector;
        
        private:
            const vector<T> *vec;
            int pos;
        public:
            const_iterator(const vector<T> *v, int p) : vec(v), pos(p) {}
            
            const_iterator(const const_iterator &other) : vec(other.vec), pos(other.pos) {}
            
            const_iterator operator+(const int &n) const {
                if (pos + n > vec->size())throw invalid_iterator();
                iterator temp(*this);
                temp.pos += n;
                return temp;
            }
            
            const_iterator operator-(const int &n) const {
                if (pos < n)throw invalid_iterator();
                iterator temp(*this);
                temp.pos -= n;
                return temp;
            }
            
            int operator-(const iterator &rhs) const {
                if (vec != rhs.vec)throw invalid_iterator();
                return pos - rhs.pos;
            }
            
            const_iterator &operator+=(const int &n) {
                if (pos + n > vec->size())throw invalid_iterator();
                pos += n;
                return *this;
            }
            
            const_iterator &operator-=(const int &n) {
                if (pos < n)throw invalid_iterator();
                pos -= n;
                return *this;
            }
            
            const_iterator operator++(int) {
                if (pos + 1 > vec->size())throw invalid_iterator();
                iterator temp(*this);
                pos++;
                return temp;
            }
            
            const_iterator &operator++() {
                if (pos + 1 > vec->size())throw invalid_iterator();
                pos++;
                return *this;
            }
            
            const_iterator operator--(int) {
                if (pos < 1)throw invalid_iterator();
                iterator temp(*this);
                pos--;
                return temp;
            }
            
            const_iterator &operator--() {
                if (pos < 1)throw invalid_iterator();
                pos--;
                return *this;
            }
            
            T &operator*() const {
                return vec->store[pos];
            }
            
            bool operator==(const iterator &rhs) const {
                if (vec == rhs.vec && pos == rhs.pos)return true;
                else return false;
            }
            
            bool operator==(const const_iterator &rhs) const {
                if (vec == rhs.vec && pos == rhs.pos)return true;
                else return false;
            }
            
            bool operator!=(const iterator &rhs) const {
                return !(*this == rhs);
            }
            
            bool operator!=(const const_iterator &rhs) const {
                return !(*this == rhs);
            }
        };
        
        vector() : length(INIT_LEN), tail(0) {
            store = (T *) ::operator new(sizeof(T) * length);
        }
        
        vector(const vector &other) : length(other.length), tail(other.tail) {
            store = (T *) ::operator new(sizeof(T) * length);
            for (int i = 0; i < tail; i++)memcpy(store + i, other.store + i, sizeof(T));
        }
        
        ~vector() {
            for (T *p = store; p != store + tail; p++) p->~T();
            operator delete(store);
        }
        
        vector &operator=(const vector &other) {
            if (this == &other)return *this;
            for (T *p = store; p != store + tail; p++) p->~T();
            operator delete(store);
            length = other.length;
            tail = other.tail;
            store = (T *) ::operator new(sizeof(T) * length);
            for (int i = 0; i < tail; i++) memcpy(store + i, other.store + i, sizeof(T));
            return *this;
        }
        
        T &at(const size_t &pos) {
            if (pos < 0 || pos >= length)throw index_out_of_bound();
            return store[pos];
        }
        
        const T &at(const size_t &pos) const {
            if (pos < 0 || pos >= length)throw index_out_of_bound();
            return store[pos];
        }
        
        T &operator[](const size_t &pos) {
            if (pos < 0 || pos >= tail)throw index_out_of_bound();
            return store[pos];
        }
        
        const T &operator[](const size_t &pos) const {
            if (pos < 0 || pos >= tail)throw index_out_of_bound();
            return store[pos];
        }
        
        const T &front() const {
            if (tail == 0)throw container_is_empty();
            return store[0];
        }
        
        const T &back() const {
            if (tail == 0)throw container_is_empty();
            return store[tail - 1];
        }
        
        iterator begin() {
            if (tail == 0)throw container_is_empty();
            return iterator(this, 0);
        }
        
        const_iterator cbegin() const {
            if (tail == 0)throw container_is_empty();
            return const_iterator(this, 0);
        }
        
        iterator end() {
            if (tail == 0)throw container_is_empty();
            return iterator(this, tail);
        }
        
        const_iterator cend() const {
            if (tail == 0)throw container_is_empty();
            return const_iterator(this, tail);
        }
        
        bool empty() const {
            if (tail == 0)return true;
            else return false;
        }
        
        size_t size() const {
            return tail;
        }
        
        void clear() {
            for (T *p = store; p != store + tail; p++) p->~T();
            operator delete(store);
            tail = 0;
            length = INIT_LEN;
            store == (T *) ::operator new(sizeof(T) * length);
        }
        
        iterator insert(iterator pos, const T &value) {
            if (tail == length) double_space();
            for (int i = tail - 1; i >= pos.pos; i--)memcpy(store + 1 + i, store + i, sizeof(T));
            tail++;
            (store + pos.pos)->~T();
            new(store + pos.pos) T(value);
            pos++;
            return pos;
        }
        
        iterator insert(const size_t &ind, const T &value) {
            if (ind < 0 || ind > tail)throw index_out_of_bound();
            if (tail == length) double_space();
            for (int i = tail - 1; i >= ind; i--)memcpy(store + 1 + i, store + i, sizeof(T));
            tail++;
            (store + ind)->~T();
            new(store + ind) T(value);
            return iterator(this, ind + 1);
        }
        
        iterator erase(iterator pos) {
            for (int i = pos.pos; i < tail - 1; i++) memcpy(store + i, store + 1 + i, sizeof(T));
            tail--;
            (store + tail)->~T();
            return pos;
        }
        
        iterator erase(const size_t &ind) {
            for (int i = ind; i < tail - 1; i++)memcpy(store + i, store + 1 + i, sizeof(T));
            tail--;
            (store + tail)->~T();
            if ((tail < (length / 2)))halve_space();
            return iterator(this, ind);
        }
        
        void push_back(const T &value) {
            if (tail == length) double_space();
            new(store + tail) T(value);
            tail++;
        }
        
        void pop_back() {
            if (tail == 0)throw container_is_empty();
            tail--;
            (store + tail)->~T();
            if (tail < (length / 2))halve_space();
        }
    };
    
    
}

#endif
