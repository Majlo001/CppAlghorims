#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <math.h> 

static int counter = 0;

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

public:
    BinaryHeap() {
        size = 0;
        capacity = 0;
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
        if (size != 0) {
            T temp = bHeap[0];

            //je¿eli parmamanet delete
            /*bHeap[0].~T();
            delete bHeap[0];*/

            bHeap[0] = bHeap[size - 1];
            size--;

            heapDown(0, data_cmp);
            return temp;
        }
        return NULL;
    }

    void heapUp(int id, int(*data_cmp)(T, T)) {
        if (id > 0) {
            T temp;
            int parentId = getParent(id);
            int cmp = data_cmp(bHeap[id], bHeap[parentId]);
            if (cmp == 1) {
                temp = bHeap[id];
                bHeap[id] = bHeap[parentId];
                bHeap[parentId] = temp;
                heapUp(parentId, data_cmp);
            }
        }
        return;
    }
    void heapDown(int id, int(*data_cmp)(T, T)) {
        if (size - 1 < getLeftChild(id)) return;
        if (id < size) {
            T temp;
            int leftChildId = getLeftChild(id);
            int cmp = data_cmp(bHeap[leftChildId], bHeap[leftChildId + 1]);
            if (cmp == 1 || cmp == 0) {
                cmp = data_cmp(bHeap[id], bHeap[leftChildId]);
                if (cmp == -1) {
                    temp = bHeap[id];
                    bHeap[id] = bHeap[leftChildId];
                    bHeap[leftChildId] = temp;
                    heapDown(leftChildId, data_cmp);
                }
            }
            else {
                cmp = data_cmp(bHeap[id], bHeap[leftChildId+1]);
                if (cmp == -1) {
                    temp = bHeap[id];
                    bHeap[id] = bHeap[leftChildId + 1];
                    bHeap[leftChildId + 1] = temp;
                    heapDown(leftChildId + 1, data_cmp);
                }
            }
            //else {
            //    //Powtórzenie here
            //}
        }
        return;
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
    }
};



int main()
{
    const int MAX_ORDER = 7;
    BinaryHeap<Person*>* bh = new BinaryHeap<Person*>();

    bh->add(new Person(23, "Adam", "Adamiak", 1000), person_cmp);
    bh->add(new Person(35, "Adam", "Adamiak", 1000), person_cmp);
    bh->add(new Person(21, "Adam", "Adamiak", 1000), person_cmp);
    bh->add(new Person(9, "Adam", "Adamiak", 1000), person_cmp);
    bh->add(new Person(60, "Adam", "Adamiak", 1000), person_cmp);
    bh->add(new Person(69, "Adam", "Adamiak", 1000), person_cmp);
    bh->add(new Person(62, "Adam", "Adamiak", 1000), person_cmp);

    std::cout << bh->to_string(person_to_str) << std::endl;
    std::cout << bh->poll(person_cmp) << std::endl;
    std::cout << bh->to_string(person_to_str) << std::endl;


    bh->clear(true);
    return 0;
}