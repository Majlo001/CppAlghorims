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
    ~dynamic_array() {
        size = 0;
        capacity = 1;
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
        if (size > 0) {
            for (int i = 0; i < size; i++) {
                dArray[i] = nullptr;
            }
        }
        size = 0;
    }
    void clear(bool isPointer) {
        if (isPointer == true) {
            if (size > 0) {
                for (int i = 0; i < size; i++) {
                    delete dArray[i];
                    dArray[i] = nullptr;
                }
            }
        }
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



int main() {
    dynamic_array<Person*>* da = new dynamic_array<Person*>();
    const int order = 7;
    const int n = pow(10, order);

    clock_t t1 = clock();
    double max_time_per_element = 0.0;

    for (int i = 0; i < n; i++) {
        clock_t t1_element = clock();

        int pesel = rand() % 1000000 + 1;
        da->add(new Person(std::to_string(pesel), "Adam", "Adamiak", 1000+i));

        clock_t t2_element = clock();
        double time_per_element = (t2_element - t1_element)/(double)CLOCKS_PER_SEC;
        
        if (time_per_element > max_time_per_element){
            max_time_per_element = time_per_element;

            std::cout << "Nowy najgorszy czas na element: " << max_time_per_element * 1000 << "ms i jego indeks: " << i << std::endl;
        }
    }
    clock_t t2 = clock();
    double time = (t2 - t1) / (double)CLOCKS_PER_SEC;

    std::cout << da->to_string(person_to_str, 10) << std::endl;
    std::cout << "Pomiar czasowy: " << time << "s dla 10^" << order << " elementow." <<  std::endl;
    //Tutaj czas zamortyzowany.


    da->clear(true);
    delete da;
    return 0;
}