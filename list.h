#include <iostream>
#include <vector>
using namespace std;
struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }

};


class List {
public:
    Node* begin;
    Node* last;

public:
// Конструктор копирования
List(const List& other) {
    begin = nullptr;
    last = nullptr;
    if (other.begin != nullptr) {
        Node* temp = other.begin;
        do {
            appendToBegin(temp->data); // Копируем данные узлов
            temp = temp->next;
        } while (temp != other.begin);
    }
}

// Оператор присваивания
List& operator=(const List& other) {
    if (this == &other) return *this; // Проверка на самоприсваивание

    free(); // Очистка текущего списка
    if (other.begin != nullptr) {
        Node* temp = other.begin;
        do {
            appendToBegin(temp->data); // Копируем данные узлов
            temp = temp->next;
        } while (temp != other.begin);
    }
    return *this;
}

    List() {
        begin = nullptr;
        last = nullptr;
    }


    void appendToBegin(int value) {
        Node* newNode = new Node(value);
        Node* prev = nullptr;
        if (begin == nullptr) {
            begin = newNode;
            last = begin;
            begin->next = newNode;
        }
        else {
            Node* temp = begin;
            while (temp->next != begin) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = begin;
            begin = newNode;
        }
    }



    void deleteValue(int value) {
        if (begin == nullptr) {
            return;  
        }
        Node* temp = begin;
        while ( begin->data == value) {
            if (begin->next == begin) {
                delete begin;
                last = begin = nullptr;
                return;
            }
            begin = begin->next;
            last->next = begin;
            delete temp;
            temp = begin;

        }
        Node* temp2 = begin->next;
        Node* prev = begin;
        while (temp2 != begin) {
            if (temp2->data == value) {
                if (temp2 == last) {
                    prev->next = begin;
                    delete temp2;
                    last = prev;
                    temp2 = begin;
                }else {
                    prev->next = temp2->next;
                    delete temp2;
                    temp2 = prev->next;
                }
            }else {
                prev = temp2;
                temp2 = temp2->next;
            }
        } 
    }





    void print() {
        if (begin == nullptr) {
            cout << "Список пуст";
        }
        Node* temp = begin;
        do {
            cout << temp->data << " ";
            temp = temp->next;

        } while (temp != begin);

    }


    void deleteAfter(int value) {
        if (!begin || begin->next == begin) return; // Список пуст или состоит из одного элемента

        Node* curr = begin;

        do {
            if (curr->data == value) {
                // Если следующий элемент не является началом списка
                if (curr->next != begin) {
                    Node* temp = curr->next; // Указатель на узел, который нужно удалить
                    curr->next = temp->next; // Обходим удаляемый узел

                    // Если удаляем последний элемент, обновляем указатель на конец
                    if (temp == last) {
                        last = curr;
                    }

                    delete temp;
                }
                // Если последний элемент содержит значение и нужно удалить первый
                else if (curr == last) {
                    Node* temp = begin;
                    begin = begin->next;
                    last->next = begin;
                    delete temp;
                }
            }
            curr = curr->next;
        } while (curr != begin);
    }



    vector<int> search(int value) {
        vector<int> pos;
        int position = 1;
        if (begin == nullptr) {
            cout << "Список пуст";
        }
        Node* temp = begin;
        do {
            if (temp->data == value) {
                pos.push_back(position);
            }
            position++;
            temp = temp->next;
        } while (temp != begin);
        if (pos.empty()) {
            return vector<int> (0);
        }
        else {
            return pos;
        }
    }
    int size(){
        if (begin == nullptr){
            return 0;
        }
        int cnt = 0;
        Node* temp = begin;
        do{
            cnt++;
            temp = temp->next;
        }while (temp!=begin);
        return cnt;
        
    }

    bool contains(int value) {
        if (begin == nullptr) {
            return false;
        }
        Node* temp = begin;
        do {
            if (temp->data == value) {
                return true;
            }
            temp = temp->next;
        } while (temp != begin);
        return false;
    }

    void free() {
        if (begin == nullptr) {
            cout << "список уже пуст";
            return;
        }
        if (begin->next == begin) {
            delete begin;
            begin = nullptr;
            return;
        }
        Node* temp = begin;
        Node* nextNode;
        do {
            nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != begin);
        begin=nullptr;

    }

    void append(int value, int maxnum){
        if (maxnum == 0) {
            return;
        }
        int colvo = (value / maxnum);
        if (colvo == 0 || value == maxnum){
            this->appendToBegin(value);
            return;
        }
        if (maxnum == 1) {
            for (int i = 0; i < value; i++) {
                this->appendToBegin(1);
            }
            return;
        }
        else{
            for (int i = 0; i < colvo+1; i++) {
                if (value < maxnum) {
                    this->appendToBegin(value);
                    return;
                }
                this->appendToBegin(maxnum);
                value = value - maxnum;

            }
        }

    }
};

List intersection(List list1, List list2, List size) {
    List intersectionList;

    if (list1.begin == nullptr || list2.begin == nullptr) {
        
        return intersectionList;
    }
    Node* temp1 = list1.begin;
    Node* temp2 = list2.begin;
    Node* sizet = size.begin;
    do {
        if (temp1->data == temp2->data) {
            intersectionList.appendToBegin(temp1->data);
            temp1 = temp1->next;
            temp2 = temp2->next;
            sizet = sizet->next;
        }
        else if (temp1->data > temp2->data) {
            temp2 = temp2->next;
            sizet = sizet->next;
        }
        else if (temp1->data < temp2->data) {
            temp1 = temp1->next;
            sizet = sizet->next;

        }

    } while (sizet != size.begin);
    return intersectionList;
}
List sizeList(List list1, List list2) {
    int cnt1 = 0;
    int cnt2 = 0;
    Node* temp1 = list1.begin;
    Node* temp2 = list2.begin;
    if (list1.begin == nullptr && list2.begin!= nullptr) {
        std::cout << "1 список пуст";
        return list2;
    }
    if (list2.begin == nullptr && list2.begin!= nullptr) {
        std::cout << "2 список пуст";
        return list1;
    }
    if (list2.begin == nullptr && list2.begin == nullptr) {
        std::cout << "2 списокa пусты";
        return list1;
    }
    do {
        cnt1++;
        temp1 = temp1->next;

    } while (temp1 != list1.begin);
    do {
        cnt2++;
        temp2 = temp2->next;

    } while (temp2 != list2.begin);
    if (cnt1 > cnt2) {
        return list1;
    }
    if (cnt1 == cnt2) {
        std::cout << "Списки имеют одинаковую длинну";
        return list1;
    }
    else
    {
        return list2;
    }
    
}
List sortList(List list) {
    if (list.begin == nullptr) {
        std::cout << "Список пуст сортировка невозможна";
        return list;
    }
    int tempData;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        Node* temp = list.begin;
        while (temp->next != list.begin) {
            if (temp->data > (temp->next)->data) {
                swapped = true;
                tempData = temp->data;
                temp->data = (temp->next)->data;
                (temp->next)->data = tempData;
            }
            temp = temp->next;
        }
    }

    return list;
}

/*
    int countelem(int value) {
        if (begin == nullptr) {
            return 0;
        }
        int num = 0;
        Node* temp = begin;
        do {
            if (temp->data == value) {
                num++;
            }
            temp = temp->next;
        } while (temp != begin);
        return num;
    }
*/