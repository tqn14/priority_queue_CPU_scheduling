#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>



template<typename T>
class DoublyLinkedList {
public:
    /* uncomment the declarations as you implement them */
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        sz = 0;
    }

    DoublyLinkedList(T data) {
        Node<T> *tmp = new Node<T>(data);
        head = tmp;
        tail = tmp;
        sz = 1;
    }
    
    DoublyLinkedList(const DoublyLinkedList<T>& old) {
        // using other member functions to accomplish this
        head = nullptr;
        tail = nullptr;
        sz = 0;
        Node<T> *cur = old.front_node();
        while (cur != nullptr) {
            push_back(cur->data);
            cur = cur->next;
        }
    }
    
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& old) {
        clear();
        // using other member functions to accomplish this
        head = nullptr;
        tail = nullptr;
        sz = 0;
        Node<T> *cur = old.front_node();
        while (cur != nullptr) {
            push_back(cur->data);
            cur = cur->next;
        }
        return *this;
    }
    
    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node<T> *tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        sz = 0;
    }
    
    unsigned int size() const { return sz; }

    T& front() { return head->data; }

    const T& front() const { return head->data; }

    T& back() { return tail->data; }

    const T& back() const { return tail->data; }

    void push_back(T data) {
        Node<T> *tmp = new Node<T>(data);
        // when the list is empty
        if (sz == 0) {
            head = tmp;
            tail = tmp;
        } else {
            tmp->prev = tail;
            tail->next = tmp;
            tail = tmp;
        }
        sz++;
    }
    
    void push_front(T data) {
        Node<T> *tmp = new Node<T>(data);
        // when the list is empty
        if (sz == 0) {
            head = tmp;
            tail = tmp;
        } else {
            head->prev = tmp;
            tmp->next = head;
            head = tmp;
        }
        sz++;
    }

    void pop_back() {
        if (sz > 1) {
            Node<T> *tmp = tail;
            tail->prev->next = nullptr;
            tail = tail->prev;
            sz--;
            if (sz == 1) head = tail;
            delete tmp;
        } else if (sz > 0) {
            delete tail;
            sz = 0;
            head = nullptr;
            tail = nullptr;
        }
    }
    
    void pop_front() {
        if (sz > 1) {
            Node<T> *tmp = head;
            head->next->prev = nullptr;
            head = head->next;
            sz--;
            if (sz == 1) tail = head;
            delete tmp;
        } else if (sz > 0) {
            delete head;
            sz = 0;
            head = nullptr;
            tail = nullptr;
        }
    }

    void erase(unsigned int index) {
        if (index < 0) return;
        if (index == 0) {
            pop_front();
        } else if (index +1 == sz) {
            pop_back();
        } else if (index +1 < sz) {
            unsigned int count = 0;
            Node<T> *tmp = head;
            while (count < index) {
                tmp = tmp->next;
                count++;
            }
            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;
            sz--;
            delete tmp;
        }
    }
    
    void insert(T data, unsigned int idx) {
        if (idx < 0) return;        // hm idx is unsigned ??????
        if (idx == 0) {
            push_front(data);
        } else if (idx == sz) {
            push_back(data);
        } else if (idx < sz) {
            Node<T> *tmp = new Node<T>(data);
            Node<T> *cur = head;
            unsigned int count = 0;
            while (count < idx) {
                cur = cur->next;
                count++;
            }
            tmp->prev = cur->prev;
            tmp->next = cur;
            cur->prev->next = tmp;
            cur->prev = tmp;
            sz++;
        }
    }
    
    void clear() {
        while (head != nullptr) {
            Node<T> *tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        sz = 0;
    }

    Node<T>* front_node() const { return head; }

    std::string to_str() const;

    // breaks encapsulation... gives operator== access to private data... not great approach, but makes the homework easier for you since we haven't talked about iterators :).
    template<typename U> friend bool operator==(DoublyLinkedList<U> const&, DoublyLinkedList<U> const&);
private:
    // do not change ordering.
    Node<T> *head;
    Node<T> *tail;
    unsigned int sz;
};

//////////////////////////////////////////////////////////////////////////////
//                       helper function declarations                       //
//////////////////////////////////////////////////////////////////////////////
template<typename T> std::ostream& operator<<(std::ostream &, DoublyLinkedList<T> const&);

template<typename T> bool operator==(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

template<typename T> bool operator!=(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

//////////////////////////////////////////////////////////////////////////////
//                     member template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
std::string DoublyLinkedList<T>::to_str() const
{
    std::stringstream os;
    const Node<T> *curr = head;
    os << std::endl << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    os << "head: " << head << std::endl;
    os << "tail: " << tail << std::endl;
    os << "  sz: " << sz << std::endl;
    os << std::setw(16) << "node" << std::setw(16) << "node.prev" << std::setw(16) << "node.data" <<  std::setw(16) << "node.next" << std::endl;
    while (curr) {
        os << std::setw(16) << curr;
        os << std::setw(16) << curr->prev;
        os << std::setw(16) << curr->data;
        os << std::setw(16) << curr->next;
        os << std::endl;
        curr = curr->next;
    }
    os << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    return os.str();
}

//////////////////////////////////////////////////////////////////////////////
//                     helper template function definitions                 //
//////////////////////////////////////////////////////////////////////////////
template<typename T>
bool operator==(DoublyLinkedList<T> const& lhs, DoublyLinkedList<T> const& rhs)
{
    if (lhs.size() != rhs.size()) return false;
    Node<T> *c_lhs = lhs.head;
    Node<T> *c_rhs = rhs.head;
    while (c_lhs != nullptr && c_rhs != nullptr) {
        if (c_lhs->data != c_rhs->data) return false;
        c_lhs = c_lhs->next;
        c_rhs = c_rhs->next;
    }
    return true;
}

template<typename T>
bool operator!=(DoublyLinkedList<T> const& lhs, DoublyLinkedList<T> const& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, DoublyLinkedList<T> const& rhs)
{
    os << rhs.to_str();
    return os;
}

#endif
