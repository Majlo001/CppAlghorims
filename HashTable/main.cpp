#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <math.h> 
#include <cmath> 
#include "List.h"

/* ==== PERSON ==== */
class Person {
public:
    int pesel;
    std::string imie;
    std::string nazwisko;
    int rok_urodzenia;

    Person(int pesel, std::string imie, std::string nazwisko, int rok_urodzenia) {
        this->pesel = pesel;
        this->imie = imie;
        this->nazwisko = nazwisko;
        this->rok_urodzenia = rok_urodzenia;
    }
    Person() {}
    ~Person() {
        pesel = 0;
        imie = "";
        nazwisko = "";
        rok_urodzenia = 0;
    }

    std::ostream& operator<<(std::ostream& os)
    {
        os << imie << ' ' << nazwisko << ' ' << pesel << ' ' << rok_urodzenia;
        return os;
    }
};

template<typename T>
int normal_cmp(T a, T b) {
    if (a == b) return 0;
    else if (a < b) return -1;
    else return 1;
}
int person_cmp(Person p1, Person p2) {
    if (p1.pesel == p2.pesel) return 0;
    else if (p1.pesel < p2.pesel) return -1;
    else return 1;
}
int person_cmp(Person* p1, Person* p2) {
    if (p1->pesel == p2->pesel) return 0;
    else if (p1->pesel < p2->pesel) return -1;
    else return 1;
}

std::string person_to_str(Person p) {
    return "[" + p.imie + " " + p.nazwisko + " " + std::to_string(p.pesel) + " " + std::to_string(p.rok_urodzenia) + "]";
}
std::string person_to_str(Person* p) {
    return "[" + p->imie + " " + p->nazwisko + " " + std::to_string(p->pesel) + " " + std::to_string(p->rok_urodzenia) + "]";
}

template<typename T>
std::string not_str(T str) {
    return std::to_string(str);
}
std::string just_str(std::string str) {
    return str;
}




/* ==== HASH TABLE ==== */
template<typename T>
class HashTable {
private:
    List<T>* dArray;
    size_t size;
    size_t capacity;
public:
    HashTable() {
        size = 0;
        capacity = 0;
    }
    ~HashTable() {
        size = 0;
        capacity = 0;
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

    void resize() {
        capacity *= 2;
        List<T>* temp_array = new List<T>[capacity];

        //TODO: funkcja rehashująca

        for (int i = 0; i < capacity; i++) {
            List<T>* list = new List<T>();
            dArray[i] = *list;
        }
        delete[] dArray;
        dArray = temp_array;
    }
    void add(std::string key, T value) {
        if (size == 0 && capacity == 0) {
            capacity = 1024;
            dArray = new List<T>[capacity];

            for (int i = 0; i < capacity; i++) {
                List<T>* list = new List<T>();
                dArray[i] = *list;
            }
            return;
        }
        if (size/capacity >= 0.75) {
            resize();
        }
        dArray[hashValue(key)].add(key, value);
        size++;
    }

    ListNode<T>* get(std::string key) {
        if (size != 0 && key != "") {
            return dArray[hashValue(key)].get(key);
        }
        return NULL;
    }

    bool remove(std::string key) {
        return dArray[hashValue(key)].remove(key);
    }

    /*bool change(size_t indeks, T data) {
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
    }*/



    int hashValue(std::string str) {
        int value = 0;
        int strCount = str.size();

        for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
            strCount--;
            value += int(*it) * pow(31, strCount);
        }
        value = value % capacity;
        return value;
    }

};


std::string randomString(int len) {
    const char chars[] = "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
    std::string tmp;
    tmp.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp += chars[rand() % (sizeof(chars) - 1)];
    }

    return tmp;
}






int main()
{
    HashTable<int>* ha = new HashTable<int>();

    for (int i = 0; i < 10; i++) {
        int randnum = rand() % 1000000 + 1;
        ha->add(randomString(6), i);
    }
    ha->add("kotkot", 2022);

    std::cout << ha->get("kotkot") << std::endl;
    std::cout << ha->remove("kotkot") << std::endl;
    std::cout << ha->get("kotkot") << std::endl;
}