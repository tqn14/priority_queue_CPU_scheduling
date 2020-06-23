#ifndef PQLINKEDLIST_H
#define PQLINKEDLIST_H

#include <fstream>
#include <list>
#include <iomanip>
#include <vector>
#include <string>
#include <iostream>
#include <sstream> 

using namespace std; 

template<typename T> 
class LinkedListPQ {
    private: 
    typedef list<T> elem; 
    elem L; 
    public: 
    class Locator {
        friend class LinkedListPQ; 
        private: 
        typename elem::iterator iterator; 
        public: 
        T& operator*() {return *iterator;}
    };
    Locator insertItem(T& t); 
    T removeMin(); 
    void printList();
    void createPQlist(string filename, vector<Locator>& r); 
    void decreaseKey(const Locator& p, vector<Locator>& r);   
};
struct CPUjob {
    int ID; 
    int length; 
    int prior; 
    LinkedListPQ<CPUjob>::Locator *p;
    public:
    CPUjob(int a =0, int b=0, int c=0) : ID(a), length(b), prior(c) {}; 
    int getID() {return this->ID;}
    int getLength() {return this->length;}
    int getPrior() {return this->prior;}
    LinkedListPQ<CPUjob>::Locator *getItem() {return p;}
    // void setID(const int& id) {ID = id;}
    // void setLength(const int& l) {length = l;}
    // void setPrior(const int& p) {prior =p; }
    void setLocator(LinkedListPQ<CPUjob>::Locator *pos) {p=pos;}
    bool operator<(const CPUjob &job) {return (this->prior < job.prior);}
};
template<typename T>
typename LinkedListPQ<T>::Locator
LinkedListPQ<T>::insertItem(T& t) {
    typename elem::iterator iterator = L.begin(); 
    while (iterator != L.end() && !t(*iterator)) {
        ++iterator; 
    }
    Locator pos; 
    pos.iterator = L.insert(iterator, t);
    t.setLocator(&pos); 
    return pos;
}
template<typename T>
void LinkedListPQ<T>::createPQlist(string filename, vector<Locator>& r) {
    ifstream fin(filename); 
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
               r[prior] = insertItem(temp_v);
            }
        }
    }
}
template<typename T>
void LinkedListPQ<T>::printList() {
    for (auto it = L.begin(); it != L.end(); it++) {
        cout << it->getID(); 
        cout << it->getLength();
        cout << it->getPrior();
    }
    cout << endl; 
}
template<typename T>
T LinkedListPQ<T>::removeMin() {
    L.erase(L.begin()); 
    return (*L.begin()); 
}
#endif