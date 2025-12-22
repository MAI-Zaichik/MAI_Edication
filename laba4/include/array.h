#ifndef ARRAY_H
#define ARRAY_H

#include <memory>

template<typename T>
class Array {
private:
    std::shared_ptr<T[]> elements;
    size_t count;
    size_t capacity;

    void expand() {
        size_t new_capacity = capacity * 2;
        std::shared_ptr<T[]> new_elements(new T[new_capacity]);

        for (size_t i = 0; i < count; ++i) {
            new_elements[i] = std::move(elements[i]);
        }

        elements = new_elements;
        capacity = new_capacity;
    }

public:
    Array() : count(0), capacity(10) {
        elements = std::shared_ptr<T[]>(new T[capacity]);
    }

    void add(const T& element) {
        if (count >= capacity) expand();
        elements[count] = element;
        count++;
    }
    
    void add(T&& element) {
        if (count >= capacity) expand();
        elements[count] = std::move(element);
        count++;
    }

    void remove(size_t index) {
        if (index >= count) return;

        for (size_t i = index; i < count - 1; ++i) {
            elements[i] = std::move(elements[i + 1]);
        }
        count--;
    }

    T& operator[](size_t index) {
        return elements[index];
    }

    const T& operator[](size_t index) const {
        return elements[index];
    }

    size_t size() const { return count; }
    bool empty() const { return count == 0; }
};

#endif