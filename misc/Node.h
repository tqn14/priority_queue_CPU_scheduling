#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node {
    Node(T data) : data(data), next(nullptr), prev(nullptr) {}; // need to define this
    T data;
    Node* next;
    Node* prev;
};

template<typename T> bool operator==(const Node<T>& rhs, const Node<T>& lhs) {
    return rhs.data == lhs.data;
}

template<typename T> bool operator!=(const Node<T>& rhs, const Node<T>& lhs) {
    return rhs.data != lhs.data;
}

template<typename T> bool operator<(const Node<T>& rhs, const Node<T>& lhs) {
    return rhs.data < lhs.data;
}

template<typename T> bool operator>(const Node<T>& rhs, const Node<T>& lhs) {
    return rhs.data > lhs.data;
}

template<typename T> bool operator<=(const Node<T>& rhs, const Node<T>& lhs) {
    return !(rhs > lhs);
}

template<typename T> bool operator>=(const Node<T>& rhs, const Node<T>& lhs) {
    return !(rhs < lhs);
}


#endif