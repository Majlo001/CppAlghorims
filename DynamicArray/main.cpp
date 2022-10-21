#include <iostream>
#include <string>
#include <time.h>
#include <sstream>



template<typename T>
class dynamic_array {
private:
    T* dArray;
    size_t size;
    size_t capacity;
public:
    dynamic_array() {
        size = 0;
        capacity = 1;
        dArray = new T[capacity];
    }
    ~dynamic_array() {
        size = NULL;
        capacity = NULL;
        delete[] dArray;
    }

    T operator [](size_t liczba) {
        if (liczba < size) {
            return *(dArray+liczba);
        }
    }

    size_t getSize() {
        return size;
    }
    size_t getCapacity() {
        return capacity;
    }

    void resize() {
        capacity *= 2;
        T* temp_array = new T[capacity];
        for (int i = 0; i < size; i++) {
            temp_array[i] = dArray[i];
        }
        delete[] dArray;
        dArray = temp_array;
    }
    void add(T data) {
        if (size == capacity) {
            resize();
        }
        size++;
        dArray[size-1] = data;
    }
    bool change(size_t indeks, T data) {
        if (indeks < size - 1) {
            dArray[indeks] = data;
            return 1;
        }
        return 0;
    }
    void clear() {
        delete[] dArray;
        size = 0;
        capacity = 1;
    }
};



int main() {
    dynamic_array<int> da;
    da.add(12);
    da.add(13);
    da.add(155);
    da.add(138348);
    da.add(1383);

    std::cout << da.getSize() << std::endl;
    std::cout << da.getCapacity() << std::endl;

    return 0;
}