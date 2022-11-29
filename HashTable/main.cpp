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
        for (int i = 0; i < capacity; i++) {
            List<T>* list = new List<T>();
            temp_array[i] = *list;
        }
        rehash(temp_array);

        delete[] dArray;
        dArray = temp_array;
    }
    void rehash(List<T>* temp_array) {
        int temp_cap = capacity / 2;
        size = 0;

        for (int i = 0; i < temp_cap; i++) {
            if (dArray[i].isEmpty() == 0) {
                for (int j = 0; j < dArray[i].getSize(); j++) {
                    ListNode<T>* temp_object = dArray[i].getRehash();

                    ListNode<T>* new_object = temp_array[hashValue(temp_object->key)].get(temp_object->key);
                    if (new_object == NULL) {
                        temp_array[hashValue(temp_object->key)].add(temp_object->key, temp_object->value);
                        size++;
                    }
                    else {
                        temp_array[hashValue(temp_object->key)].overwrite(temp_object->key, temp_object->value);
                    }
                }
            }
            dArray[i].del_all();
            dArray[i].~List();
        }
    }
    void add(std::string key, T value) {
        if (size == 0 && capacity == 0) {
            capacity = 1024;
            dArray = new List<T>[capacity];

            for (int i = 0; i < capacity; i++) {
                List<T>* list = new List<T>();
                dArray[i] = *list;
            }
        }
        if (size/capacity >= 0.75) {
            resize();
        }

        ListNode<T>* temp_object = dArray[hashValue(key)].get(key);
        if (temp_object == NULL) {
            dArray[hashValue(key)].add_order(key, value);
            size++;
        }
        else {
            dArray[hashValue(key)].overwrite(key, value);
        }
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

    std::string to_string() {
        std::ostringstream os;
        try {
            if (size != 0) {
                os << "current_size: " << size << "\n";
                os << "max_size: " << capacity << "\n";
                os << "table:\n";
                for (int i = 0; i < capacity; i++) {
                    if (dArray[i].isEmpty() == 0) {
                        os << std::to_string(i) << ": " << dArray[i].to_string() << "\n";
                    }
                }
                os << getStats();
            }
            else throw 1;
        }
        catch (...) {
            os << "Wszystkie listy puste!\n";
        }
        return os.str();
    }
    std::string to_string(int count) {
        std::ostringstream os;
        try {
            if (size != 0) {
                os << "current_size: " << size << "\n";
                os << "max_size: " << capacity << "\n";
                os << "table:\n";
                if (count > size) {
                    count = size;
                }
                for (int i = 0; i < capacity; i++) {
                    if (dArray[i].isEmpty() == 0 && count != 0) {
                        os << std::to_string(i) << ": " << dArray[i].to_string() << "\n";
                        count--;
                    }
                }
                os << "...\n";
                os << getStats();
            }
            else throw 1;
        }
        catch (...) {
            os << "Wszystkie listy puste!\n";
        }
        return os.str();
    }
    std::string to_string(std::string(*data_to_str)(T)) {
        std::ostringstream os;
        try {
            if (size != 0) {
                os << "current_size: " << size << "\n";
                os << "max_size: " << capacity << "\n";
                os << "table:\n";
                for (int i = 0; i < capacity; i++) {
                    if (dArray[i].isEmpty() == 0) {
                        if (data_to_str) {
                            os << std::to_string(i) << ": " << dArray[i].to_string(data_to_str) << "\n";
                        }
                    }
                }
                os << getStats();
            }
            else throw 1;
        }
        catch (...) {
            os << "Wszystkie listy puste!\n";
        }
        return os.str();
    }
    std::string to_string(std::string(*data_to_str)(T), int count) {
        std::ostringstream os;
        try {
            if (size != 0) {
                os << "current_size: " << size << "\n";
                os << "max_size: " << capacity << "\n";
                os << "table:\n";
                if (count > size) {
                    count = size;
                }
                for (int i = 0; i < capacity; i++) {
                    if (dArray[i].isEmpty() == 0 && count != 0) {
                        if (data_to_str) {
                            os << std::to_string(i) << ": " << dArray[i].to_string(data_to_str) << "\n";
                        }
                        count--;
                    }
                }
                os << "...\n";
                os << getStats();
            }
            else throw 1;
        }
        catch (...) {
            os << "Brak rekordow!\n";
        }
        return os.str();
    }

    std::string getStats() {
        std::ostringstream os;
        int min = 1000;
        int max = 0;
        int nonNull = 0;

        for (int i = 0; i < capacity; i++) {
            if (dArray[i].isEmpty() == 0) {
                if (dArray[i].getSize() < min) {
                    min = dArray[i].getSize();
                }
                if (dArray[i].getSize() > max) {
                    max = dArray[i].getSize();
                }
                nonNull++;
            }
        }

        double avgSize = (double)size / (double)nonNull;

        os << "stats:\n";
        os << "list min size: " << std::to_string(min) << "\n";
        os << "list max size: " << std::to_string(max) << "\n";
        os << "non-null lists: " << std::to_string(nonNull) << "\n";
        os << "list avg size: " << std::to_string(avgSize) << "\n";

        return os.str();
    }


    void clear() {
        for (int i = 0; i < capacity; i++) {
            dArray[i].del_all();
            dArray[i].~List();
        }
        size = 0;
        capacity = 1024;
        delete[] dArray;

        dArray = new List<T>[capacity];
        for (int i = 0; i < capacity; i++) {
            List<T>* list = new List<T>();
            dArray[i] = *list;
        }
    }
    void clear(bool isPointer) {
        for (int i = 0; i < capacity; i++) {
            /*if (dArray[i].isEmpty() == 0) {
                for (int j = 0; j < dArray[i].getSize(); j++) {

                }
            }*/
            dArray[i].del_all(isPointer);
            dArray[i].~List();
        }
        size = 0;
        capacity = 1024;
        delete[] dArray;

        dArray = new List<T>[capacity];
        for (int i = 0; i < capacity; i++) {
            List<T>* list = new List<T>();
            dArray[i] = *list;
        }
    }



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






//int main()
//{
//    HashTable<int>* ha = new HashTable<int>();
//
//    for (int i = 0; i < 10; i++) {
//        //int randnum = rand() % 1000000 + 1;
//        ha->add(randomString(6), i);
//    }
//    ha->add("kotkot", 2022);
//    ha->add("kotkot", 99);
//
//    /*std::cout << ha->get("kotkot") << std::endl;
//    std::cout << ha->remove("kotkot") << std::endl;
//    std::cout << ha->get("kotkot") << std::endl;*/
//
//    std::cout << ha->to_string() << std::endl;
//    std::cout << "RESIZE:::" << std::endl;
//    ha->resize();
//    std::cout << ha->to_string() << std::endl;
//
//
//    ha->clear();
//}


int main()
{
    const int MAX_ORDER = 7;
    HashTable<int>* ht = new HashTable<int>();

    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = pow(10, o);

        clock_t t1 = clock();
        for (int i = 0; i < n; i++)
        {
            ht->add(randomString(6), i);
        }
        clock_t t2 = clock();

        std::cout << ht->to_string(16) << std::endl;

        double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
        std::cout << "Pomiar czasowy dodawania: " << time << "s dla 10^" << o << " elementow." << std::endl;
        std::cout << "Czas zamortyzowany: " << (time / n) * 1000 * 1000 * 1000 << " ns" << std::endl;

        const int m = pow(10, 4);
        int hits = 0;
        t1 = clock();

        for (int i = 0; i < m; i++){
            ListNode<int>* entry = ht->get(randomString(6));
            if (entry != NULL) hits++;
        }
        t2 = clock();

        time = (t2 - t1) / (double)CLOCKS_PER_SEC;
        std::cout << "Ilosc trafien: " << std::to_string(hits) << std::endl;
        std::cout << "Pomiar czasowy szukania: " << time << "s dla 10^" << o << " elementow.\n\n" << std::endl;

        ht->clear();
    }
    delete ht;
    return 0;
}