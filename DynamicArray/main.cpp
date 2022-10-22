#include <iostream>
#include <string>
#include <time.h>
#include <sstream>

class Person {
public:
    std::string pesel;
    std::string imie;
    std::string nazwisko;
    int rok_urodzenia;

    Person(std::string pesel, std::string imie, std::string nazwisko, int rok_urodzenia) {
        this->pesel = pesel;
        this->imie = imie;
        this->nazwisko = nazwisko;
        this->rok_urodzenia = rok_urodzenia;
    }
    Person() {}
    ~Person() {
        pesel = "";
        imie = "";
        nazwisko = "";
        rok_urodzenia = NULL;
    }

    std::ostream& operator<<(std::ostream& os)
    {
        os << imie << ' ' << nazwisko << ' ' << pesel << ' ' << rok_urodzenia;
        return os;
    }
};


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
    return p.imie + " " + p.nazwisko + " " + p.pesel + " " + std::to_string(p.rok_urodzenia);
}
std::string person_to_str(Person* p) {
    return p->imie + " " + p->nazwisko + " " + p->pesel + " " + std::to_string(p->rok_urodzenia);
}

template<typename T>
std::string not_str(T str) {
    return std::to_string(str);
}
std::string just_str(std::string str) {
    return str;
}

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
        if (size == 0) {
            dArray = new T[capacity];
        }
        if (size == capacity) {
            resize();
        }
        size++;
        dArray[size-1] = data;
    }
    bool change(size_t indeks, T data) {
        if (indeks < size - 1 && size != 0) {
            dArray[indeks] = data;
            return 1;
        }
        return 0;
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
        delete[] dArray;
        size = 0;
    }
    void clear(bool isPointer) {
        if (isPointer == true) {
            if (size > 0) {
                for (int i = 0; i < size; i++) {
                    delete dArray[i];
                }
            }
        }

        delete[] dArray;
        size = 0;
    }

    void bubbleSort(int(*data_cmp)(T,T)) {
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

    std::string to_string(std::string(*data_to_str)(T)) {
        std::ostringstream os;
        try {
            if (size != 0) {
                for(int i = 0; i < size; i++){
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



int main() {
    dynamic_array<std::string> da;

    da.add("Adam");
    da.add("Piter");
    da.add("Wawrzyn");
    da.add("Król");
    da.add("Wroobelek");
    da.add("AAA");

    std::cout << da.to_string(just_str) << std::endl;
    da.bubbleSort();
    std::cout << da.to_string(just_str) << std::endl;

    std::cout << da.getSize() << std::endl;
    std::cout << da.getCapacity() << std::endl;
    
    da.clear();


    dynamic_array<Person*> daPerson;
    daPerson.add(new Person("12345678910", "Adam", "Adamiak", 2001));
    daPerson.add(new Person("12434737744", "Szymon", "Adamiak", 1976));
    daPerson.add(new Person("03747383333", "Kazimierz", "Adamiak", 1953));
    daPerson.add(new Person("27348489933", "Karol", "Adamiak", 1998));
    daPerson.add(new Person("57282929292", "Wiktor", "Adamiak", 2016));
    daPerson.add(new Person("00274878389", "Jan", "Adamiak", 2000));

    std::cout << daPerson.to_string(person_to_str) << std::endl;
    daPerson.bubbleSort(person_cmp);
    std::cout << daPerson.to_string(person_to_str) << std::endl;
    daPerson.change(2, new Person("19327373739", "Krzysztof", "Marian", 1944), true);
    std::cout << daPerson.to_string(person_to_str) << std::endl;


    std::cout << daPerson.getSize() << std::endl;
    std::cout << daPerson.getCapacity() << std::endl;

    daPerson.clear(true);


    return 0;
}