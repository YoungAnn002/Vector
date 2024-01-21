#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <iostream>
#include <stdexcept>
using std::size_t;

template<typename T>
class Vector {
    enum { CHUNK = 10 };
    size_t capacity = 0;    // Size of the current array allocation (total number of ints, in use or not)
    size_t n_elems = 0;     // Number of int spaces currently in use, starting from position 0
    T* data_ptr = nullptr;      // Pointer to the heap array
    void grow() {
        capacity = capacity * 1.6;
        T* temp = new T[capacity];
        for (unsigned int i = 0; i < n_elems; i++) {
            temp[i] = data_ptr[i];
        }
        delete[] data_ptr;
        data_ptr = temp;

    };
public:
    // Object Mgt.
    Vector() {
        capacity = 10;
        n_elems = 0;
        data_ptr = new T[capacity];
    };
    Vector(const Vector& v) {

        capacity = v.capacity;
        n_elems = v.n_elems;
        data_ptr = new T[CHUNK];

        for (unsigned int i = 0; i < n_elems; i++) {
            data_ptr[i] = v.data_ptr[i];
        }

    }; // Copy constructor
    Vector& operator=(const Vector& v) {
        capacity = v.capacity;
        n_elems = v.n_elems;
        data_ptr = new T[CHUNK];

        for (unsigned int i = 0; i < n_elems; i++) {
            data_ptr[i] = v.data_ptr[i];
        }

        return *this;

    }; // Copy assignment operator
    ~Vector() {
        delete[] data_ptr;
    };

    // Accessors
    T front() const {
        if (n_elems == 0) {
            throw std::range_error("out of range");
        }

        return data_ptr[0];
    };                  // Return the int in position 0, if any
    T back() const {
        if (n_elems == 0) {
            throw std::range_error("out of range");
        }

        return data_ptr[n_elems - 1];
    };                   // Return last element (position n_elems-1)
    T at(size_t pos) const {
        if (n_elems == 0) {
            throw std::range_error("out of range");
        }
        return data_ptr[pos];
    };           // Return element in position "pos" (0-based)
    size_t size() const {
        return n_elems;
    };                // Return n_elems
    bool empty() const {
        return n_elems == 0;
    };                 // Return n_elems == 0

    // Mutators
    T& operator[](size_t pos) {
        return data_ptr[pos];
    };        // Same as at but no bounds checking
    void push_back(T item) {

        data_ptr[n_elems] = item;
        n_elems++;

        //std::cout << n_elems << std::endl;
        if (n_elems > capacity) {
            grow();
        }

    };           // Append a new element at the end of the array
    void pop_back() {
        if (n_elems == 0) {
            throw std::range_error("out of range");
        }
        --n_elems;
    };                    // --n_elems (nothing else to do; returns nothing)
    void erase(size_t pos) {
        int blank = 0;
        if (n_elems == 0) {
            throw std::range_error("out of range");
        }
        if (n_elems >= capacity) {
            grow();
        }
        for (unsigned int i = pos; i <= n_elems; i++) {
            if (i + 1 <= n_elems) {
                data_ptr[i] = data_ptr[i + 1];
            }
        }
        data_ptr[n_elems] = blank;
        --n_elems;

    };             // Remove item in position pos and shuffles following items left
    void insert(size_t pos, T item) {
        if (n_elems >= capacity) {
            grow();
        }

        if (n_elems == 1) {

            data_ptr[1] = data_ptr[0];

        }
        else {
            for (unsigned int i = n_elems; i >= pos; i--) {

                data_ptr[i] = data_ptr[i - 1];

            }
        }

        data_ptr[pos] = item;
        ++n_elems;

    };  // Shuffle items right to make room for a new element
    void clear() {
        n_elems = 0;
    };                       // n_elems = 0 (nothing else to do; keep the current capacity)

    // Iterators
    T* begin() {
        T* beg;

        if (n_elems == 0) {
            beg = nullptr;
        }
        else {
            beg = &data_ptr[0];
        }
        return beg;
    };                       // Return a pointer to 1st element, or nullptr if n_elems == 0
    T* end() {
        T* last;
        if (n_elems == 0) {
            last = nullptr;
        }
        else {
            last = &data_ptr[n_elems];
        }
        return last;
    };                         // Return a pointer to 1 past last element, or nullptr if n_elems == 0

    // Comparators
    bool operator==(const Vector& v) const {
        int matches = 0;

        if (&v.data_ptr == &data_ptr) {
            return true;
        }
        else if (v.n_elems == n_elems) {
            for (unsigned int i = 0; i < n_elems; i++) {
                if (v.data_ptr[i] == data_ptr[i]) {
                    matches++;
                }
            }
            if (matches == n_elems) {
                return true;
            }
            else {
                return false;
            }

        }
        else {
            return false;
        }

    };
    bool operator!=(const Vector& v) const {
        int matches = 0;

        if (&v.data_ptr == &data_ptr) {
            return false;
        }
        else if (v.n_elems == n_elems) {
            for (unsigned int i = 0; i < n_elems; i++) {
                if (v.data_ptr[i] == data_ptr[i]) {
                    matches++;
                }
            }
            if (matches == n_elems) {
                return false;
            }
            else {
                return true;
            }

        }
        else {
            return true;
        }

    };
};

#endif
