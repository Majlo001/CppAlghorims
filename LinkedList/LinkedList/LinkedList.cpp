﻿#include <iostream>
#include <string>
#include <time.h>


// ==== TODO:
// (f) ustawienie (podmiana) danych i-tego elementu listy (argumenty: indeks i żądanego elementu
// (numerując od zera) oraz nowe dane; wynik: pusty lub niepowodzenie w razie indeksu poza
// zakresem)

// (i) dodanie nowego elementu z wymuszeniem porządku (argumenty: dane i informacja lub kom-
// parator definiujące klucz porządkowania)

// linked_list<some_object*>* ll = new linked_list<some_object*>();
// 6. clock()
// 7. operator [], opcjonalnie
// 8.


//template<typename T>
class Node {
public:
    //Node<T>* prev;
    //Node<T>* next;
    Node* prev;
    Node* next;
    int number;
    //std::string phrase;

    Node() {
        prev = nullptr;
        next = nullptr;
        number = 0;
    }
};

template<typename T>
class linked_list {
private:
    T* head;
    T* tail;
    int size;
public:
    linked_list() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    void add_first(T dane) {
        T* new_object = (T*)malloc(sizeof(T));

        if (size != 0) {
            T* temp = head;
            temp->prev = head;
        }

        new_object->number = dane.number;
        new_object->next = head;
        head = new_object;
        head->prev = nullptr;
        size++;
    }
    void add_last(T dane) {
        T* new_object = (T*)malloc(sizeof(T));
        new_object->number = dane.number;
        //new_object->phrase = dane.phrase;
        new_object->next = nullptr;
        new_object->prev = nullptr;

        if (size == 0) {
            head = new_object;
            tail = new_object;
        }
        else {
            T* temp_object = head;
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
            T* head_object = head;

            if (size == 1) {
                head = nullptr;
                tail = nullptr;
            }
            else {
                T* temp = head_object->next;
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
            T* tail_object = tail;

            if (size == 1) {
                head = nullptr;
                tail = nullptr;
            }
            else {
                T* temp = tail_object->prev;
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
            T* head_object = head;
            T* temp_object;
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
                std::cout << "Used 1 " << size - 1 << " : " << (size - 1 / 2) << std::endl;
                T* temp_object = head;
                int i = 0;
                
                while (i != index){
                    i++;
                    temp_object = temp_object->next;
                }

                T* next_object = temp_object->next;
                T* prev_object = temp_object->prev;
                prev_object->next = temp_object->next;
                next_object->prev = temp_object->prev;
                
                free(temp_object);
            }
            else {
                T* temp_object = tail;
                int i = size-1;

                while (i != index) {
                    i--;
                    temp_object = temp_object->prev;
                }

                T* next_object = temp_object->next;
                T* prev_object = temp_object->prev;
                prev_object->next = temp_object->next;
                next_object->prev = temp_object->prev;

                free(temp_object);
            }
            size--;
        }
     }
    void print_index(int number) {
        if (number <= size) {
            T* temp_object = head;
            int temp_index = 0;

            for (int i = 0; i <= number; i++) {
                if (temp_index == number) {
                    std::cout << temp_index << " " << temp_object << " " << temp_object->prev << " " << temp_object->next << " " << temp_object->number << std::endl;
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
        T* temp_object = head;
        if (size != 0) {
            std::cout << std::endl << "<==== LISTA ====>" << std::endl;
            for (int i = 0; i < size; i++) {
                std::cout << temp_object << " " << temp_object->prev << " " << temp_object->next << " " << temp_object->number << std::endl;
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
    //linked_list<Node<int>>* l1 = new linked_list<Node<int>>();
    //Node<int> so;

    linked_list<Node>* l1 = new linked_list<Node>();
    Node so1;
    so1.number = 999;
    //so1.phrase = 'work';
    l1->add_first(so1);

    Node so2;
    so2.number = 888;
    l1->add_last(so2);

    Node so3;
    so3.number = 777;
    l1->add_last(so3);

    so3.number = 1111;
    l1->add_first(so3);

    l1->print_index(0);
    l1->print_index(2);
    l1->del_index(2);
    l1->printAll();
    l1->del_index(2);

    l1->printAll();
    l1->del_all();
    l1->printAll();


    delete l1;
    return 0;
}