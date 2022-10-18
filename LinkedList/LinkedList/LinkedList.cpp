#include <iostream>
#include <string>
#include <time.h>
#include <typeinfo>
#include <sstream>


// ==== TODO:

// Try catche
// dodać zakomentowany przykładowy kod


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
        os  << imie << ' ' << nazwisko << ' ' << pesel << ' ' << rok_urodzenia;
        return os;
    }

    bool operator == (const Person& p) {
        return p.pesel == pesel;
    }
    bool operator == (const Person*& p) {
        return p->pesel == pesel;
    }
    bool operator <= (const Person& p) {
        return p.pesel < pesel || p.pesel == pesel;
    }
    bool operator <= (const Person*& p) {
        return p->pesel < pesel || p->pesel == pesel;
    }
};

int person_is_equal() {
    return 0;
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
class Node {
public:
    Node<T>* prev;
    Node<T>* next;
    T data;

    Node() {
        prev = nullptr;
        next = nullptr;
    }
    ~Node() {
        prev = nullptr;
        next = nullptr;
    }
};

template<typename T>
class linked_list {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
    linked_list() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    void add_first(T dane) {
        Node<T>* new_object = new Node<T>;

        if (size == 0) {
            new_object->data = dane;
            head = new_object;
            tail = new_object;
            new_object->next = nullptr;
            new_object->prev = nullptr;
        }
        else {
            Node<T>* temp_head = head;
            head->prev = new_object;
            new_object->data = dane;
            new_object->next = temp_head;
            new_object->prev = nullptr;
            head = new_object;
        }
        size++;
    }
    void add_last(T dane) {
        Node<T>* new_object = new Node<T>;
        new_object->data = dane;
        new_object->next = nullptr;
        new_object->prev = nullptr;

        if (size == 0) {
            head = new_object;
            tail = new_object;
        }
        else {
            Node<T>* temp_object = tail;
            temp_object->next = new_object; 
            new_object->prev = temp_object;
            tail = new_object;
        }
        size++;
    }

    // Nie działa dla typów wskaźnikowych
    void add_order(T dane) {
        Node<T>* temp_object = head;


        if (size != 0) {
            for (int i = 0; i < size; i++) {
                if (dane <= temp_object->data) {
                    if (i == 0) {
                        add_first(dane);
                        return;
                    }
                    Node<T>* new_object = new Node<T>;

                    new_object->data = dane;
                    new_object->next = temp_object;
                    new_object->prev = temp_object->prev;
                    temp_object->prev->next = new_object;
                    temp_object->prev = new_object;
                    return;
                }
                temp_object = temp_object->next;
            }
            add_last(dane);
            return;
        }
        else {
            add_first(dane);
            return;
        }
        size++;
    }
    bool del_first(bool isIndicator) {
        if (size == 0) {
            return 0;
        }
        else {
            Node<T>* head_object = head;

            if (size == 1) {
                head = nullptr;
                tail = nullptr;
            }
            else {
                Node<T>* temp = head_object->next;
                head = temp;
                temp->prev = nullptr;
            }
            head_object->next = nullptr;
            head_object->prev = nullptr;

            //'delete': cannot delete objects that are not pointers
            /*if (isIndicator == true) {
                delete head_object->data;
            }*/
            delete head_object;
            size--;
            return 1;
        }
    }
    bool del_last(bool isIndicator) {
        if (size == 0) {
            return 0;
        }
        else{
            Node<T>* tail_object = tail;

            if (size == 1) {
                head = nullptr;
                tail = nullptr;
            }
            else {
                Node<T>* temp = tail_object->prev;
                tail = temp;
                temp->next = nullptr;
            }
            tail_object->next = nullptr;
            tail_object->prev = nullptr;

            //'delete': cannot delete objects that are not pointers
            /*if (isIndicator == true) {
                delete tail_object->data;
            }*/
            delete tail_object;
            size--;
            return 1;
        }
    }
    bool del_all(bool isIndicator) {
        if (size == 0) {
            return 0 ;
        }
        else {
            Node<T>* head_object = head;
            Node<T>* temp_object;
            head = nullptr;
            tail = nullptr;

            while (size > 0) {
                temp_object = head_object->next;

                head_object->next = nullptr;
                head_object->prev = nullptr;
                /*if (isIndicator == true) {
                    delete head_object->data;
                }*/
                delete head_object;
                head_object = temp_object;
                size--;
            }
        }
        return 1;
    }
    bool del_index(int index, bool isIndicator) {
        if (size == 0 || index > size - 1) {
            return false;
        }
        else {
            Node<T>* temp_object;

            if (size == 1 && index == size-1) {
                return del_all(isIndicator);
            }
            else if (index == 0) {
                return del_first(isIndicator);
            }
            else if (index == size - 1) {
                return del_last(isIndicator);
            }
            else if (index <= ((size - 1) / 2)) {
                temp_object = head;
                int i = 0;
                
                while (i != index){
                    i++;
                    temp_object = temp_object->next;
                }
            }
            else {
                temp_object = tail;
                int i = size-1;

                while (i != index) {
                    i--;
                    temp_object = temp_object->prev;
                }
            }

            Node<T>* next_object = temp_object->next;
            Node<T>* prev_object = temp_object->prev;
            prev_object->next = temp_object->next;
            next_object->prev = temp_object->prev;

            /*if (isIndicator == true) {
                delete head_object->data;
            }*/
            delete temp_object;
            size--;
            return true;
        }
     }

    // Nie działa dla typów wskaźnikowych
    bool del_by_key(T dane, bool isIndicator) {
        Node<T>* temp_object = head;
        if (size != 0) {
            for (int i = 0; i < size; i++) {
                if (temp_object->data == dane) {
                    delete temp_object;
                    /*if (isIndicator == true) {
                        delete head_object->data;
                    }*/
                    return true;
                }
                temp_object = temp_object->next;
            }
        }
        return false;
    }

    // Nie działa dla typów wskaźnikowych
    std::string change_index(int index, T dane, bool isIndicator) {
        try {
            if (index <= size) {
                Node<T>* temp_object = head;
                int temp_index = 0;

                if (index <= ((size - 1) / 2)) {
                    while (temp_index != index) {
                        temp_index++;
                        temp_object = temp_object->next;
                    }
                }
                else {
                    temp_index = size - 1;
                    while (temp_index != index) {
                        temp_index--;
                        temp_object = temp_object->prev;
                    }
                }
                /*if (isIndicator == true) {
                    delete temp_object->data;
                }*/
                temp_object->data = dane;
                return "";
            }
            else {
                throw 1;
            }
        }
        catch (...) {
            return "Indeks poza wielkoscia!";
        }
    }

    // Nie działa dla typów wskaźnikowych
    std::string change_by_key(T pattern_data, T dane, bool isIndicator) {
        try {
            Node<T>* temp_object = head;
            if (size != 0) {
                for (int i = 0; i < size; i++) {
                    if (temp_object->data == pattern_data) {
                        /*if (isIndicator == true) {
                            delete temp_object->data;
                        }*/
                        temp_object->data = dane;
                        return "";
                    }
                    temp_object = temp_object->next;
                }
            }
            else {
                throw 1;
            }
        }
        catch (...) {
            return "Nie znaleziono takiego klucza!";
        }
    }

    std::string print_index(int index, std::string(*data_to_str)(T)) {
        std::ostringstream temp;
        if (index <= size) {
            Node<T>* temp_object = head;
            int temp_index = 0;

            if (index <= ((size - 1) / 2)) {
                for (int i = 0; i <= index; i++) {
                    if (temp_index == index) {
                        temp << temp_object << " ";
                        temp << temp_object->prev << " ";
                        temp << temp_object->next << " ";
                        if (data_to_str) {
                            temp << data_to_str(temp_object->data) << "\n";
                        }
                        return;
                    }
                    temp_index++;
                    temp_object = temp_object->next;
                }
            }
            else {
                temp_object = tail;
                temp_index = size - 1;
                while (temp_index != index) {
                    temp_index--;
                    temp_object = temp_object->prev;
                }
                if (temp_index == index) {
                    temp << temp_object << " ";
                    temp << temp_object->prev << " ";
                    temp << temp_object->next << " ";
                    if (data_to_str) {
                        temp << data_to_str(temp_object->data) << "\n";
                    }
                    return;
                }
            }
        }
        else {
            temp << "Nie ma obiektu z takim indeksem!\n";
        }

        return temp.str();
    }

    // Nie działa dla typów wskaźnikowych
    Node<T>* find_by_key(T dane) {
        Node<T>* temp_object = head;
        if (size != 0) {
            for (int i = 0; i < size; i++) {
                if (temp_object->data == dane) {
                    //std::cout << "Działa" << std::endl;
                    return temp_object;
                }
                temp_object = temp_object->next;
            }
        }
        return NULL;
    }


    std::string to_string(std::string(*data_to_str)(T)) {
        std::ostringstream temp;
        Node<T>* temp_object = head;

        while (temp_object) {
            temp << temp_object << " ";
            temp << temp_object->prev << " ";
            temp << temp_object->next << " ";
            if (data_to_str) {
                temp << data_to_str(temp_object->data) << "\n";
            }
            temp_object = temp_object->next;
        }

        return temp.str();
    }
};

// MAIN OLD
//int main()
//{
//    clock_t t1 = clock();
//
//
//    linked_list<int>* l1 = new linked_list<int>();
//    linked_list<Person*>* l2 = new linked_list<Person*>();
//    linked_list<Person>* l3 = new linked_list<Person>();
//    linked_list<std::string>* l4 = new linked_list<std::string>();
//
//    Person* osoba = new Person("12345678910", "Adam", "Adamiak", 2001);
//    Person* osoba2 = new Person("12345786632", "Jan", "Kowalski", 1998);
//    Person* osoba3 = new Person("12345786632", "Nataniel", "Wegier", 1976);
//    l2->add_first(osoba);
//    l2->add_first(osoba2);
//    l2->find_by_key(osoba3);
//    std::cout << "FIND: " << (bool)l2->find_by_key(osoba3) << std::endl;
//    l2->del_by_key(osoba3);
//    delete osoba3;
//    std::cout << "LISTA\n" << l2->to_string(person_to_str) << std::endl;
//    l2->del_first(true);
//
//
//    Person adamiak;
//    adamiak.pesel = "1234567890";
//    adamiak.imie = "Adam";
//    adamiak.nazwisko = "Adamiak";
//    adamiak.rok_urodzenia = 2000;
//
//
//    Person adamiak2;
//    adamiak2.pesel = "1234567890";
//    adamiak2.imie = "Piotr";
//    adamiak2.nazwisko = "Adamiak";
//    adamiak2.rok_urodzenia = 2016;
//
//    l3->add_first(adamiak);
//    std::cout << "\nLISTA\n" << l3->to_string(person_to_str) << std::endl;
//    l3->find_by_key(adamiak2);
//    std::cout << l3->change_by_key(adamiak, adamiak2, false) << std::endl;
//    std::cout << "\nLISTA\n" << l3->to_string(person_to_str) << std::endl;
//
//
//
//    /*l1->add_first(763);
//    l1->add_first(873);
//    l1->add_first(545);*/
//    l1->add_order(999);
//    l1->add_order(888);
//    l1->add_order(777);
//    l1->add_order(885);
//    l1->add_order(1111);
//    std::cout << "LISTA ORDER\n" << l1->to_string(not_str) << std::endl;
//
//    l1->print_index(0);
//    l1->print_index(2);
//    l1->del_index(2, false);
//    std::cout << "LISTA\n" << l1->to_string(not_str) << std::endl;
//    l1->del_index(2, false);
//    std::cout << l1->change_index(10, 300, false) << std::endl;
//
//    std::cout << "LISTA\n" << l1->to_string(not_str) << std::endl;
//    l1->find_by_key(999);
//    l1->del_all(false);
//    std::cout << "LISTA\n" << l1->to_string(not_str) << std::endl;
//
//
//
//
//    l4->add_first("Adam");
//    l4->add_last("Szczaw");
//    l4->add_first("Kruk");
//    l4->find_by_key("Szczaw");
//    std::cout << "LISTA\n" << l4->to_string(just_str) << std::endl;
//
//    delete l4;
//    delete l3;
//    delete l2;
//    delete l1;
//
//    clock_t t2 = clock();
//    double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
//    std::cout << time << std::endl;
//    return 0;
//}

// MAIN NEW
int main() {
    const int MAX_ORDER = 4;
    linked_list<Person>* l1 = new linked_list<Person>();
    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = pow(10, o);


        std::cout << "\nPomiar: " << o << " rozmiar danych: " << n << std::endl << std::endl;

        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            long int pesel = 12345678900+i;
            Person osoba(std::to_string(pesel), "Adam", "Adamiak", 1900+i);
            l1->add_first(osoba);
        }
        clock_t t2 = clock();
        //std::cout << "LISTA L1:\n" << l1->to_string(person_to_str) << std::endl;

        double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
        std::cout << "Pomiar czasowy 1: " << time << "s" << std::endl;



        const int m = pow(10, o);
        t1 = clock();
        for (int i = 0; i < m; i++) {
            long int pesel = 12345678900 + i;
            
            Person osoba2(std::to_string(pesel), "Adam", "Adamiak", 1900 + i);
            l1->find_by_key(osoba2);
            //delete osoba2;
        }
        t2 = clock();
        //std::cout << "LISTA L1:\n" << l1->to_string(person_to_str) << std::endl;

        time = (t2 - t1) / (double)CLOCKS_PER_SEC;
        std::cout << "Pomiar czasowy 2: " << time << "s" << std::endl;

        l1->del_all(true);
    }


    delete l1;
    return 0;
}