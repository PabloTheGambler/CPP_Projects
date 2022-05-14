#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdio>

using namespace std;

struct Node {
    Node* p = nullptr;

    string data;

    Node(string _data) { data = _data; }
};

Node* XOR(Node* a, Node* b) {
    return (Node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

struct List {
    Node* head = nullptr;
    Node* tail = nullptr;
    Node* selected = nullptr;
    Node* leading = nullptr;
    Node* trailing = nullptr;
    Node* front = nullptr; //proj 3
    Node* back = nullptr; //proj 3

    void insert(Node** list, string data) { //wstawanie na BEG albo END
        Node* newnode = new Node(data);

        if (*list != nullptr) {
            (*list)->p = XOR((*list)->p, newnode);
            newnode->p = *list;
        }
        else {
            selected = head = tail = newnode;
        }

        *list = newnode;

        if (&head == list && head->p == selected) {
            leading = head;
        }

        if (&tail == list && tail->p == selected) {
            trailing = tail;
        }
    }

    void insert(Node** previous, Node** selected, Node** list, string data) { //wstawanie w wybranym miejscu
        Node* newnode = new Node(data);
        if (*previous) {
            (*previous)->p = XOR(XOR((*previous)->p, *selected), newnode);
            (*selected)->p = XOR(XOR((*selected)->p, *previous), newnode);
            newnode->p = XOR(*previous, *selected);
            *previous = newnode;
        }
        else {
            insert(list, data);
        }
    }


    void remove(Node** list) {
        if (!*list)  // lista jest już pusta
            return;

        Node* removed = *list;  // node do usunięcia
        Node* temp = *list;

        if (removed->p) {  // istnieje kolejny node
            *list = removed->p;
            (*list)->p = XOR((*list)->p, removed);
        }
        else {  // to był ostani node, lista jest teraz pusta
            selected = head = tail = nullptr;
            front = back = nullptr;
        }

        if (removed == trailing) {
            trailing = nullptr;
        }
        if (removed == leading) {
            leading = nullptr;
        }
        if (removed == selected) {
            selected = tail;
            leading = nullptr;
            trailing = selected->p;
        }

        if (removed == selected && removed->p) {
            selected = removed->p;

            if (selected == head) {
                trailing = selected->p;
            }
            if (selected == tail) {
                leading = selected->p;
            }
        }
        if (temp == back) {
            back = head;
        }
        if (temp == front) {
            front = tail;
        }
        delete removed;
    }

    void print(Node* list, bool print) { //drukowanie print forward i backward
        Node* last = nullptr, * current = list, * next = nullptr;
        int size = 0;

        if (!current) {
            cout << "NULL";
        }
        while (current) {
            if (print) {
                cout << current->data << " ";
            }
            size++;
            next = XOR(last, current->p);
            last = current;
            current = next;
        }
        if (!print) {
            cout << size;
        }
        cout << endl;
    }

    void moveright(Node** next, Node** previous, Node* list, bool print) { //idziemy w prawo
        if (selected == nullptr) {
            if (print)
                cout << "NULL" << endl;
            return;
        }
        if (*next == nullptr) {
            selected = list;
            *next = selected->p;
            *previous = nullptr;
            if (print)
                cout << selected->data << endl;
            return;
        }
        Node* advanced = *next;
        *next = XOR((*next)->p, selected);
        *previous = selected;
        selected = advanced;
        if (print)
            cout << selected->data << endl;
    }

    void moveleft(Node** next, Node** previous, Node* list, bool print) { //idziemy w lewo
        if (selected == nullptr) {
            if (print)
                cout << "NULL" << endl;
            return;
        }
        if (*previous == nullptr) {
            selected = list;
            *previous = selected->p;
            *next = nullptr;
            if (print)
                cout << selected->data << endl;
            return;
        }
        Node* advanced = *previous;
        *previous = XOR((*previous)->p, selected);
        *next = selected;
        selected = advanced;
        if (print)
            cout << selected->data << endl;
    }

    void push(Node** list, string data) { //push
        if (head == nullptr) { //lista pusta
            insert(&head, data);
        }
        if (back == nullptr) { //kolejka pusta
            back = tail;
            front = tail;
            tail->data = data;
        }
        else { //normalna sytuacja
            if (selected == nullptr) {
                return;
            }
            Node** next = &trailing;
            Node** previous = &leading;
            Node* prevtmp = trailing;
            Node* currtmp = selected;
            Node* nexttmp = leading;
            while (true) {
                moveleft(next, previous, tail, false);
                if (selected == back) {
                    moveleft(next, previous, tail, false);
                    if (selected == front) {
                        while (true) {
                            moveleft(next, previous, tail, false);
                            if (selected == back) {
                                break;
                            }
                        }
                        if (previous == nullptr) {
                            insert(&head, data);
                            back = head;
                            head->data = data;
                            break;
                        }
                        else {
                            insert(previous, &selected, &head, data);
                            moveleft(next, previous, tail, false);
                            back = selected;
                            selected->data = data;
                            break;
                        }
                    }
                    back = selected;
                    selected->data = data;
                    break;
                }
                if (selected == currtmp) {
                    next = &nexttmp;
                    previous = &prevtmp;
                    selected = currtmp;
                    break;
                }
            }
        }
    }

    void pop(Node** list) { //pop

        if (front == nullptr) { //kolejka pusta
            cout << "NULL" << endl;
            return;
        }
        if (front == back) { //jeden element
            cout << front->data << endl;
            front = nullptr;
            back = nullptr;
            return;
        }
        else { //normalna sytuacja
            if (selected == nullptr)
                return;
            Node** next = &trailing;
            Node** previous = &leading;
            Node* prevtmp = trailing;
            Node* currtmp = selected;
            Node* nexttmp = leading;
            while (true) {
                moveleft(next, previous, tail, false);
                if (selected == front) {
                    cout << selected->data << endl;
                    moveleft(next, previous, tail, false);
                    front = selected;
                }
                if (selected == currtmp) {
                    next = &nexttmp;
                    previous = &prevtmp;
                    selected = currtmp;
                    break;
                }
            }
        }
    }

    void printq(Node* list, bool print) { //print queue i count
        if (front == nullptr) {
            if (print) {
                cout << "NULL";
                cout << endl;
            }
            if (!print) {
                cout << 0;
                cout << endl;
            }
            return;
        }
        Node** next = &trailing;
        Node** previous = &leading;
        Node* prevtmp = trailing;
        Node* currtmp = selected;
        Node* nexttmp = leading;
        int count = 0;
        while (true) {
            moveleft(next, previous, tail, false);
            if (selected == front) {
                break;
            }
        }
        while (true) {
            if (print) {
                cout << selected->data << " ";
            }
            count++;
            if (selected == back) {
                while (true) {
                    moveleft(next, previous, tail, false);
                    if (selected == currtmp) {
                        next = &nexttmp;
                        previous = &prevtmp;
                        selected = currtmp;
                        break;
                    }
                }
                break;
            }
            moveleft(next, previous, tail, false);
        }
        if (!print) {
            cout << count;
        }
        cout << endl;
    }

    void garbage(Node* list, bool hard) { //garbage soft i hard
        Node** next = &trailing;
        Node** previous = &leading;
        Node* prevtmp = trailing;
        Node* currtmp = selected;
        Node* nexttmp = leading;

        if (head == nullptr) {
            return;
        }

        if (front == nullptr) {
            while (true) {
                if (!hard) {
                    selected->data = "0";
                    moveright(next, previous, head, false);
                    if (selected == currtmp) {
                        break;
                    }
                }
                else {
                    del_selected(next, previous);
                    moveright(next, previous, head, false);
                    if ((selected == currtmp) || (selected == nullptr)) {
                        break;
                    }
                }
            }
            return;
        }
        while (true) {
            moveright(next, previous, head, false);
            if (selected == front) {
                break;
            }
            if (selected == currtmp) {
                next = &nexttmp;
                previous = &prevtmp;
                selected = currtmp;
                break;
            }
        }
        moveright(next, previous, head, false);
        if ((selected == front) || (selected == back)) {
            return;
        }
        while (true) {
            if (!hard) {
                selected->data = "0";
                moveright(next, previous, head, false);
                if (selected == back) {
                    break;
                }
            }
            else {
                del_selected(next, previous);
                moveright(next, previous, head, false);
                if (selected == back) {
                    break;
                }
            }
        }
        while (true) {
            moveright(next, previous, head, false);
            if (selected == currtmp) {
                next = &nexttmp;
                previous = &prevtmp;
                selected = currtmp;
                break;
            }
        }
    }

    void del_selected(Node** next, Node** previous) { //usuwanie wybranego Node 
        Node* removed = selected;
        if (!(*previous) && !(*next)) {
            delete removed;
            head = tail = trailing = leading = selected = nullptr;
            return;
        }

        if (!head) {
            return;
        }

        if (!(*previous)) {
            head = selected->p;
            head->p = XOR((*next)->p, selected);
            selected = tail;
            *next = nullptr;
            *previous = selected->p;

            delete removed;
            return;
        }

        if (*next == nullptr && XOR((*previous)->p, selected) == nullptr) {
            head = tail = selected = *previous;
            selected->p = nullptr;
            *next = *previous = nullptr;
            delete removed;
            return;
        }

        if (*next == nullptr) {
            (*previous)->p = XOR(XOR((*previous)->p, selected), *next);
            selected = *previous;
            tail = selected;
            *previous = XOR(selected->p, *next);
            delete removed;
            return;
        }
        (*previous)->p = XOR(XOR((*previous)->p, selected), *next);
        (*next)->p = XOR(XOR((*next)->p, selected), *previous);
        selected = *previous;
        *previous = XOR(selected->p, *next);

        delete removed;
        return;
    }
};

void ADD_BEG(List* l, string data) { l->insert(&l->head, data); }
void ADD_END(List* l, string data) { l->insert(&l->tail, data); }
void DEL_BEG(List* l) { l->remove(&l->head); }
void DEL_END(List* l) { l->remove(&l->tail); }
void PRINT_FORWARD(List* l) { l->print(l->head, true); }
void PRINT_BACKWARD(List* l) { l->print(l->tail, true); }
void SIZE(List* l) { l->print(l->head, false); } //proj 3
void PUSH(List* l, string data) { l->push(&l->back, data); } //proj 3  
void POP(List* l) { l->pop(&l->front); } //proj 3
void PRINT_QUEUE(List* l) { l->printq(l->front, true); } //proj 3
void COUNT(List* l) { l->printq(l->front, false); } //proj 3
void GARBAGE_SOFT(List* l) { l->garbage(l->front, false); } //proj 3
void GARBAGE_HARD(List* l) { l->garbage(l->front, true); } //proj 3

int main() {
    List list = List();

    string input = "a";

    while (input != "") {
        input = "";

        string first = "";
        string parameter = "";

        getline(cin, input);

        size_t found_f = input.find_first_of(" ");
        size_t found = input.find_last_of(" ");
        first = input.substr(0, found_f);
        parameter = input.substr(found + 1);

        if (first == "ADD_BEG" || first == "ADD_END" || first == "PUSH") {
            if (first == "ADD_BEG")
                ADD_BEG(&list, parameter);
            if (first == "ADD_END")
                ADD_END(&list, parameter);
            if (first == "PUSH") //proj 3
                PUSH(&list, parameter);
        }
        else {
            if (input == "DEL_BEG")
                DEL_BEG(&list);
            if (input == "DEL_END")
                DEL_END(&list);
            if (input == "PRINT_FORWARD")
                PRINT_FORWARD(&list);
            if (input == "PRINT_BACKWARD")
                PRINT_BACKWARD(&list);
            if (input == "SIZE") //proj 3
                SIZE(&list);
            if (input == "POP") //proj 3
                POP(&list);
            if (input == "PRINT_QUEUE") //proj 3
                PRINT_QUEUE(&list);
            if (input == "COUNT") //proj 3
                COUNT(&list);
            if (input == "GARBAGE_SOFT") //proj 3
                GARBAGE_SOFT(&list);
            if (input == "GARBAGE_HARD") //proj 3
                GARBAGE_HARD(&list);
        }
        
    }
    return 0;
}
