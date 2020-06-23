#ifndef PQLINKEDLIST_H
#define PQLINKEDLIST_H

#include <iostream>

using namespace std; 
template<typename T>
struct Node {
    T obj;       // each node holds an integer data
    T priority; // pointer to the previous node
    Node<T>* next, *prev;     // pointer to the next node
    public: 
    Node (T e = T(), T p = T(), Node<T> *n = nullptr, Node<T> *pr = nullptr)
          : obj(e) , priority(p) , next(n), prev(pr) {}
    T getObj() const {return obj;}
    T getPrior() const {return priority;}
    Node<T> *getNext() const {return next;}
    Node<T> *getPrev() const {return prev;}
};
template<typename T>
class LinkedListPQ {
    private: 
    Node<T> *header,*trailer;
    public:
    LinkedListPQ() : header(T()), trailer(T()) // default constructor
        {header.next = &trailer; trailer.prev = &header; }
    // Node<T> *first_node() const { return header.next; }
    // Node<T> *last_node() const { return trailer.prev; }
    ~LinkedListPQ();  
    bool isEmpty(); 
    void insertFirst(T obj, T prior);
    void insertLast(T obj, T prior); 
    void insertAfter(Node<T>&p, T obj, T prior);
    void insert(T obj, T prior); 
    T removeMin();
};
struct EmptyDLList : public std::runtime_error {
  explicit EmptyDLList(char const* msg=nullptr): runtime_error(msg) {}
};
template<typename T> 
LinkedListPQ<T>::~LinkedListPQ() {
  Node<T> *prev_node, *node = header.next; 
  while(node!=&trailer) {
    prev_node = node; 
    node = node->getNext(); 
    delete prev_node; 
  }
  header.next = &trailer; 
  trailer.prev = &header; 
}
template<typename T>
bool LinkedListPQ<T>::isEmpty() {
    return (header == nullptr);
}
template<typename T>
void LinkedListPQ<T>::insertFirst(T obj, T prior)
{ 
  Node<T> *newNode = new Node<T>(obj, prior,&header, header.next); 
  header.next->prev = newNode; 
  header.next = newNode;
}

template<typename T> 
void LinkedListPQ<T>::insertLast(T obj, T prior) {
  Node<T> *newNode = new Node<T>(obj, prior, trailer.prev,&trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}

template<typename T>
void LinkedListPQ<T>::insertAfter(Node<T> &p, T obj, T prior)
{
  if (&p == nullptr) {
    throw std::invalid_argument("P not found");
  }
  if(p.next == &trailer) {
    insertLast(obj);
  } else { 
    Node<T> *newNode = new Node<T>(obj, prior, nullptr, nullptr); 
    newNode->next = p.next;
    p.next = newNode;
    newNode->prev = p.next->prev;
    if(newNode->next != nullptr) {
      newNode->next->prev = newNode; 
    }
  }

}
template<typename T>
void LinkedListPQ<T>::insert(T obj, T prior) {
  Node<T> *newNode = new Node<T>(obj, prior, nullptr, nullptr);
  if (isEmpty()) {
    insertFirst(obj, prior);
  } else {
    Node<T> *f = header->next; 
    Node<T> *r = trailer->prev; 
    if (prior <= f->getPrior()) {
      insertFirst(obj, prior); 
    } else if (prior > r->getPrior()) {
      insertLast(obj, prior);
    } else {
      Node<T> *curr = f->next; 
      while(curr->getPrior() < prior) {
        insertAfter(curr, obj, prior);
      }
    }
  }

}


template<typename T> 
T LinkedListPQ<T>::removeMin() { //assume list has been sorted min is the first node 
    if(isEmpty()) {
        throw EmptyDLList("Empty list"); 
    }
    Node<T> *tmp = header.next; 
    tmp->next->prev = &header; 
    header.next = tmp->getNext();
    T obj = tmp->getObj(); 
    delete tmp; 
    return obj; 
}
template<typename T> ostream& operator<<(ostream& out, const LinkedListPQ<T>& dll) {
    Node<T> *tmp = dll.first_node(); 
    while(tmp!=dll.after_last_node()) {
        T obj = tmp->getObj(); 
        out << obj;
		    out << ","; 
        tmp = tmp->getNext();
    }
  /* Complete this function */
  return out;
}; 

#endif