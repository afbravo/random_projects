#ifndef __linked_list__
#define __linked_list__

#include <iostream>

namespace LinkedList{

//######################### Begin Node Class #############################

template <class T> class node{
public:
    T data; // data stored in the node
    node *next; // pointer to the next node
    node *prev; // pointer to the previous node
    // constructor with data
    node(T newData) { data = newData; next = nullptr; prev = nullptr; } 
    // constructor with data, next, and prev
    node(T newData, node *newNext, node *newPrev){ data = newData; next = newNext; prev = newPrev; } 
    //destructor
    ~node(){}
    //operator overloads
    template <class U> friend std::ostream& operator<<(std::ostream& os, const node<U>& n);
};

//------------------------Operator Overloads------------------------
template <typename T> std::ostream& operator<<(std::ostream& os, const LinkedList::node<T>& n){
    os << "data: " << n.data << " next: ";
    if(n.next == nullptr){
        os << "nullptr";
    }
    else{
        os << n.next->data << " (" << n.next << ")";
    }
    os << " prev: ";
    if(n.prev == nullptr){
        os << "nullptr";
    }
    else{
        os << n.prev->data << " (" << n.prev << ")";
    }

    return os;
}

//######################### End Node Class #############################


//######################### Begin List Class #############################

template <class T> class list{
private:
    node<T> *head;
    node<T> *tail;
    int _size;
    int _capacity;
public:
    list() { head = nullptr; tail = nullptr; _size = 0; _capacity = 0;}
    ~list();
    //node accessors
    node<T> *begin() { return head; } //O(1)
    node<T> *end() { return tail; } //O(1)
    node<T> *nodeAt(int index); //O(n)
    // element accessors
    T front() { return head->data; } //O(1)
    T back() { return tail->data; } //O(1)
    T at(int index) { return nodeAt(index)->data; } //O(n)
    //capacity 
    bool empty() { return head == nullptr; } //O(1)
    int size() { return _size; } //O(1)
    int max_size() { return _capacity; } //O(1)
    //modifiers
    void clear(); //O(n)
    void insert(node<T> *node, T data); //before node O(1)
    void insert(int pos, T data); //before pos O(n)
    void erase(node<T> *node); //O(1)
    void erase(int index); //O(n)
    void push_back(T data); //O(1)
    void pop_back(); //O(1)
    void push_front(T data); //O(1)
    void pop_front(); //O(1)
    void moveToFront(node<T> *node); //O(1)
    //operations
    void reverse(); //O(n)
    //operator overloads
    int &operator[](int index); //O(n)
    template <class U> friend std::ostream& operator<<(std::ostream& os, const list<U>& l);
};

//------------------------------destructor----------------------------------------
template <class T> LinkedList::list<T>::~list()
{
    LinkedList::node<T> *current = head;
    while(current != nullptr){
        LinkedList::node<T> *next = current->next;
        delete current;
        current = next;
    }
}

// ----------------------------node accessors-----------------------------------
template <class T> LinkedList::node<T> *LinkedList::list<T>::nodeAt(int index)
{
    if(index >= _size){return nullptr;}
    LinkedList::node<T> *current = head;
    for(int i = 0; i < index; i++){
        current = current->next;
    }
    return current;
}

// --------------------------------modifiers------------------------------------

template <class T> void LinkedList::list<T>::clear()
{
    LinkedList::node<T> *current = head;
    while(current != nullptr){
        LinkedList::node<T> *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    _size = 0;
}

template <class T> void LinkedList::list<T>::insert(LinkedList::node<T> *node, T data)
{
    if(node == nullptr){return;}
    LinkedList::node<T> *newNode = new LinkedList::node<T>(data, node, node->prev);
    if(node->prev != nullptr){
        node->prev->next = newNode;
    }
    node->prev = newNode;
    if(node == head){
        head = newNode;
    }
    _size++;
}

template <class T> void LinkedList::list<T>::insert(int pos, T data){
    LinkedList::node<T> *current = nodeAt(pos);
    insert(current, data);
}

template <class T> void LinkedList::list<T>::erase(LinkedList::node<T> *node){
    if(node == nullptr){
        return;
    }
    if(node->prev != nullptr){
        node->prev->next = node->next;
    }
    if(node->next != nullptr){
        node->next->prev = node->prev;
    }
    if(node == head){
        head = node->next;
    }
    if(node == tail){
        tail = node->prev;
    }
    delete node;
    _size--;
}

template <class T> void LinkedList::list<T>::erase(int index){
    LinkedList::node<T> *current = nodeAt(index);
    erase(current);
}

template <class T> void LinkedList::list<T>::push_back(T data){
    tail->next = new LinkedList::node<T>(data, nullptr, tail);
    tail = tail->next;
    _size++;
}

template <class T> void LinkedList::list<T>::pop_back(){
    if(tail == nullptr){return;}
    LinkedList::node<T> *newTail = tail->prev;
    delete tail;
    tail = newTail;
    if(tail == nullptr){
        head = nullptr;
    }
    else{
        tail->next = nullptr;
    }
    _size--;
}

template <class T> void LinkedList::list<T>::push_front(T data){
    LinkedList::node<T> *newnode = new LinkedList::node<T>(data);
    if(head == nullptr){
        head = newnode;
        tail = newnode;
    }
    else{
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }
    _size++;
}

template <class T> void LinkedList::list<T>::pop_front(){
    if(head == nullptr){
        return;
    }
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
    _size--;
}

template <class T> void LinkedList::list<T>::moveToFront(LinkedList::node<T> *node){
    if(node == head){return;}
    if(node == tail){
        tail = tail->prev;
        tail->next = nullptr;
    }
    else{
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    node->next = head;
    node->prev = nullptr;
    head->prev = node;
    head = node;
}

// -------------------------------operations-----------------------------------

template <class T> void LinkedList::list<T>::reverse(){
    LinkedList::node<T> *current = head;
    while(current != nullptr){
        LinkedList::node<T> *temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    }
    LinkedList::node<T> *temp = head;
    head = tail;
    tail = temp;
}

//-------------------------------operator overloads----------------------------

template <class T> int &LinkedList::list<T>::operator[](int index){
    LinkedList::node<T> *current = nodeAt(index);
    return current->data;
}

template <class T> std::ostream& operator<<(std::ostream& os, const LinkedList::list<T>& l){
    LinkedList::node<T> *current = l.head;
    if(current == nullptr){
        os << "empty list"; 
        return os;
    }
    while(current != nullptr){
        os << current->data << "->";
        current = current->next;
    }
    os << "nullptr";
    return os;
}

}



#endif