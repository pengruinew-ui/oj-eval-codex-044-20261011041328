#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <string>

class mystring {
private:
    char *ch = nullptr; // dynamically allocated character array
    int len = 0;        // length of the string (number of characters)

    // helper to copy raw data
    void copy_from(const char *src, int n) {
        ch = new char[n];
        for (int i = 0; i < n; ++i) ch[i] = src[i];
        len = n;
    }

public:
    // default constructor – creates empty string
    mystring() : ch(nullptr), len(0) {}

    // construct with length and a character (int c is expected to be a char code)
    mystring(int _len, int c) {
        if (_len < 0) _len = 0;
        ch = new char[_len];
        for (int i = 0; i < _len; ++i) ch[i] = static_cast<char>(c);
        len = _len;
    }

    // construct from std::string (by reference as required by problem)
    mystring(std::string &s) {
        copy_from(s.c_str(), static_cast<int>(s.length()));
    }

    // copy constructor – deep copy to avoid shared ownership
    mystring(const mystring &other) {
        if (other.len > 0) copy_from(other.ch, other.len);
        else { ch = nullptr; len = 0; }
    }

    // copy assignment – deep copy, self‑check
    mystring &operator=(const mystring &other) {
        if (this != &other) {
            delete[] ch;
            if (other.len > 0) copy_from(other.ch, other.len);
            else { ch = nullptr; len = 0; }
        }
        return *this;
    }

    // destructor – free memory
    ~mystring() { delete[] ch; }

    // index operator – read‑only, returns '\0' when out of range
    char operator[](int idx) const {
        if (idx < 0 || idx >= len) return '\0';
        return ch[idx];
    }

    // less‑than comparison as described in the statement
    bool operator<(const mystring &rhs) const {
        int minlen = (len < rhs.len) ? len : rhs.len;
        for (int i = 0; i < minlen; ++i) {
            if (ch[i] != rhs.ch[i]) return ch[i] < rhs.ch[i];
        }
        return len < rhs.len;
    }

    // concatenate another mystring to this one
    void ADD(const mystring &other) {
        int newlen = len + other.len;
        char *newbuf = new char[newlen];
        for (int i = 0; i < len; ++i) newbuf[i] = ch[i];
        for (int i = 0; i < other.len; ++i) newbuf[len + i] = other.ch[i];
        delete[] ch;
        ch = newbuf;
        len = newlen;
    }

    // output the string (no newline)
    void out() const {
        for (int i = 0; i < len; ++i) std::cout << ch[i];
    }

    // retrieve length
    int get_len() const { return len; }
};

// Optional overload for stream output – not required but convenient
inline std::ostream &operator<<(std::ostream &os, const mystring &s) {
    s.out();
    return os;
}

#endif // MYSTRING_H

