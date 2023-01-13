#pragma once


template<typename T>
class ListNode {
public:
    ListNode<T>* next;
    ListNode<T>* prev;
    T value;

    ListNode() {
        next = NULL;
        prev = NULL;
    }
    ~ListNode() {
        next = NULL;
        prev = NULL;
        value = NULL;
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
    ~List() {
        head = NULL;
        tail = NULL;
        size = 0;
    }
    int getSize() {
        return size;
    }
    ListNode<T>* getHead() {
        return head;
    }

    void add(T value) {
        ListNode<T>* new_object = new ListNode<T>;
        new_object->value = value;

        if (size == 0) {
            head = new_object;
            tail = new_object;
            new_object->next = nullptr;
            new_object->prev = nullptr;
        }
        else {
            ListNode<T>* temp_object = tail;
            temp_object->next = new_object;
            new_object->prev = temp_object;
            tail = new_object;
        }
        size++;
    }
    void add_first(T value) {
        ListNode<T>* new_object = new ListNode<T>;
        new_object->value = value;

        if (size == 0) {
            head = new_object;
            tail = new_object;
            new_object->next = nullptr;
            new_object->prev = nullptr;
        }
        else {
            ListNode<T>* temp_head = head;
            head->prev = new_object;
            new_object->next = temp_head;
            new_object->prev = nullptr;
            head = new_object;
        }
        size++;
    }
    void add_order(T value) {
        ListNode<T>* temp_object = head;

        if (size != 0) {
            for (int i = 0; i < size; i++) {
                if (temp_object->value > value) {
                    if (i == 0) {
                        add_first(value);
                        return;
                    }
                    ListNode<T>* new_object = new ListNode<T>;

                    new_object->value = value;
                    new_object->next = temp_object;
                    new_object->prev = temp_object->prev;
                    temp_object->prev->next = new_object;
                    temp_object->prev = new_object;
                    size++;
                    return;
                }
                temp_object = temp_object->next;
            }
            add(value);
            return;
        }
        else {
            add(value);
            return;
        }
        size++;
    }
    void add_order(T value, int (*data_cmp)(T, T)) {
        ListNode<T>* temp_object = head;

        if (size != 0) {
            for (int i = 0; i < size; i++) {
                int cmp = data_cmp(value, temp_object->value);
                if (cmp == -1 || cmp == 0) {
                    if (i == 0) {
                        add_first(value);
                        return;
                    }
                    ListNode<T>* new_object = new ListNode<T>;

                    new_object->value = value;
                    new_object->next = temp_object;
                    new_object->prev = temp_object->prev;
                    temp_object->prev->next = new_object;
                    temp_object->prev = new_object;
                    size++;
                    return;
                }
                temp_object = temp_object->next;
            }
            add(value);
            return;
        }
        else {
            add(value);
            return;
        }
        size++;
    }
    void overwrite(std::string key, T value) {
        ListNode<T>* temp_object = head;
        if (size != 0) {
            for (int i = 0; i < size; i++) {
                if (temp_object->key == key) {
                    temp_object->value = value;
                    return;
                }
                temp_object = temp_object->next;
            }
        }
        return;
    }

    ListNode<T>* get(std::string key) {
        ListNode<T>* temp_object = head;
        if (size != 0) {
            for (int i = 0; i < size; i++) {
                if (key == temp_object->key) {
                    return temp_object;
                }
                temp_object = temp_object->next;
            }
        }
        return NULL;
    }
    bool isEmpty() {
        if (head == NULL && tail == NULL) {
            return 1;
        }
        return 0;
    }


    ListNode<T>* getRehash() {
        ListNode<T>* temp_object = tail;
        tail = temp_object->prev;
        return temp_object;
    }

    bool del_first(bool isIndicator) {
        if (size == 0) {
            return 0;
        }
        else {
            ListNode<T>* head_object = head;

            if (size == 1) {

                if (isIndicator == true) {
                    delete head_object->data;
                }
                delete head_object;

                head = nullptr;
                tail = nullptr;
                size--;
                return 1;
            }
            else {
                ListNode<T>* temp = head_object->next;
                head = temp;
                temp->prev = nullptr;
            }
            head_object->next = nullptr;
            head_object->prev = nullptr;

            if (isIndicator == true) {
                delete head_object->value;
            }
            delete head_object;
            size--;
            return 1;
        }
    }
    bool del_first() {
        if (size == 0) {
            return 0;
        }
        else {
            ListNode<T>* head_object = head;

            if (size == 1) {
                delete head_object;

                head = nullptr;
                tail = nullptr;
                size--;
                return 1;
            }
            else {
                ListNode<T>* temp = head_object->next;
                head = temp;
                temp->prev = nullptr;
            }
            head_object->next = nullptr;
            head_object->prev = nullptr;

            delete head_object;
            size--;
            return 1;
        }
    }
    bool del_last(bool isIndicator) {
        if (size == 0) {
            return 0;
        }
        else {
            ListNode<T>* tail_object = tail;

            if (size == 1) {
                head = nullptr;
                tail = nullptr;
            }
            else {
                ListNode<T>* temp = tail_object->prev;
                tail = temp;
                temp->next = nullptr;
            }
            tail_object->next = nullptr;
            tail_object->prev = nullptr;

            if (isIndicator == true) {
                delete tail_object->value;
            }
            delete tail_object;
            size--;
            return 1;
        }
    }
    bool del_last() {
        if (size == 0) {
            return 0;
        }
        else {
            ListNode<T>* tail_object = tail;

            if (size == 1) {
                head = nullptr;
                tail = nullptr;
            }
            else {
                ListNode<T>* temp = tail_object->prev;
                tail = temp;
                temp->next = nullptr;
            }
            tail_object->next = nullptr;
            tail_object->prev = nullptr;

            delete tail_object;
            size--;
            return 1;
        }
    }
    bool del_all(bool isIndicator) {
        if (size == 0) {
            return 0;
        }
        else {
            ListNode<T>* head_object = head;
            ListNode<T>* temp_object;
            head = nullptr;
            tail = nullptr;

            while (size > 0) {
                temp_object = head_object->next;

                head_object->next = nullptr;
                head_object->prev = nullptr;
                if (isIndicator == true) {
                    delete head_object->value;
                }
                delete head_object;
                head_object = temp_object;
                size--;
            }
        }
        return 1;
    }
    bool del_all() {
        if (size == 0) {
            return 0;
        }
        else {
            ListNode<T>* head_object = head;
            ListNode<T>* temp_object;
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
        return 1;
    }

    bool remove(std::string key) {
        ListNode<T>* temp_object = head;
        if (size != 0) {
            for (int i = 0; i < size; i++) {
                if (temp_object->key == key) {
                    if (i == 0 && i == size - 1) {
                        return del_all();
                    }
                    else if (i == 0) {
                        return del_first();
                    }
                    else if (i == size - 1) {
                        return del_last();
                    }
                    else {
                        delete temp_object;
                        size--;
                        return true;
                    }
                }
                temp_object = temp_object->next;
            }
        }
        return false;
    }
    bool remove(std::string key, bool isIndicator) {
        ListNode<T>* temp_object = head;
        if (size != 0) {
            for (int i = 0; i < size; i++) {
                if (temp_object->key == key) {
                    if (i == 0 && i == size - 1) {
                        return del_all(isIndicator);
                    }
                    else if (i == 0) {
                        return del_first(isIndicator);
                    }
                    else if (i == size - 1) {
                        return del_last(isIndicator);
                    }
                    else {
                        delete temp_object;
                        size--;
                        return true;
                    }
                }
                temp_object = temp_object->next;
            }
        }
        return false;
    }

    std::string to_string() {
        std::ostringstream temp;
        try {
            ListNode<T>* temp_object = head;

            if (size != 0) {
                while (temp_object) {
                    temp << std::to_string(temp_object->value) + ", ";
                    temp_object = temp_object->next;
                }
            }
            else {
                throw 1;
            }
        }
        catch (...) {
            temp << "Brak rekordow!";
        }
        return temp.str();
    }
    std::string to_string(std::string(*data_to_str)(T)) {
        std::ostringstream temp;
        try {
            ListNode<T>* temp_object = head;

            if (size != 0) {
                if (data_to_str) {
                    while (temp_object) {
                        temp << data_to_str(temp_object->value) << ", ";
                        temp_object = temp_object->next;
                    }
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