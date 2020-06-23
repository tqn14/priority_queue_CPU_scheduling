#include <vector>
#include <sstream>
#include <fstream> 
#include <iostream> 
#include <algorithm>
#include <chrono>
#include "binaryheap.h"

using namespace std; 
using namespace std::chrono;

struct EmptyHeap : public runtime_error {
   explicit EmptyHeap(char const* msg=nullptr): runtime_error(msg) {}
};

template<typename T> BinaryHeap<T>::BinaryHeap() : heap(1,0), curSize(0) {} 

template<typename T> 
void BinaryHeap<T>::Clear() {
    heap.clear();
    heap.push_back(0);
}
template<typename T> 
T BinaryHeap<T>::getItem(int index) {
    return heap[index]; 
}

template<typename T> 
int BinaryHeap<T>::getSize() {return heap.size();}

template<typename T> 
int BinaryHeap<T>::parent(int index) {
    if (index ==1 ) {
        return -1;
    }
    return (index/2);
}
template<typename T>
int BinaryHeap<T>::child(int index) { //either left or right
    if ((curSize <= 1) || ((2*index) > curSize)) return -1;
    return (2* index); 
}
template<typename T> 
int BinaryHeap<T>::find(int index, T val) {
    if (index > curSize) return -1; 
    if (val.getPrior() < heap[index].getPrior()) return -1; 
    if (val.getPrior() == heap[index].getPrior()) return index; 

    int childidx = child(index); 
    int i = -1; 
    if (childidx != -1) {
        i = max(find(childidx, val), find(childidx+1, val));
    }
}
template<typename T>
void BinaryHeap<T>::walkUp(int index) {
    int parentIdx = parent(index);
    if (parentIdx == -1) return; 
    if ((index >= 0) && (parentIdx >=0)) {
        if (heap[parentIdx].getPrior() > heap[index].getPrior()) { 
            swap(heap[parentIdx],heap[index]); 
            walkUp(parentIdx); 
        } else if (heap[parentIdx].getPrior() == heap[index].getPrior()) {
            if (heap[parentIdx].getID() < heap[index].getID()) {
                swap(heap[parentIdx],heap[index]); 
                walkUp(parentIdx);
            }
        }
    }
}
template<typename T> 
void BinaryHeap<T>::insert(T val) {
    heap.push_back(val); 
    curSize++;
    walkUp(curSize);
}
template<typename T> 
int BinaryHeap<T>::getMinIdx(int a, int b, int c) { 
    //a parent, b left child, c right child 
    bool isSmaller = (heap[a].getPrior() < heap[b].getPrior());
    bool isEqual = (heap[a].getPrior() == heap[b].getPrior());
    bool isIDSmaller = (heap[a].getID() < heap[b].getID());
    if (c > curSize) {
        if (isSmaller) {
            return a;
        } else if (isEqual) {
            return (isIDSmaller) ? a : b;
        } else {
            return b; 
        }
    } else if (isSmaller) {
        if (heap[a].getPrior() < heap[c].getPrior()) {
            return a;
        } else if (heap[a].getPrior() == heap[c].getPrior()) { 
            return (heap[a].getID() < heap[c].getID()) ? a : c;
        } else {
            return c;
        }
    } else if (isEqual) {
        if (isIDSmaller) {
            if (heap[a].getPrior() < heap[c].getPrior()) {
                return a;
            } else if (heap[a].getPrior() == heap[c].getPrior()) { 
                return (heap[a].getID() < heap[c].getID()) ? a : c;
            } else {
                return c;
            }
        } else {
            if (heap[b].getPrior() < heap[c].getPrior()) { 
                return b;
            } else if (heap[b].getPrior() == heap[c].getPrior()) {
                return (heap[b].getID() < heap[c].getID()) ? b : c;
            } else {
                return c; 
            }
        }
    } else { 
        if (heap[b].getPrior() < heap[c].getPrior()) { 
            return b;
        } else if (heap[b].getPrior() == heap[c].getPrior()) {
            return (heap[b].getID() < heap[c].getID()) ? b : c;
        } else {
            return c; 
        }
    }
}
template<typename T> 
void BinaryHeap<T>::walkDown(int index) {
    int childidx = child(index); 
    if (childidx == -1) return; 
    int minidx = getMinIdx(index, childidx, childidx+1); 
    if (minidx != index) {
        swap(heap[minidx], heap[index]); 
        walkDown(minidx); 
    }
}
template<typename T> 
void BinaryHeap<T>::remove(T val) {
    int index = find(1, val); 
    if (index == -1) return; 
    heap[index]=heap[curSize--]; //decrement size
    heap.resize(curSize+1); 
    walkDown(index); 
    walkUp(index); 
}
template<typename T> 
T BinaryHeap<T>::deleteMin() {
    if(isEmpty()) throw EmptyHeap("Empty Heap"); 
    T min = heap[1]; 
    //extract-heapify; 
    remove(min);
    return min;  
}
template<typename T>
void BinaryHeap<T>::buildHeap(T array[], int n) { //O(n log n)?
  curSize= n;
  int i = 0;

  for (; i < n; i++) { // O(n)
    heap.push_back(array[i]);
  }
  for (int i = n; i > 0; i--) {
    walkDown(i); //O(log n)
  }
}
template<typename T>
void BinaryHeap<T>::buildHeap(vector<T> &input) {
    curSize = input.size(); 
    for (auto a : input) {
        heap.push_back(a); 
    }
    for (int i = curSize; i > 0; i--) {
        walkDown(i); 
    }
}

template<typename T>
T& BinaryHeap<T>::operator[](int index) {
    if (index > curSize) {
        throw invalid_argument("index out of bound"); 
    } 
    return heap[index]; 
}

void operator>>(ifstream &fin, vector<CPUjob> &v){
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
               v.push_back(temp_v);
            }
        }
    }
}


int main() {
    cout << "Input size 4: \n";
    BinaryHeap<CPUjob> heap; 
    vector<CPUjob> v;
    ifstream fin("SetSize4.txt");
    fin >> v; 
    cout << "---------------Build Heap CPU type-------------\n";
    auto start1 = high_resolution_clock::now();
    heap.buildHeap(v); 
    // ofstream out("SetSize100000heap.txt"); 
    // for (int i = 1; i < heap.getSize(); i++) { 
    //     int b = heap[i].getLength(); 
    //     while (b > 0) 
    //     { 
    //         out << "Job ";
    //         out << heap[i].getID() << " with length ";
    //         out << b << " and priority ";
    //         out << heap[i].getPrior() << endl;
    //         b--;
    //     }
    // }
    // out << "No more job to run." << endl; 
    // out.close();
    for (int i = 1; i < heap.getSize(); i++) {
        cout << heap[i].getID() << " ";
        cout << heap[i].getLength() << " ";
        cout << heap[i].getPrior() << " ";
    }
    cout << " "; 

    cout << endl;
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1-start1);
    cout << "Time it takes to build heap: " << duration1.count() << endl;
    CPUjob a = CPUjob(112,0,19);
    auto start2 = high_resolution_clock::now();
    heap.insert(a);

    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2-start2);
    cout << "---------------Insert New-------------\n";
    cout << "Time it takes to insert new obj into heap: " << duration2.count() << endl;
    // for (int i = 1; i < heap.getSize(); i++) { //should be 1 5 3 15 30 23
    //     cout << heap[i].getID() << " ";
    //     cout << heap[i].getLength() << " ";
    //     cout << heap[i].getPrior() << " ";
    // }
    cout << endl; 
    auto start3 = high_resolution_clock::now();
    heap.deleteMin();
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3-start3);
    cout << "---------------Delete Min-------------\n";
    cout << "Time it takes to delete minimum obj: " << duration3.count() << endl;
    cout << "\nDelete then check is empty(): \n"; 
    heap.Clear(); 
    cout << heap.isEmpty() << endl;
    // for (int i = 1; i < heap.getSize(); i++) { //should be 1 5 3 15 30 23
    //     cout << heap[i].getID() << " ";
    //     cout << heap[i].getLength() << " ";
    //     cout << heap[i].getPrior() << " ";
    // }
    // cout << endl; 
    // heap.deleteMin();
    // cout << "---------------Delete Min(2)-------------"<< endl; 
    // // for (int i = 1; i < heap.getSize(); i++) { //should be 1 5 3 15 30 23
    // //     cout << heap[i].getID() << " ";
    // //     cout << heap[i].getLength() << " ";
    // //     cout << heap[i].getPrior() << " ";
    // // }
    // cout << endl; 
    // heap.deleteMin();
    // cout << "---------------Delete Min(3)-------------" <<endl; 
    // for (int i = 1; i < heap.getSize(); i++) { //should be 1 5 3 15 30 23
    //     cout << heap[i].getID() << " ";
    //     cout << heap[i].getLength() << " ";
    //     cout << heap[i].getPrior() << " ";
    // }
    // cout << endl; 
}


