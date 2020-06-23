#include <algorithm>
#include <vector> 
#include <iostream>
#include <fstream>
#include <chrono>


#include "pqvectorint.h"
//#include "pqvector.h"
using namespace std; 
using namespace std::chrono;

int main() {
    cout << "---------Test with type int----------\n";
    // ifstream ifs("SetSize100000.txt"); 
    VectorPQ<int> v; 
    vector<int> v1{30,15,23,-8,1,3,5};
    cout << "Test insert values 30,15,23,-8,1,3,5 (unsorted) \n"; 
    ostream out(cout.rdbuf());
    for (auto a : v1 ) { 
        v.insert(a);
    }
    out << v;
    cout << "\nTest insert into sorted vector with value -3: \n";
    v.insertSorted(v,-3); 
    out << v;
    cout << "\nTest remove min:";
    int min = v.removeMin(); 
    cout << "\nmin removed: " << min << endl;
    v.removeMin(); 
    cout << "vector now: \n";
    out << v;
    cout << "\nClear vector and test is_empty: \n"; 
    v.Clear(v);
    out << v;
    cout << (v.isEmpty()) << endl;

    // auto start1 = high_resolution_clock::now();
    // ifs >> job;
    // job.Sort(job);
    // auto stop1 = high_resolution_clock::now();
    // auto duration1 = duration_cast<seconds>(stop1-start1);
    // cout << "Time it takes to input and sort in a vector:" << duration1.count() << "seconds" << endl;
    // CPUjob a = CPUjob(112,0,19);
    // auto start2 = high_resolution_clock::now();
    // job.insertSorted(job,a);
    // auto stop2 = high_resolution_clock::now();
    // auto duration2 = duration_cast<seconds>(stop2-start2);
    // cout << "Time it takes to insert in a sorted vector: " << duration2.count() << "seconds" << endl;
    // ofstream out("SetSize100000out.txt"); 
    // ostream os(cout.rdbuf());
    // for (auto a : job) {
    //     int b = a.getLength(); 
    //     while (b > 0) {
    //         out << "Job "; 
    //         out << a.getID();
    //         out << " with length ";
    //         out << b; 
    //         out << " and priority "; 
    //         out << a.getPrior();
    //         b--; 
    //         out << endl;
    //     }
    // }
    // out << "No more job to run" << endl; 
    // out.close();
    return 0;
    // ofstream out("SetSize4out.txt"); 
    // out << "Job " << job.getID();
}   
