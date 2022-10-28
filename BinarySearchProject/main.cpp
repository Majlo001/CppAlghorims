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
        parent = NULL;
        l_node = NULL;
        r_node = NULL;
    }
    ~Node() {
        parent = NULL;
        l_node = NULL;
        r_node = NULL;
    }
};

template<typename T>
class bst {
private:
    Node<T>* root;
    int size;
public:
    bst() {
        root = NULL;
        size = 0;
    }
    int getSize() {
        return size;
    }
    int getRoot() {
        return root;
    }

    // Potem zrobić porównywanie dla wskaźnika na funkcję.
    void add(T dane) {
        Node<T>* new_object = new Node<T>;
        new_object->data = dane;

        if (size == 0) {
            root = new_object;
        }
        else {
            Node<T>* temp_object = root;
            bool findNULL = false;

            while (findNULL == false) {
                if (temp_object->data <= new_object->data) {
                    if (temp_object->l_node == NULL) {
                        temp_object->l_node = new_object;
                        new_object->parent = temp_object;

                        findNULL = true;
                        break;
                    }
                    temp_object = temp_object->l_node;
                }
                else {
                    if (temp_object->r_node == NULL) {
                        temp_object->r_node = new_object;
                        new_object->parent = temp_object;

                        findNULL = true;
                        break;
                    }
                    temp_object = temp_object->r_node;
                }
            }
        }
        size++;
    }

    Node<T>* find(T dane) {
        if (size != 0) {
            Node<T>* temp_object = root;
            bool findNULL = false;

            while (findNULL == false) {
                if (temp_object->data == dane) {
                    findNULL = true;
                    break;
                }

                if (temp_object->data < dane) {
                    temp_object = temp_object->l_node;
                }
                else {
                    temp_object = temp_object->r_node;
                }
            }
            return temp_object;
        }
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


        if (max_height_l > max_height_r) {
            return max_height_l;
        }
        return max_height_r;
    }
    int height(Node<T>* temp_object, int temp_height, int max_height) {
        if (temp_height > max_height) {
            max_height = temp_height;
        }

        temp_height++;
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
        clear(temp_object);
        size--;
        root = NULL;
    }
    void clear(Node<T>* temp_object) {
        if (temp_object->l_node != NULL) {
            clear(temp_object->l_node);
        }
        if (temp_object->r_node != NULL) {
            clear(temp_object->r_node);
        }
        if (temp_object->l_node == NULL && temp_object->r_node == NULL) {

        }

        size--;
    }

    //Zmienić potem na jedną funkcję
    //std::string pre_order(std::string(*data_to_str)(T)) {
    std::string pre_order() {
        std::ostringstream temp;
        try {
            Node<T>* temp_object = root;

            if (size != 0) {
                //int temp_size = 1;

                /*if (data_to_str) {
                    temp << data_to_str(temp_object->data) << "\n";
                }*/

                temp << temp_object->data << ":\t[p: NULL l: ";
                if (temp_object->l_node != NULL) {
                    temp << temp_object->l_node->data;
                }
                else {
                    temp << " NULL";
                }

                if (temp_object->r_node != NULL) {
                    temp << " r: " << temp_object->r_node->data << "]\n";
                }
                else {
                    temp << " r: NULL]\n";
                }


                if (temp_object->l_node != NULL) {
                    temp << pre_order(temp_object->l_node);
                }
                if (temp_object->r_node != NULL) {
                    temp << pre_order(temp_object->r_node);
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
    std::string pre_order(Node<T>* temp_object) {
        std::ostringstream temp;

        temp << temp_object->data << ":\t[p: ";
        temp << temp_object->parent->data << " l: ";
        if (temp_object->l_node != NULL) {
            temp << temp_object->l_node->data;
        }
        else {
            temp << " NULL";
        }
        if (temp_object->r_node != NULL) {
            temp << " r: " << temp_object->r_node->data << "]\n";
        }
        else {
            temp << " r: NULL]\n";
        }

        if (temp_object->l_node != NULL) {
            temp << pre_order(temp_object->l_node);
        }
        if (temp_object->r_node != NULL) {
            temp << pre_order(temp_object->r_node);
        }
        return temp.str();
    }
};


int main()
{
    bst<int>* bst1 = new bst<int>();
    bst1->add(13);
    bst1->add(53);
    bst1->add(33);
    bst1->add(23);
    bst1->add(9);

    std::cout << bst1->getSize() << std::endl;
    std::cout << bst1->find(23) << std::endl;
    std::cout << bst1->pre_order() << std::endl;
    std::cout << std::to_string(bst1->getHeight()) << std::endl;


    delete bst1;
    return 0;
}