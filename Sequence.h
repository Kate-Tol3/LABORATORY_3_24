#pragma once

template <typename T>
class Node{
public:
        T value;
        Node<T> *prev;
        Node<T> *next;
public:
    explicit Node(const T &n_val = 0, Node<T> *n_prev = nullptr, Node<T> *n_next = nullptr):
        value(n_val), prev(n_prev), next(n_next){};
};
 
template <typename T>
class Deque {
private:
    int length;
    Node<T>* head;
    Node<T>* tail;
public:

  Deque():  length(0), head(nullptr), tail(nullptr) {};

  ~Deque(){
     Node<T> *curr = head;
        while (curr) {
            Node<T> *temp = curr->next;
            delete curr;
            curr = temp;
        }
  }

  T popFront(){
    if (head == NULL) return;
    auto *temp = head;
    head = head->next;
    if (head) head->prev = NULL;
    if (temp == tail) {tail = NULL};
    T value = temp->value;
    delete temp;

    length--;
    return value;
  }

  T popBack(){
    if (tail == NULL) return;
    auto *temp = tail;
    tail = tail->prev;
    if (tail) tail->next = NULL;
    if (temp == head) {head = NULL};
    T value = temp->value;
    delete temp;
    length--;
    return value;
  }
};