#include <iostream>
#include <string>
#include <time.h>


// ==== TODO:
// (f) ustawienie (podmiana) danych i-tego elementu listy (argumenty: indeks i żądanego elementu
// (numerując od zera) oraz nowe dane; wynik: pusty lub niepowodzenie w razie indeksu poza
// zakresem)

// (g) wyszukanie elementu (argumenty: dane wzorcowe oraz informacja lub komparator definiujące
// klucz wyszukiwania — szczegółowe wskazówki dalej; wynik: wskaźnik na odnaleziony element
// listy lub NULL w przypadku niepowodzenia)

// (h)wyszukanie i usunięcie elementu(argumenty: jak wyżej; wynik: flaga logiczna sygnalizująca
// powodzenie lub niepowodzenie)

// (i) dodanie nowego elementu z wymuszeniem porządku (argumenty: dane i informacja lub kom-
// parator definiujące klucz porządkowania)

// linked_list<some_object*>* ll = new linked_list<some_object*>();
// 6. clock()
// 7. operator [], opcjonalnie
// 8.


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

    std::ostream& operator<<(std::ostream& os)
    {
        os << '[' << imie << ' ' << nazwisko << ' ' << pesel << ' ' << rok_urodzenia << ']';
        return os;
    }
};


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
        Node<T>* new_object = (Node<T>*)malloc(sizeof(Node<T>));
        
        //temp_head->prev = head;

        if (size == 0) {
            new_object->data = dane;
            head = new_object;
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

    //DO POPRAWY!
    void add_last(T dane) {
        Node<T>* new_object = (Node<T>*)malloc(sizeof(Node<T>));
        new_object->data = dane;
        new_object->next = nullptr;
        new_object->prev = nullptr;

        if (size == 0) {
            head = new_object;
            tail = new_object;
        }
        else {
            Node<T>* temp_object = head;
            for (int i = 0; i < size; i++) {
                if (temp_object->next == nullptr) {
                    temp_object->next = new_object; 
                    new_object->prev = temp_object;
                    tail = new_object;
                }
                temp_object = temp_object->next;
            }
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
            free(head_object);
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
            free(tail_object);
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
                free(head_object);
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
                
                free(temp_object);
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

                free(temp_object);
            }
            size--;
        }
     }
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
            for (int i = 0; i < size; i++) {
                std::cout << temp_object << " " << temp_object->prev << " " << temp_object->next << " " << temp_object->data << std::endl;
                temp_object = temp_object->next;
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Brak rekordów" << std::endl;
        }
    }
};

int main()
{
    clock_t t1 = clock();


    linked_list<int>* l1 = new linked_list<int>();
    linked_list<Person*>* l2 = new linked_list<Person*>();

    Person* osoba = new Person("12345678910", "Adam", "Adamiak", 2001);
    Person* osoba2 = new Person("12345786632", "Jan", "Kowalski", 1998);
    l2->add_first(osoba);
    l2->add_first(osoba2);
    //l2->del_first();

    delete osoba;
    delete osoba2;
    l2->printAll();


    l1->add_first(999);
    l1->add_last(888);
    l1->add_last(777);
    l1->add_first(1111);

    l1->print_index(0);
    l1->print_index(2);
    l1->del_index(2);
    l1->printAll();
    l1->del_index(2);

    l1->printAll();
    l1->del_all();
    l1->printAll();



    delete l2;
    delete l1;



    clock_t t2 = clock();
    double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
    std::cout << time << std::endl;
    return 0;
}