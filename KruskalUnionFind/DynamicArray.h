#pragma once

template<typename T>
class dynamicArray {
private:
    T* dArray;
    size_t size;
    size_t capacity;
public:
    dynamicArray() {
        size = 0;
        capacity = 0;
    }
    ~dynamicArray() {
        size = 0;
        capacity = 0;
        //delete[] dArray;
    }

    T operator [](size_t liczba) {
        if (liczba < size) {
            return *(dArray + liczba);
        }
    }

    size_t getSize() {
        return size;
    }
    size_t getCapacity() {
        return capacity;
    }
    T* getArray() {
        return dArray;
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
        if (size == 0 && capacity == 0) {
            capacity = 1;
            dArray = new T[capacity];
        }
        if (size == capacity) {
            resize();
        }
        size++;
        dArray[size - 1] = data;
    }
    bool change(size_t indeks, T data) {
        if (indeks < size - 1 && size != 0) {
            dArray[indeks] = data;
            return 1;
        }
        return 0;
    }

    T get_index(size_t indeks) {
        if (size != 0) {
            if (indeks < size - 1) {
                return dArray[indeks];
            }
        }
    }
    bool change(size_t indeks, T data, bool isPointer) {
        if (indeks < size - 1 && size != 0) {
            if (isPointer == true) {
                delete dArray[indeks];
            }
            dArray[indeks] = data;
            return 1;
        }
        return 0;
    }
    void clear() {
        if (size > 0) {
            for (int i = 0; i < size; i++) {
                dArray[i].~T();
            }
        }
        size = 0;
        capacity = 1;
        delete[] dArray;
    }
    void clear(bool isPointer) {
        if (isPointer == true) {
            if (size > 0) {
                for (int i = 0; i < size; i++) {
                    dArray[i].~T();
                    delete dArray[i];
                }
            }
        }
        size = 0;
        capacity = 1;
        delete[] dArray;
    }

    void bubbleSort(int(*data_cmp)(T, T)) {
        if (size > 1) {
            T temp;

            for (int i = 0; i < size - 1; i++) {
                for (int j = 0; j < size - i - 1; j++) {
                    int cmp = data_cmp(dArray[j], dArray[j + 1]);
                    if (cmp == 1) {
                        temp = dArray[j];
                        dArray[j] = dArray[j + 1];
                        dArray[j + 1] = temp;
                    }
                }
            }
        }
    }
    void bubbleSort() {
        if (size > 1) {
            T temp;

            for (int i = 0; i < size - 1; i++) {
                for (int j = 0; j < size - i - 1; j++) {
                    if (dArray[j] > dArray[j + 1]) {
                        temp = dArray[j];
                        dArray[j] = dArray[j + 1];
                        dArray[j + 1] = temp;
                    }
                }
            }
        }
    }

    std::string show_index(std::string(*data_to_str)(T), int indeks) {
        std::ostringstream os;
        if (size != 0) {
            if (indeks < size - 1) {
                if (data_to_str) {
                    os << data_to_str(dArray[indeks]) << "\n";
                }
            }
            else {
                os << "Indeks poza zakresem!\n";
            }
        }
        else {
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
                        os << data_to_str(dArray[i]) << "\n";
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
                        os << data_to_str(dArray[i]) << "\n";
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
};