#ifndef PQVECTOR_H
#define PQVECTOR_H

#include <vector> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;
struct CPUjob {
    int ID; 
    int length; 
    int prior; 
    public:
    CPUjob(int a =0, int b=0, int c=0) : ID(a), length(b), prior(c) {}; 
    int getID() {return this->ID;}
    int getLength() {return this->length;}
    int getPrior() {return this->prior;}
    bool operator<(const CPUjob &job) {return (this->prior < job.prior);}
};
template<typename T>
class VectorPQ {
    private: 
    vector<T> elem;
    
    public:
    CPUjob job; 
    VectorPQ() {elem;}
    ~VectorPQ() {}
    // typename vector<T>::iterator iterator; 
    typename vector<T>::iterator begin() {return elem.begin();}
    typename vector<T>::iterator end() {return elem.end();}
    int getSize(); 
    bool isEmpty(); 
    void insert(const T data); 
    void insertSorted(VectorPQ<T>& elem, const T data);
    void Sort(VectorPQ<T>& elem); 
    T removeMin(); 
    T& operator[](int index); 
};
struct EmptyList : public std::runtime_error {
  explicit EmptyList(char const* msg=nullptr): runtime_error(msg) {}
};
template<typename T>
T& VectorPQ<T>::operator[](int index) {
    if (index > elem.size()) {
        throw invalid_argument("index out of bound"); 
    } 
    return elem[index]; 
}
template<typename T> 
int VectorPQ<T>::getSize() {return elem.size();}
template<typename T>
bool VectorPQ<T>::isEmpty() {return (elem.size()==0);}

template<typename T>
void VectorPQ<T>::Sort(VectorPQ<T>& elem) {
    if (isEmpty()) {
        throw EmptyList("Empty list");
    }
    for (int k = 1; k < elem.getSize(); k++) {
        T tmp = elem[k].getPrior(); 
        int j = k;
        T tmp2 = elem[k];
        for (j; j > 0; j--) {
            if (elem[j].getPrior() < elem[j-1].getPrior()) {
                elem[j]=elem[j-1]; 
                elem[j-1]=tmp2;
            }
        }
      
    }
}

template<typename T> 
T VectorPQ<T>::removeMin() {
    if (isEmpty()) {
        throw EmptyList("Empty list");
    }
    //Sort(); 
    T min = elem[0]; 
    elem.erase(0);
    return min;  
}
template<typename T>
void VectorPQ<T>::insert(const T data) {
    elem.push_back(data);
}
template<typename T>
void VectorPQ<T>::insertSorted(VectorPQ<T>& elem,const T data) {
    elem.elem.push_back(data); 
    elem.Sort(elem);
}

template<typename T>
void operator>>(ifstream &fin, VectorPQ<T> &v){
    if (!fin.is_open()) {
        throw runtime_error("could not open file");
    }
    string line;
    while(getline(fin,line)) {
        istringstream iss(line); 
        int ID, length, prior;
        while (iss >> ID >> length >> prior) {
           if (!fin.fail()) {
               CPUjob temp_v(ID, length, prior);
               v.insert(temp_v);
            }
        }
    }
}
void operator<<(ostream &out, vector<CPUjob> &v) {
    for (auto a : v) {
        out << a.getID();
        out << a.getLength();
        out << a.getPrior();
    }
    out << ", ";
}

#endif
