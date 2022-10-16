#include <iostream>
#include <string>
#include <time.h>
#include <typeinfo>
#include <sstream>


// ==== TODO:
// (f) ustawienie (podmiana) danych i-tego elementu listy (argumenty: indeks i żądanego elementu
// (numerując od zera) oraz nowe dane; wynik: pusty lub niepowodzenie w razie indeksu poza
// zakresem) DONE

// (g) wyszukanie elementu (argumenty: dane wzorcowe oraz informacja lub komparator definiujące
// klucz wyszukiwania — szczegółowe wskazówki dalej; wynik: wskaźnik na odnaleziony element
// listy lub NULL w przypadku niepowodzenia) HALF DONE

// (h)wyszukanie i usunięcie elementu(argumenty: jak wyżej; wynik: flaga logiczna sygnalizująca
// powodzenie lub niepowodzenie)

// (i) dodanie nowego elementu z wymuszeniem porządku (argumenty: dane i informacja lub kom-
// parator definiujące klucz porządkowania)

// linked_list<some_object>* ll = new linked_list<some_object>();
// 6. clock() DONE
// 8. Operator <= itd. PRAWIE DONE
// 9. to_string() PRAWIE DONE


// Usunięcie wszystkich cout'ów i dodanie returnów
// Try catche


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

    std::ostream& operator<<(std::ostream& os)
    {
        os  << imie << ' ' << nazwisko << ' ' << pesel << ' ' << rok_urodzenia;
        return os;
    }
};

bool operator<=(const Person& a, const Person& b) {
    return a.pesel < b.pesel || a.pesel == b.pesel;
}
bool operator==(const Person& a, const Person& b) {
    return a.pesel == b.pesel;
}


std::string person_to_str(Person p) {
    return p.imie + " " + p.nazwisko + " " + p.pesel + " " + std::to_string(p.rok_urodzenia);
}
std::string person_to_str(Person* p) {
    return p->imie + " " + p->nazwisko + " " + p->pesel + " " + std::to_string(p->rok_urodzenia);
}


// Do poprawy!
template<typename T>
std::string just_str(T just) {
    std::string temp = "";

    if (typeid(just).name() != typeid(temp).name()) {
        
        temp = std::to_string(just);
    }
    else {
        temp = just;
    }
    return temp;
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

    //Poprawione
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
    void del_first() {
        if (size == 0) {
            std::cout << "Brak obiektów w tablicy!" << std::endl;
            return;
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
            delete head_object;
            size--;
        }
    }
    void del_last() {
        if (size == 0) {
            std::cout << "Brak obiektów w tablicy!" << std::endl;
            return;
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
            delete tail_object;
            size--;
        }
    }
    void del_all() {
        if (size == 0) {
            std::cout << "Brak obiektów w tablicy!" << std::endl;
            return;
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
                delete head_object;
                head_object = temp_object;
                size--;
            }
        }
    }
    void del_index(int index) {
        if (size == 0) {
            std::cout << "Brak obiektów w tablicy!" << std::endl;
            return;
        }
        else if (index > size-1) {
            std::cout << "Brak obiektu o podanym indeksie!" << std::endl;
            return;
        }
        else {
            if (size == 1 && index == size-1) {
                del_all();
                return;
            }
            else if (index == 0) {
                del_first();
                return;
            }
            else if (index == size - 1) {
                del_last();
                return;
            }
            else if (index <= ((size - 1) / 2)) {
                Node<T>* temp_object = head;
                int i = 0;
                
                while (i != index){
                    i++;
                    temp_object = temp_object->next;
                }

                Node<T>* next_object = temp_object->next;
                Node<T>* prev_object = temp_object->prev;
                prev_object->next = temp_object->next;
                next_object->prev = temp_object->prev;
                
                delete temp_object;
            }
            else {
                Node<T>* temp_object = tail;
                int i = size-1;

                while (i != index) {
                    i--;
                    temp_object = temp_object->prev;
                }

                Node<T>* next_object = temp_object->next;
                Node<T>* prev_object = temp_object->prev;
                prev_object->next = temp_object->next;
                next_object->prev = temp_object->prev;

                delete temp_object;
            }
            size--;
        }
     }
    void change_index(int index, T dane) {
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
                temp_object->data = dane;
            }
            else {
                throw 1;
            }
        }
        catch (...) {
            std::cout << "Indeks poza wielkoscia!" << std::endl;
        }
    }

    // Tu też do poprawy!
    void print_index(int number) {
        if (number <= size) {
            Node<T>* temp_object = head;
            int temp_index = 0;

            /*if (index <= ((size - 1) / 2)) {
            }*/
            for (int i = 0; i <= number; i++) {
                if (temp_index == number) {
                    std::cout << temp_index << " " << temp_object << " " << temp_object->prev << " " << temp_object->next << " " << temp_object->data << std::endl;
                    return;
                }
                temp_index++;
                temp_object = temp_object->next;
            }
        }
        else {
            std::cout << "Nie ma obiektu z takim indeksem!" << std::endl;
        }
    }
    void printAll() {
        Node<T>* temp_object = head;
        if (size != 0) {
            std::cout << std::endl << "<==== LISTA ====>" << std::endl;
            //std::string dane = person_to_str(temp_object->data);
            for (int i = 0; i < size; i++) {
                std::cout << temp_object << " " << temp_object->prev << " " << temp_object->next << " " << person_to_str(temp_object->data) << std::endl;
                temp_object = temp_object->next;
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Brak rekordów" << std::endl;
        }
    }

    void print_by_key(T dane) {
        Node<T>* temp_object = head;
        if (size != 0) {
            for (int i = 0; i < size; i++) {

                if (temp_object->data <= dane) {
                    std::cout << temp_object << " " << temp_object->prev << " " << temp_object->next << " " << temp_object->data << std::endl;
                    return;
                }
                else {
                    temp_object = temp_object->next;
                }
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Brak rekordów" << std::endl;
        }
    }
    void print_by_key(T dane, bool isIndicator) {
        Node<T>* temp_object = head;
        if (size != 0) {
            for (int i = 0; i < size; i++) {

                if (isIndicator == true) {
                    if (*temp_object->data <= *dane) {
                        std::cout << temp_object << " " << temp_object->prev << " " << temp_object->next << " " << person_to_str(temp_object->data) << std::endl;
                        return;
                    }
                    else {
                        temp_object = temp_object->next;
                    }
                }
                else {
                    if (temp_object->data <= dane) {
                        std::cout << temp_object << " " << temp_object->prev << " " << temp_object->next << " " << person_to_str(temp_object->data) << std::endl;
                        return;
                    }
                    else {
                        temp_object = temp_object->next;
                    }
                }
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Brak rekordów" << std::endl;
        }
    }


    // Do poprawy!
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
            /*else {
                temp << std::to_string(temp_object->data) << "\n";
            }*/
            temp_object = temp_object->next;
        }

        return temp.str();
    }
};

int main()
{
    clock_t t1 = clock();


    linked_list<int>* l1 = new linked_list<int>();
    linked_list<Person*>* l2 = new linked_list<Person*>();
    linked_list<Person>* l3 = new linked_list<Person>();
    linked_list<std::string>* l4 = new linked_list<std::string>();

    Person* osoba = new Person("12345678910", "Adam", "Adamiak", 2001);
    Person* osoba2 = new Person("12345786632", "Jan", "Kowalski", 1998);
    Person* osoba3 = new Person("12345786632", "Nataniel", "Wegier", 1976);
    l2->add_first(osoba);
    l2->add_first(osoba2);
    //l2->print_by_key(osoba3, true);
    //l2->del_first();
    l2->printAll();
    std::cout << "LISTA\n" << l2->to_string(person_to_str) << std::endl;


    //Do poprawy
    //Person adamiak("12345678910", "Adam", "Adamiak", 2000);
    Person adamiak;
    adamiak.pesel = "1234567890";
    adamiak.imie = "Adam";
    adamiak.nazwisko = "Adamiak";
    adamiak.rok_urodzenia = 2000;
    l3->add_first(adamiak);
    //l3->print_by_key(adamiak, false);
    l3->printAll();



    l1->add_first(999);
    l1->add_last(888);
    l1->add_last(777);
    l1->add_first(1111);

    l1->print_index(0);
    l1->print_index(2);
    l1->del_index(2);
    //l1->printAll();
    std::cout << "LISTA\n" << l1->to_string(just_str) << std::endl;
    l1->del_index(2);
    l1->change_index(10, 300);

    //l1->printAll();
    std::cout << "LISTA\n" << l1->to_string(just_str) << std::endl;
    l1->print_by_key(300);
    l1->del_all();
    std::cout << "LISTA\n" << l1->to_string(just_str) << std::endl;
    //l1->printAll();




    l4->add_first("Adam");
    l4->add_last("Szczan");
    l4->add_first("Kruk");
    //std::cout << "LISTA\n" << l4->to_string(just_str) << std::endl;
    //l4->printAll();

    delete l4;
    delete l3;
    delete l2;
    delete l1;

    clock_t t2 = clock();
    double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std::cout << time << std::endl;
    return 0;
}