#ifndef MYVECTOR_H
#define MYVECTOR_H

template <typename T>
class MyVector {
    T* data;
    int capacity;
    int currentSize;

    void resize();

public:
    MyVector();
    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    ~MyVector();

    void push_back(const T& value);
    void pop_back();
    int size() const;
    int getCapacity() const;
    bool empty() const;

    T& operator[](int index);
    const T& operator[](int index) const;

    void clear();
};

#endif