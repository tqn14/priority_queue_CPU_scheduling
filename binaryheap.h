#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <iostream> 
#include <vector>
#include <stdexcept>

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
class BinaryHeap {
    private: 
    int curSize; 
    vector<T> heap; 
    void walkDown(int parent);
    void walkUp(int child);  
    public: 
    BinaryHeap(); 
    ~BinaryHeap() {}; 
    bool isEmpty() const {return heap.size() == 1;}
    void Clear();
    T getItem(int index); 
    int parent(int index);
    int child(int index);
    int find(int index, T val); 
    int getMinIdx(int a, int b, int c); 
    void buildHeap(vector<T> &input); 
    void buildHeap(T array[], int n);
    void insert(T val); 
    T deleteMin();
    void remove(T val);
    int getSize(); 
    T& operator[](int index); 
    
};

void operator>>(ifstream &fin, vector<int> &v);
#endif

    
