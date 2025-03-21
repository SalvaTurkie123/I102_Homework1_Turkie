
#include <iostream>
#include <memory>

using namespace std;

struct Node {
    int value;
    shared_ptr<Node> next;
};

struct list {
    shared_ptr<Node> head;
    shared_ptr<Node> tail;
    int size;
};

shared_ptr<Node> create_node(int value) {
    shared_ptr<Node> newNode = make_shared<Node>();
    newNode->value = value;
    newNode->next = nullptr;
    return newNode;
}

void push_front(shared_ptr<list> l, int value) {
    shared_ptr<Node> newNode = create_node(value);
    if (l->head == nullptr) {
        l->head = newNode;
        l->tail = newNode;
    } else {
        newNode->next = l->head;
        l->head = newNode;
    }
    l->size++;
}

void push_back(shared_ptr<list> l, int value) {
    shared_ptr<Node> newNode = create_node(value);
    if (l->head == nullptr) {
        l->head = newNode;
        l->tail = newNode;
    } else {
        l->tail->next = newNode;
        l->tail = newNode;
    }
    l->size++;
}

void insert(shared_ptr<list> l, int value, int position) {
    if (position < 0) {
        cerr << "Error: La posición no puede ser negativa." << endl;
        return;
    }
    if (position == 0) {
        push_front(l, value);
    } else if (position >= l->size) {
        cerr << "Advertencia: La posición ("<< position << ") es mayor o igual al tamaño de la lista. ("<< l->size <<") Se agregará al final." << endl;
        push_back(l, value);
    } else {
        shared_ptr<Node> newNode = create_node(value);
        shared_ptr<Node> current = l->head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        l->size++;
    }
}

void erase(shared_ptr<list> l, int position) {
    if (position < 0) {
        cerr << "Error: La posición no puede ser negativa." << endl;
        return;
    }
    if (position == 0) {
        l->head = l->head->next;
        l->size--;
    } else if (position >= l->size) {
        cerr << "Advertencia: La posición ("<< position << ") es mayor o igual al tamaño de la lista. ("<< l->size <<") Se borrará el último nodo." << endl;
        shared_ptr<Node> current = l->head;
        for (int i = 0; i < l->size - 2; i++) {
            current = current->next;
        }
        current->next = nullptr;
        l->tail = current;
        l->size--;
    } else {
        shared_ptr<Node> current = l->head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        current->next = current->next->next;
        l->size--;
    }
}

void print_list(shared_ptr<list> l) {
    shared_ptr<Node> current = l->head;
    cout << "Lista: "; 
    while (current != nullptr) {
        cout << current->value;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << endl;
}

int main() {
    shared_ptr<list> l = make_shared<list>();
    l->head = nullptr;
    l->tail = nullptr;
    l->size = 0;

    push_front(l, 1);
    push_front(l, 2);
    push_front(l, 3);
    push_back(l, 4);
    push_back(l, 5);
    insert(l, 6, 2);
    insert(l, 7, 0);
    insert(l, 8, 10);
    erase(l, 2);
    erase(l, 0);
    erase(l, 10);

    print_list(l);

    return 0;
}




