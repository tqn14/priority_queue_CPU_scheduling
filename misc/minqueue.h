#include <fstream> 
#include <iostream> 
#include <algorithm>
#include <vector>
#include <sstream>

// #include "binaryheap.h"
// #include "pqlinkedlist.h"

using namespace std;
struct CPUjob {
    private:
    int ID; 
    int length; 
    int prior; 
    public: 
    CPUjob(int a =0, int b=0, int c=0) : ID(a), length(b), prior(c) {}; 
    int getID() const {return ID;}
    int getLength() const {return length;}
    int getPrior() const {return prior;}
    bool operator< (const CPUjob& job); 
   
};
bool CPUjob::operator<(const CPUjob& job) { 
    return (this->getPrior() < job.getPrior());
}

void operator>>(ifstream &fin, vector<CPUjob> &v){
    
    if (!fin.is_open()) {
        throw runtime_error("could not open file");
    }
    int ID, length, prior;
    while(!fin.eof()) {
        fin >> ID >> length >> prior; 
        if (!fin.fail()) {
            CPUjob temp_v(ID, length, prior);
            v.push_back(temp_v);
        }
    }
}

void operator<<(ostream &os, CPUjob &v) {
    os << v.getID(); 
    os << v.getLength(); 
    os << v.getPrior();
  
}
