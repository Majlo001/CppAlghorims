#include <iostream>
#include <string>
#include <time.h>
#include <sstream>

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
    return p.imie + " " + p.nazwisko + " " + std::to_string(p.pesel) + " " + std::to_string(p.rok_urodzenia);
}
std::string person_to_str(Person* p) {
    return p->imie + " " + p->nazwisko + " " + std::to_string(p->pesel) + " " + std::to_string(p->rok_urodzenia);
}


template<typename T>
std::string not_str(T str) {
    return std::to_string(str);
}
std::string just_str(std::string str) {
    return str;
}

template<typename T>
class Node {
public:
    Node<T>* parent;
    Node<T>* l_node;
    Node<T>* r_node;
    T data;

    Node() {
        parent = nullptr;
        l_node = nullptr;
        r_node = nullptr;
    }
    ~Node() {
        parent = nullptr;
        l_node = nullptr;
        r_node = nullptr;
    }
};

template<typename T>
class bst {
private:
    Node<T>* root;
    int size;
public:
    bst() {
        root = nullptr;
        size = 0;
    }
    void add(T dane) {
        Node<T>* new_object = new Node<T>;

        if (size == 0) {
            new_object->data = dane;
            root = new_object;
        }
        else {
            Node<T>* temp_object = root;
        }
        size++;
    }
};


int main()
{
    bst<int>* bst1 = new bst<int>();

    delete bst1;
    return 0;
}