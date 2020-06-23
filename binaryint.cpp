#include <vector>
#include <sstream>
#include <fstream> 
#include <iostream> 
#include <algorithm>
#include <map>
#include "binaryheap.h"

using namespace std; 

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
    return ((int) (index-1)/2 );
}
template<typename T>
int BinaryHeap<T>::child(int index) { //either left or right
    if ((curSize <= 1) || ((2*index) > curSize)) return -1;
    return (int) (2* index); 
}
template<typename T> 
int BinaryHeap<T>::find(int index, T val) {
    if (index > curSize) return -1; 
    if (val < heap[index]) return -1; 
    if (val == heap[index]) return index; 

    int childidx = child(index); 
    int i = -1; 
    if (childidx != -1) {
        i = max(find(childidx, val), find(childidx+1, val));
    }
}
template<typename T>
void BinaryHeap<T>::walkUp(int index) {
    T parentIdx = parent(index);
    if (parentIdx == -1) return; 
    if ((index >= 0) && (parentIdx >=0) && (heap[parentIdx] > heap[index])) {
        swap(heap[parentIdx],heap[index]); 
        walkUp(parentIdx); 
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
    bool isSmaller = (heap[a] < heap[b]);
    if (c > curSize) {
        return (isSmaller) ? a : b; 
    } else if (isSmaller) {
        return(heap[a] < heap[c]) ? a : c; 
    } else {
        return(heap[b] < heap[c]) ? b : c; 
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
    cout << "-----------Test Binary Heap type int----------\n";
    BinaryHeap<int> v; 
    cout << "Build heap with values 30,15,23,-8,1,3,5\n";
    vector<int> a{30,15,23,-8,1,3,5}; 
    v.buildHeap(a);
    cout << "before delete min: (should be -8 1 3 15 30 23 5) "<< endl;
    for (int i = 1; i < v.getSize(); i++) { //should be -8 1 3 15 30 23 5
        cout << v[i] << " "; 
    }
    cout << endl;

    // int array[] = {3, 70, 4, 80,90,5,6,82,84,91,92,7,8};
    // v.buildHeap(array, 13);
    cout << "\nafter delete min: (should now be 1 5 3 15 30 23) " << endl; 
    v.deleteMin(); 
    for (int i = 1; i < v.getSize(); i++) { //should be 1 5 3 15 30 23
        cout << v[i] << " "; 
    }
    cout << "\nInsert (-3): (should be -3 5 1 15 30 23 3) "<< endl; 
    v.insert((-3)); 
    for (int i = 1; i < v.getSize(); i++) { //should be -3 5 1 15 30 23 3
        cout << v[i] << " "; 
    }
    cout << "\n check IsEmpty: " << endl; 
    v.Clear(); 
    cout << v.isEmpty(); 
    cout << "\nDelete from an empty heap: ";
    v.deleteMin(); 
    
    
}


