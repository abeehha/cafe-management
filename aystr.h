#ifndef AYSTR_H
#define AYSTR_H

#include <iostream>

class AYstr {
    int len;
    int cap;
    char* Cs;

    int strlength(const char* str);
    void regrow(int newcap);
    void strcpy(char* dest, const char* src);
    void inttostr(int num, char* buffer);
    int strtoint(const char* str);

public:
    AYstr();
    AYstr(const char* p);
    AYstr(int size, char ch);
    AYstr(int num);
    AYstr(const AYstr& other);
    ~AYstr();

    void print() const;
    void replacefirst(char c);
    AYstr& trim();
    static AYstr trim(const char* str);
    bool isequal(const AYstr& S);
    bool isless(const AYstr& S);
    bool isgreater(const AYstr& S);

    char operator[](int i) const;
    char& operator[](int i);
    AYstr concat(const AYstr& s) const;
    AYstr& append(const AYstr& s);
    AYstr operator+(const AYstr& s) const;
    AYstr operator+=(const AYstr& s);

    int* all_sub_strings(const char* substring, int& count) const;
    int find_first(char ch);
    int find_first(const AYstr& substring) const;
    int find_last(char ch);
    int find_last(const AYstr& substring) const;
    int* find_all(char ch, int& count) const;
    int* find_all(const AYstr& sub, int& count) const;

    void insert_at(int i, char ch);
    void insert_at(int i, const AYstr& sub);
    void remove_at(int i);
    void remove_first(char ch);
    void remove_last(char ch);
    void remove_all(char ch);

    AYstr ToUpper() const;
    AYstr ToLower() const;
    void ToUpper();
    void ToLower();
    void clear();
};

#endif // AYSTR_H