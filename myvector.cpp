#include "MyVector.h"

template <typename T>
MyVector<T>::MyVector() : capacity(4), currentSize(0) {
    data = new T[capacity];
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other) : capacity(other.capacity), currentSize(other.currentSize) {
    data = new T[capacity];
    for (int i = 0; i < currentSize; ++i) {
        data[i] = other.data[i];
    }
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        currentSize = other.currentSize;
        data = new T[capacity];
        for (int i = 0; i < currentSize; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] data;
}

template <typename T>
void MyVector<T>::resize() {
    capacity *= 2;
    T* newData = new T[capacity];
    for (int i = 0; i < currentSize; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

template <typename T>
void MyVector<T>::push_back(const T& value) {
    if (currentSize >= capacity) resize();
    data[currentSize++] = value;
}

template <typename T>
void MyVector<T>::pop_back() {
    if (currentSize > 0) --currentSize;
}

template <typename T>
int MyVector<T>::size() const {
    return currentSize;
}

template <typename T>
int MyVector<T>::getCapacity() const {
    return capacity;
}

template <typename T>
bool MyVector<T>::empty() const {
    return currentSize == 0;
}

template <typename T>
T& MyVector<T>::operator[](int index) {
    static T dummy = T();
    if (index < 0 || index >= currentSize) return dummy;
    return data[index];
}

template <typename T>
const T& MyVector<T>::operator[](int index) const {
    static T dummy = T();
    if (index < 0 || index >= currentSize) return dummy;
    return data[index];
}

template <typename T>
void MyVector<T>::clear() {
    currentSize = 0;
}
