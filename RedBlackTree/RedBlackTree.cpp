#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <math.h> 

static int counter = 0;

void resetCounter() {
    counter = 0;
}
int setIndeks() {
    counter++;
    return (counter - 1);
}

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



/* ==== LISTA ==== */
template<typename T>
class ListNode {
public:
    ListNode<T>* next;
    ListNode<T>* prev;
    T data;

    ListNode() {
        next = NULL;
        prev = NULL;
    }
    ~ListNode() {
        next = NULL;
        prev = NULL;
    }
};
template<typename T>
class List {
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    int size;
public:
    List() {
        head = NULL;
        tail = NULL;
        size = 0;
    }
    void add(T dane) {
        ListNode<T>* new_object = new ListNode<T>;
        new_object->data = dane;
        new_object->next = NULL;
        new_object->prev = NULL;

        if (size == 0) {
            head = new_object;
            tail = new_object;
        }
        else {
            ListNode<T>* temp_object = tail;
            temp_object->next = new_object;
            new_object->prev = temp_object;
            tail = new_object;
        }
        size++;
    }
};


/* ==== DRZEWO BINARNE ==== */
template<typename T>
class Node {
public:
    Node<T>* parent;
    Node<T>* l_node;
    Node<T>* r_node;
    int indeks;
    bool isBlack;
    T data;

    Node() {
        parent = NULL;
        l_node = NULL;
        r_node = NULL;
        indeks = setIndeks();
    }
    ~Node() {
        //data = ~T();
        parent = NULL;
        l_node = NULL;
        r_node = NULL;
        indeks = 0;
    }
};
template<typename T>
class Rbt {
private:
    Node<T>* root;
    int size;
public:
    Rbt() {
        root = NULL;
        size = 0;
    }
    ~Rbt() {
        root = NULL;
        size = 0;
        resetCounter();
    }
    int getSize() {
        return size;
    }
    Node<T>* getRoot() {
        return root;
    }


    void add(T dane, int(*data_cmp)(T, T)) {
        Node<T>* new_object = new Node<T>;
        new_object->data = dane;

        if (size == 0) {
            root = new_object;
            new_object->isBlack = true;
        }
        else {
            Node<T>* temp_object = root;
            bool findNULL = false;

            while (findNULL == false) {
                int cmp = data_cmp(temp_object->data, new_object->data);

                if (cmp == 0 || cmp == -1) {
                    if (temp_object->r_node == NULL) {
                        temp_object->r_node = new_object;
                        new_object->parent = temp_object;

                        findNULL = true;
                        break;
                    }
                    temp_object = temp_object->r_node;
                }
                else {
                    if (temp_object->l_node == NULL) {
                        temp_object->l_node = new_object;
                        new_object->parent = temp_object;

                        findNULL = true;
                        break;
                    }
                    temp_object = temp_object->l_node;
                }
            }
        }
        size++;
    }
    Node<T>* find(T dane, int(*data_cmp)(T, T)) {
        if (size != 0) {
            Node<T>* temp_object = root;

            for (int i = 0; i < size; i++) {
                if (temp_object == NULL) {
                    return NULL;
                }
                int cmp = data_cmp(temp_object->data, dane);

                if (cmp == 0) {
                    return temp_object;
                }
                if (cmp == 1) {
                    temp_object = temp_object->l_node;
                }
                else {
                    temp_object = temp_object->r_node;
                }
            }
            return temp_object;
        }
        return NULL;
    }




    int getHeight() {
        Node<T>* temp_object = root;
        int temp_height = 0;
        int max_height_l = 0, max_height_r = 0;


        if (temp_object->l_node != NULL) {
            max_height_l = height(temp_object->l_node, temp_height, max_height_l);
        }
        if (temp_object->r_node != NULL) {
            max_height_r = height(temp_object->r_node, temp_height, max_height_r);
        }

        return std::max(max_height_l, max_height_r);
    }
    int height(Node<T>* temp_object, int temp_height, int max_height) {
        temp_height++;

        if (temp_height > max_height) {
            max_height = temp_height;
        }

        if (temp_object->l_node != NULL) {
            max_height = height(temp_object->l_node, temp_height, max_height);
        }
        if (temp_object->r_node != NULL) {
            max_height = height(temp_object->r_node, temp_height, max_height);
        }

        return max_height;
    }

    void clear() {
        Node<T>* temp_object = root;
        if (temp_object->l_node != NULL) {
            clear(temp_object->l_node);
        }
        if (temp_object->r_node != NULL) {
            clear(temp_object->r_node);
        }
        delete temp_object;
        size = 0;
        root = NULL;
        resetCounter();
    }
    void clear(bool isIndicator) {
        Node<T>* temp_object = root;
        if (temp_object->l_node != NULL) {
            clear(temp_object->l_node, isIndicator);
        }
        if (temp_object->r_node != NULL) {
            clear(temp_object->r_node, isIndicator);
        }
        if (isIndicator == true) {
            delete temp_object->data;
        }
        delete temp_object;
        size = 0;
        root = NULL;
        resetCounter();
    }
    void clear(Node<T>* temp_object) {
        if (temp_object->l_node != NULL) {
            clear(temp_object->l_node);
        }
        if (temp_object->r_node != NULL) {
            clear(temp_object->r_node);
        }
        if (temp_object->l_node == NULL && temp_object->r_node == NULL) {
            temp_object->~Node();
            delete temp_object;
        }

        size--;
    }
    void clear(Node<T>* temp_object, bool isIndicator) {
        if (temp_object->l_node != NULL) {
            clear(temp_object->l_node);
        }
        if (temp_object->r_node != NULL) {
            clear(temp_object->r_node);
        }
        if (temp_object->l_node == NULL && temp_object->r_node == NULL) {
            if (isIndicator == true) {
                delete temp_object->data;
            }
            temp_object->~Node();
            delete temp_object;
        }

        size--;
    }

    void preOrder(List<T>* list, Node<T>* temp_object) {
        if (temp_object != NULL) {
            list->add(temp_object->data);
            preOrder(list, temp_object->l_node);
            preOrder(list, temp_object->r_node);
        }
        return;
    }
    void inOrder(List<T>* list, Node<T>* temp_object) {
        if (temp_object != NULL) {
            preOrder(list, temp_object->l_node);
            list->add(temp_object->data);
            preOrder(list, temp_object->r_node);
        }
        return;
    }

    std::string to_string(Node<T>* temp_object, std::string(*data_to_str)(T)) {
        std::ostringstream temp;
        try {
            if (size != 0) {
                if (size <= 32) {
                    temp << temp_object->indeks << ":\t[";

                    if (temp_object->isBlack == true) temp << "black\t";
                    else temp << "red\t";

                    temp << "p: ";
                    if (temp_object->parent != NULL) temp << temp_object->parent->indeks << "\t";
                    else temp << "NULL\t";

                    if (temp_object->l_node != NULL) temp << " l: " << temp_object->l_node->indeks << "\t";
                    else temp << " l: NULL";

                    if (temp_object->r_node != NULL) temp << " r: " << temp_object->r_node->indeks << "\t";
                    else temp << " r: NULL";

                    temp << " data: " << data_to_str(temp_object->data) << "]\n";

                    if (temp_object->l_node != NULL) temp << to_string(temp_object->l_node, data_to_str);
                    if (temp_object->r_node != NULL) temp << to_string(temp_object->r_node, data_to_str);

                    return temp.str();
                }
                else {
                    return to_string(temp_object, data_to_str, 4);
                }
            }
            else {
                throw 1;
            }
        }
        catch (...) {
            temp << "Brak rekordow!\n";
        }
        return temp.str();
    }
    std::string to_string(Node<T>* temp_object, std::string(*data_to_str)(T), int depth) {
        std::ostringstream temp;
        try {
            if (size != 0) {
                if (depth != 0) {
                    depth -= 1;
                    temp << temp_object->indeks << ":\t[";

                    if (temp_object->isBlack == true) temp << "black\t";
                    else temp << "red\t";

                    temp << "p: ";
                    if (temp_object->parent != NULL) temp << temp_object->parent->indeks << "\t";
                    else temp << "NULL\t";

                    if (temp_object->l_node != NULL) temp << " l: " << temp_object->l_node->indeks << "\t";
                    else temp << " l: NULL";

                    if (temp_object->r_node != NULL) temp << " r: " << temp_object->r_node->indeks << "\t";
                    else temp << " r: NULL";

                    temp << " data: " << data_to_str(temp_object->data) << "]\n";

                    if (temp_object->l_node != NULL) temp << to_string(temp_object->l_node, data_to_str, depth);
                    if (temp_object->r_node != NULL) temp << to_string(temp_object->r_node, data_to_str, depth);

                    return temp.str();
                }
            }
            else {
                throw 1;
            }
        }
        catch (...) {
            temp << "Brak rekordow!\n";
        }
        return temp.str();
    }
};

int main()
{
    Rbt<int>* rbt1 = new Rbt<int>();
    
    rbt1->add(50, normal_cmp);
    rbt1->add(70, normal_cmp);
    rbt1->add(45, normal_cmp);
    rbt1->add(10, normal_cmp);
    rbt1->add(40, normal_cmp);
    rbt1->add(60, normal_cmp);
    rbt1->add(75, normal_cmp);
    rbt1->add(38, normal_cmp);
    rbt1->add(45, normal_cmp);
    rbt1->add(43, normal_cmp);

    std::cout << rbt1->getSize() << std::endl;
    std::cout << rbt1->find(23, normal_cmp) << std::endl;
    std::cout << std::to_string(rbt1->getHeight()) << std::endl;

    std::cout << "FIND:" << rbt1->find(199, normal_cmp) << std::endl;

    std::cout << rbt1->to_string(rbt1->getRoot(), not_str) << std::endl;


    rbt1->clear();
    delete rbt1;
    return 0;
}