//
// Created by Rainy Memory on 2021/3/4.
//

#ifndef ARCHIVES_TOKENSCANNER_H
#define ARCHIVES_TOKENSCANNER_H

#include <iostream>

using std::string;

class TokenScanner {
private:
    string buffer;
    char delim;
    int pos;

public:
    explicit TokenScanner(const string &Buffer, char Delim = ' ') : buffer(Buffer), delim(Delim), pos(0) {
        while (buffer[pos] == delim)pos++;
    }
    
    string nextToken() {
        int next = pos;
        while (buffer[next] != delim && next < buffer.length())next++;
        string ret;
        for (int i = pos; i < next; i++)ret += buffer[i];
        pos = next + 1;
        if (pos < buffer.length())while (buffer[pos] == delim)pos++;
        return ret;
    }
    
    bool empty() const {
        return pos >= buffer.length();
    }
    
    void resetBuffer(const string &b) {
        buffer = b;
        pos = 0;
    }
    
    void resetDelim(char Delim) {
        delim = Delim;
    }
    
    void clear() {
        buffer.clear();
        delim = ' ';
        pos = 0;
    }
};

#endif //ARCHIVES_TOKENSCANNER_H
