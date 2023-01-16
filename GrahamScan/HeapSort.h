#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <math.h> 


/* ==== BINARY HEAP ==== */
template<typename T>
class BinaryHeap {
private:
    T* bHeap;
    int size;
    int capacity;

    int getParent(int i) {
        return floor((i - 1) / 2);
    }
    int getLeftChild(int i) {
        return (2 * i + 1);
    }
    int getRightChild(int i) {
        return (2 * i + 2);
    }
    void swap(int id, int secondid) {
        T temp = bHeap[id];
        bHeap[id] = bHeap[secondid];
        bHeap[secondid] = temp;
    }

    void fixHeap(int(*data_cmp)(T, T), int n, bool isTopDown) {
        if (isTopDown == true) {
            for (int i = 0; i < n; i++) {
                heapUp(i, data_cmp);
            }
        }
        else {
            for (int i = n - 1; i >= 0; i--) {
                heapDown(i, data_cmp);
            }
        }
        return;
    }
public:
    BinaryHeap() {
        size = 0;
        capacity = 0;
    }
    BinaryHeap(T* newArray, int n, int(*data_cmp)(T, T), bool isTopDown) {
        size = n;
        capacity = n;
        bHeap = newArray;

        fixHeap(data_cmp, n, isTopDown);
    }
    ~BinaryHeap() {
        size = 0;
        capacity = 0;
    }
    T operator [](int liczba) {
        if (liczba < size) {
            return *(bHeap + liczba);
        }
    }
    int getSize() {
        return size;
    }
    int getCapacity() {
        return capacity;
    }

    void sort(int(*data_cmp)(T, T)) {
        int n = size;
        for (int i = 0; i < n; i++) {
            swap(0, size - 1);
            size--;
            heapDown(0, data_cmp);
        }
        size = n;
    }

    void resize() {
        capacity *= 2;
        T* temp_array = new T[capacity];
        for (int i = 0; i < size; i++) {
            temp_array[i] = bHeap[i];
        }
        delete[] bHeap;
        bHeap = temp_array;
    }
    void add(T data, int(*data_cmp)(T, T)) {
        if (size == 0 && capacity == 0) {
            capacity = 1;
            bHeap = new T[capacity];
        }
        if (size == capacity) {
            resize();
        }
        bHeap[size] = data;
        heapUp(size, data_cmp);
        size++;
    }

    T poll(int(*data_cmp)(T, T)) {
        if (size > 0) {
            T temp = bHeap[0];

            bHeap[0] = bHeap[size - 1];
            size--;

            heapDown(0, data_cmp);
            return temp;
        }
        return NULL;
        //throw std::out_of_range;
    }

    void heapUp(int id, int(*data_cmp)(T, T)) {
        if (id > 0) {
            T temp;
            int parentId = getParent(id);
            int cmp = data_cmp(bHeap[id], bHeap[parentId]);
            if (cmp == 1) {
                swap(id, parentId);
                heapUp(parentId, data_cmp);
            }
        }
        return;
    }

    void heapDown(int id, int(*data_cmp)(T, T)) {
        int winner = id;
        if (getLeftChild(id) < size) {
            int cmp = data_cmp(bHeap[id], bHeap[getLeftChild(id)]);
            if (cmp == -1) {
                winner = getLeftChild(id);
            }
        }
        if (getRightChild(id) < size) {
            int cmp;
            if (winner != id) cmp = data_cmp(bHeap[winner], bHeap[getRightChild(id)]);
            else cmp = data_cmp(bHeap[id], bHeap[getRightChild(id)]);

            if (cmp == -1) {
                winner = getRightChild(id);
            }
        }
        if (winner != id) {
            swap(id, winner);
            heapDown(winner, data_cmp);
        }
        return;
    }

    std::string to_string() {
        std::ostringstream os;
        try {
            if (size != 0) {
                for (int i = 0; i < size; i++) {
                    os << i << ": ";
                    os << std::to_string(bHeap[i]) << "\n";
                }
            }
            else throw 1;
        }
        catch (...) {
            os << "Brak rekordow!\n";
        }
        return os.str();
    }
    std::string to_string(std::string(*data_to_str)(T)) {
        std::ostringstream os;
        try {
            if (size != 0) {
                for (int i = 0; i < size; i++) {
                    if (data_to_str) {
                        os << i << ": ";
                        os << data_to_str(bHeap[i]) << "\n";
                    }
                }
            }
            else throw 1;
        }
        catch (...) {
            os << "Brak rekordow!\n";
        }
        return os.str();
    }
    std::string to_string(std::string(*data_to_str)(T), int count) {
        std::ostringstream os;
        try {
            if (size != 0) {
                if (count > size) {
                    count = size;
                }
                for (int i = 0; i < count; i++) {
                    if (data_to_str) {
                        os << data_to_str(bHeap[i]) << "\n";
                    }
                }
            }
            else throw 1;
        }
        catch (...) {
            os << "Brak rekordow!\n";
        }
        return os.str();
    }

    void clear() {
        if (size > 0) {
            for (int i = 0; i < size; i++) {
                bHeap[i].~T();
            }
        }
        size = 0;
        capacity = 1;
        delete[] bHeap;
        bHeap = new T[capacity];
    }
    void clear(bool isPointer) {
        if (isPointer == true) {
            if (size > 0) {
                for (int i = 0; i < size; i++) {
                    bHeap[i].~T();
                    delete bHeap[i];
                }
            }
        }
        size = 0;
        capacity = 1;
        delete[] bHeap;
        bHeap = new T[capacity];
    }
};